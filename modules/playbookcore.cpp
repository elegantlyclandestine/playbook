#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include "../header/playbookcore.h"
#include "../header/pbkprojecthandler.h"
#include "../header/playbookinterpreter.h"
#include "../header/pbkenvironmentvariables.h"

namespace fs = std::filesystem;

std::ofstream createDebugFile(std::string debugFlag) {
    std::ofstream debugLogFile;
    if (debugFlag == "debug-printout") {
        std::string debugFilePath=getCurrentWorkingDir()+"/debug-creation-"+projectId+"-"+timestamp+".log";
        debugLogFile.open(debugFilePath);
        if (!debugLogFile.is_open()) {
            std::cerr << "Error: Failed to open debug file for logging." << std::endl;
        }
        return debugLogFile;
    }
    // Else, no debug-printout detected, not making debug file
}

std::string getCurrentWorkingDir() {
    char temp[PATH_MAX];
    return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}

std::unordered_map<std::string, std::string> loadConfig(const std::string& configFilePath) {
    std::unordered_map<std::string, std::string> charMap;
    std::ifstream configFile(configFilePath);
    std::string line;
    bool commentFound = false;

    while (std::getline(configFile, line)) {
        // if comment found, skip line
        if (std::count(line.begin(), line.end(), ':') == 3) {
            commentFound = true;
        }
        size_t delimPos = line.find('=');
        if (delimPos != std::string::npos && !commentFound) {
            std::string symbol = line.substr(0, delimPos);
            std::string emoji = line.substr(delimPos + 1);
            charMap[symbol] = emoji;
        }
        commentFound = false;
    }
    return charMap;
}

void logDebugInfo(const std::string& debugInfo, std::ofstream& dbgFile) {
    if (!dbgFile.is_open()) {
        std::cerr << "Error: Failed to write to debug file. File is not open." << std::endl;
    } else {
        dbgFile << debugInfo << std::endl;
        if (dbgFile.fail()) {
            std::cerr << "Error: Failed to write debug information." << std::endl;
        }
    }
}

int commandArgumentHandler(int argCount, char* argValues[]) {
    for (int i = 1; i < argCount; ++i) {
        std::string arg = argValues[i];
        CLIArgument argument = getArgument(arg);
        switch (argument) {
            case VERSION:
                std::cout << "Playbook version " << playbookMajorVersion << "." << playbookMinorVersion << std::endl;
                break;
            case DEBUG:
                debug = true;
                creationDebugFlag = "debug";
                break;
            case DEBUG_PRINTOUT:
                debugPrintout = true;
                creationDebugFlag = "debug-printout";
                break;
            case DEBUG_FULL:
                debugFull = true;
                creationDebugFlag = "debug-full";
                break;
            case DEBUG_FULL_PRINTOUT:
                debugFullPrintout = true;
                creationDebugFlag = "debug-full-printout";
                break;
            case CREATE:
                createFlag = true;
                // Ensure that projectName and projectId are provided
                if (i + 2 < argCount) {  // Check if there are at least two more arguments
                    projectName = argValues[++i];  // Get the next argument as projectName
                    projectId = argValues[++i];    // Get the following argument as projectId
                } else {
                    std::cerr << "Error: `create` requires a project name and a project ID." << std::endl;
                    return 1;
                }
                break;
            case UNDEFINED:
                baseFilename = argValues[i];
                inputFilename = baseFilename + ".pbk";
                break;
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
        std::cerr << "Usage: " << argValues[0] << " <input-file> [--debug] [--debug-printout] [--debug-full] [--debug-full-po/printout]" << std::endl
                  << "       " << argValues[0] << " create <project name> <project id> [--debug] [--debug-printout]" << std::endl;
        return 1;
    }
    return 0;
}