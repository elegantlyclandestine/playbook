#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include "../header/playbookcore.h"
#include "../header/pbkprojecthandler.h"
#include "../header/pbkenvironmentvariables.h"
#include "../header/pbkprojcreatorwriteout.h"

namespace fs = std::__fs::filesystem;

int buildNewProject(std::string projectName, std::string projectId, std::string debugFlag) {
    std::ofstream creationDbgFile;
    if (debugFlag == "debug-printout") {
        std::string debugFilePath=getCurrentWorkingDir()+"/debug-creation-"+projectId+"-"+timestamp+".log";
        creationDbgFile.open(debugFilePath);
        if (!creationDbgFile.is_open()) {
            std::cerr << "Error: Failed to open debug file for logging." << std::endl;
            return 1;
        }
    }

    std::string fullCreationPath = getCurrentWorkingDir() + "/" + projectName;

    // Improved logging for initial project creation attempt
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Attempting to create project directory `" + projectName + "` with project ID `" + projectId + "`";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }

    // Check if the project name is empty
    if (projectName.empty()) {
        std::cerr << "Error: Project name is empty." << std::endl;
        return 1;
    }

    // Check if the project directory already exists
    if (fs::exists(fullCreationPath)) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(WARNING)   Same name directory detected.";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
        }

        std::string confirmation;
        std::cout << "WARNING: Playbook project `" << projectName << "` already exists. Do you want to overwrite this? [y/N] > ";
        std::cin >> confirmation;

        if (confirmation == "y" || confirmation == "Y") {
            if (debugFlag == "debug" || debugFlag == "debug-printout") {
                debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Warning ignored, overwriting `" + projectName + "`";
                if (debugFlag == "debug") {
                    std::cout << debugInfo << std::endl;
                }
                creationDbgFile << debugInfo << std::endl;
            }
        } else {
            if (debugFlag == "debug" || debugFlag == "debug-printout") {
                debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Project creation aborted.";
                if (debugFlag == "debug") {
                    std::cout << debugInfo << std::endl;
                }
                creationDbgFile << debugInfo << std::endl;
            }
            std::cerr << "Overwrite aborted by user." << std::endl;
            return 1;
        }
    }

    try {
        // Create the project directory
        fs::create_directory(fullCreationPath);
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Successfully created directory: " + projectName;
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Project creation failed. An `std::__fs::filesystem error` may have occurred. Terminating project creation...";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
        }
        std::cerr << "Error: Failed to create directory `" << projectName << "`: " << e.what() << std::endl;
        return 1;
    }

    // Create file paths within the new directory
    std::string configFilePath = fullCreationPath + "/emoji_config.txt";
    std::string scriptFilePath = fullCreationPath + "/" + projectId + ".pbk";

    // Log file paths
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Config file path: " + configFilePath;
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;

        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Script file path: " + scriptFilePath;
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }

    // Open the files within the new directory
    std::ofstream sampleConfig(configFilePath);
    std::ofstream sampleScript(scriptFilePath);

    if (!sampleConfig.is_open()) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Project creation failed. `emojiconfig.txt` could not be created within the project folder.";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
        }
        std::cerr << "Error: Emoji configuration file could not be opened/created." << std::endl
                  << "You may not have the correct permissions." << std::endl;
        return 1;
    }

    if (!sampleScript.is_open()) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Project creation failed. `" + projectId + ".pbk` could not be created within the project folder.";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
        }
        std::cerr << "Error: Playbook script file could not be opened/created." << std::endl
                  << "You may not have the correct permissions." << std::endl;
        return 1;
    }

    // Write to the config file
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Now creating `emoji_config.txt` within " + projectName + "...";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }
    writeConfig(sampleConfig);

    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" `emoji_config.txt` successfully created within " + projectName + ".";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }

    // Write to the script file
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Now creating `" + projectId + ".pbk` within " + projectName + "...";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }
    writePbkFile(sampleScript);

    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" `" + projectId + ".pbk` successfully created within " + projectName + ".";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" SUCCESS: `" + projectName + "` was successfully built.";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
    }
    creationDbgFile.close();
    std::cout << "Your Playbook 3 project `" << projectName << "` has been successfully created." << std::endl
              << "Please refer to the " << projectId << ".pbk in your folder to get started." << std::endl;
    return 0;
}