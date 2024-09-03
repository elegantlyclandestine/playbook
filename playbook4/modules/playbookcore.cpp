#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include "../header/playbookcore.h"
#include "../header/pbkprojecthandler.h"
#include "../header/playbookinterpreter.h"
#include "../header/pbkenvironmentvariables.h"

namespace fs = std::__fs::filesystem;

std::string getCurrentWorkingDir() {
    char temp[PATH_MAX];
    return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}

std::unordered_map<std::string, std::string> loadConfig(const std::string& configFilePath) {
    std::unordered_map<std::string, std::string> emojiMap;
    std::ifstream configFile(configFilePath);
    std::string line;
    bool commentFound = false;

    while (std::getline(configFile, line)) {
        // if comment found, skip line
        if (line.find(':::') == !std::string::npos) {
            commentFound = true;
        }
        size_t delimPos = line.find('=');
        if (delimPos != std::string::npos && !commentFound) {
            std::string symbol = line.substr(0, delimPos);
            std::string emoji = line.substr(delimPos + 1);
            emojiMap[symbol] = emoji;
        }
        commentFound = false;
    }
    return emojiMap;
}

void logDebugInfo(const std::string& debugInfo, std::ofstream& dbgFile) {
    if (!dbgFile.is_open()) {
        std::cerr << "Error: Failed to write to debug file. File is not open." << std::endl;
    } else {
        dbgFile << debugInfo << std::endl;
        dbgFile.flush(); // Ensure the data is written immediately
        if (dbgFile.fail()) {
            std::cerr << "Error: Failed to write debug information." << std::endl;
        }
    }
}

int commandArgumentHandler(int argCount, char* argValues[]) {
    for (int i = 1; i < argCount; ++i) {
        std::string arg = argValues[i];

        if (arg == "--debug") {
            debug = true;
            creationDebugFlag = "debug";
            continue;
        } else if (arg == "--debug-printout") {
            debugPrintout = true;
            creationDebugFlag = "debug-printout";
            continue;
        } else if (arg == "--debug-full") {
            debugFull = true;
            continue;
        } else if (arg == "--debug-full-po" || arg == "--debug-full-printout") {
            debugFullPrintout = true;
            continue;
        } else if (arg == "create") {
            createFlag = true;
            // Ensure that projectName and projectId are provided
            if (i + 2 < argCount) {  // Check if there are at least two more arguments
                projectName = argValues[++i];  // Get the next argument as projectName
                projectId = argValues[++i];    // Get the following argument as projectId
            } else {
                std::cerr << "Error: `create` requires a project name and a project ID." << std::endl;
                return 1;
            }
            continue;
        } else {
            baseFilename = argValues[i];
            inputFilename = baseFilename + ".pbk";
            continue;
        }
    }

    if (createFlag) {
        if (!projectName.empty() && !projectId.empty()) {
            return buildNewProject(projectName, projectId, creationDebugFlag);
        } else {
            std::cerr << "Error: Project name or ID is missing." << std::endl;
            return 1;
        }
    }

    if (inputFilename.empty()) {
        std::cerr << "Usage: ./playbook3 <input-file> [--debug] [--debug-printout] [--debug-full] [--debug-full-po/printout]" << std::endl
                  << "       ./playbook3 create <project name> <project id> [--debug] [--debug-printout]" << std::endl;
        return 1;
    }
    return 0;
}