#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>

namespace fs = std::__fs::filesystem;

const int playbookMajorVersion = 3;
const int playbookMinorVersion = 5;

std::string getCurrentWorkingDir() {
    char temp[PATH_MAX];
    return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}

std::unordered_map<std::string, std::string> loadConfig(const std::string& configFilePath) {
    std::unordered_map<std::string, std::string> emojiMap;
    std::ifstream configFile(configFilePath);
    std::string line;

    while (std::getline(configFile, line)) {
        size_t delimPos = line.find('=');
        if (delimPos != std::string::npos) {
            std::string symbol = line.substr(0, delimPos);
            std::string emoji = line.substr(delimPos + 1);
            emojiMap[symbol] = emoji;
        }
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

int buildNewProject(std::string projectName, std::string projectId, std::string debugFlag) {
    std::string timestamp = std::to_string(std::time(nullptr));
    std::ofstream creationDbgFile;
    std::string debugInfo;

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
        debugInfo = "(PLAYBOOK3) Attempting to create project directory `" + projectName + "` with project ID `" + projectId + "`";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
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
            creationDbgFile.flush();
        }

        std::string confirmation;
        std::cout << "WARNING: Playbook project `" << projectName << "` already exists. Do you want to overwrite this? [y/N] > ";
        std::cin >> confirmation;

        if (confirmation == "y" || confirmation == "Y") {
            if (debugFlag == "debug" || debugFlag == "debug-printout") {
                debugInfo = "(PLAYBOOK3) Warning ignored, overwriting `" + projectName + "`";
                if (debugFlag == "debug") {
                    std::cout << debugInfo << std::endl;
                }
                creationDbgFile << debugInfo << std::endl;
                creationDbgFile.flush();
            }
        } else {
            if (debugFlag == "debug" || debugFlag == "debug-printout") {
                debugInfo = "(PLAYBOOK3) Project creation aborted.";
                if (debugFlag == "debug") {
                    std::cout << debugInfo << std::endl;
                }
                creationDbgFile << debugInfo << std::endl;
                creationDbgFile.flush();
            }
            std::cerr << "Overwrite aborted by user." << std::endl;
            return 1;
        }
    }

    try {
        // Create the project directory
        fs::create_directory(fullCreationPath);
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK3) Successfully created directory: " + projectName;
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
            creationDbgFile.flush();
        }
    } catch (const fs::filesystem_error& e) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK3) Project creation failed. An `std::__fs::filesystem error` may have occurred. Terminating project creation...";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
            creationDbgFile.flush();
        }
        std::cerr << "Error: Failed to create directory `" << projectName << "`: " << e.what() << std::endl;
        return 1;
    }

    // Create file paths within the new directory
    std::string configFilePath = fullCreationPath + "/emoji_config.txt";
    std::string scriptFilePath = fullCreationPath + "/" + projectId + ".pbk";

    // Log file paths
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK3) Config file path: " + configFilePath;
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();

        debugInfo = "(PLAYBOOK3) Script file path: " + scriptFilePath;
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
    }

    // Open the files within the new directory
    std::ofstream sampleConfig(configFilePath);
    std::ofstream sampleScript(scriptFilePath);

    if (!sampleConfig.is_open()) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK3) Project creation failed. `emojiconfig.txt` could not be created within the project folder.";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
            creationDbgFile.flush();
        }
        std::cerr << "Error: Emoji configuration file could not be opened/created." << std::endl
                  << "You may not have the correct permissions." << std::endl;
        return 1;
    }

    if (!sampleScript.is_open()) {
        if (debugFlag == "debug" || debugFlag == "debug-printout") {
            debugInfo = "(PLAYBOOK3) Project creation failed. `" + projectId + ".pbk` could not be created within the project folder.";
            if (debugFlag == "debug") {
                std::cout << debugInfo << std::endl;
            }
            creationDbgFile << debugInfo << std::endl;
            creationDbgFile.flush();
        }
        std::cerr << "Error: Playbook script file could not be opened/created." << std::endl
                  << "You may not have the correct permissions." << std::endl;
        return 1;
    }

    // Write to the config file
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK3) Now creating `emoji_config.txt` within " + projectName + "...";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
    }
    sampleConfig << "foo=😀" << std::endl
                 << "bar=😁" << std::endl
                 << "narrator=🎬" << std::endl;
    sampleConfig.close();

    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK3) `emoji_config.txt` successfully created within " + projectName + ".";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
    }

    // Write to the script file
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK3) Now creating `" + projectId + ".pbk` within " + projectName + "...";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
    }

    sampleScript << "::: " << projectName << std::endl
                 << "::: by Author" << std::endl
                 << "::: Description goes here." << std::endl
                 << "::: If you want to make comments, type ::: before your comment." << std::endl
                 << ":::" << std::endl
                 << "--[sample-section-1]--" << std::endl
                 << "narrator.talk:" << std::endl
                 << "    -# Foo and Bar walk on stage to a rousing applause." << std::endl
                 << "    -# They wave at the crowd with smiles and waves all aobut." << std::endl
                 << "foo.talk:" << std::endl
                 << "    Hello!" << std::endl
                 << "    This is how you make me talk." << std::endl
                 << "bar.talk:" << std::endl
                 << "    And *this* is how you make *me* say something." << std::endl
                 << "    # Markdown works pretty well too." << std::endl
                 << "    -# You see that?" << std::endl
                 << "foo.talk:" << std::endl
                 << "    Okay, showoff. Anyway, this is what a PLAYBOOK 3 script looks like." << std::endl
                 << "    You can edit it as much as you want, hell you can have thousands of lines and it will process just fine!" << std::endl
                 << "    It's scalable to any size of roleplay you want. Just edit the emojiconfig.txt to add, change or remove characters as needed." << std::endl
                 << "bar.talk:" << std::endl
                 << "    For every ten symbols you processs, it splits off to another file." << std::endl
                 << "foo.talk:" << std::endl
                 << "    That's right, Bar! How about continuing the show for the rest of our folks here?" << std::endl
                 << "bar.talk:" << std::endl
                 << "    With pleasure." << std::endl
                 << "    You can define sections like we've already done for you around the top." << std::endl
                 << "foo.talk:" << std::endl
                 << "    Make sure you disable special dashes, because the program doesn't recognise those!" << std::endl
                 << "bar.talk:" << std::endl
                 << "    Right. Also, we almost forgot, your dialogue after a symbol.talk declaration has to be in a new line, with FOUR spaces before you make us talk." << std::endl
                 << "    It's there for clean-up and organisation reasons!" << std::endl
                 << "foo.talk:" << std::endl
                 << "    Right again, Bar! And since this is the tenth symbol declaration, it looks like I'll see you on the other side!" << std::endl
                 << "bar.talk:" << std::endl
                 << "    Oh, hello! I'm on file #2. Neat, huh?" << std::endl
                 << "foo.talk:" << std::endl
                 << "    Hey there, Bar! How are things?" << std::endl
                 << "bar.talk:" << std::endl
                 << "    Handy dandy nice over here! After all of that, after you're done with your project... go to your command prompt or terminal and type PLAYBOOK3 " << projectName << ".pbk to see your hard-worked roleplay script come to life." << std::endl
                 << "foo.talk:" << std::endl
                 << "    You will *no* longer have to worry about Tupperbox's proxy limits again!" << std::endl
                 << "bar.talk:" << std::endl
                 << "    To close, we'll see you in another section of the project!" << std::endl
                 << "--[sample-section-2]--" << std::endl
                 << "foo.talk:" << std::endl
                 << "    Hello from another section, ladies and gentlemen! Bar, I believe you have some closing things to say?" << std::endl
                 << "bar.talk:" << std::endl
                 << "    Yup. If you want to see what's behind the scenes when PLAYBOOK 3 compiles your script, you can type --debug to see what it's doing!" << std::endl
                 << "    And if you don't want that log cluttering your command line display, you can type --debug-printout and look at the log file after it finishes!" << std::endl
                 << "foo.talk:" << std::endl
                 << "    But watch it, folks! You could make a mistake when making Playbook scripts. Don't worry, the program will catch it for you!" << std::endl
                 << "bar.talk:" << std::endl
                 << "    Correctomundo, Foo! I guess that's it for us at the Foo and Bar show, featuring yours truly with my partner!" << std::endl
                 << "foo.talk:" << std::endl
                 << "    -# together" << std::endl
                 << "    # Have a good night!" << std::endl
                 << "bar.talk:" << std::endl
                 << "    -# together" << std::endl
                 << "    # Have a good night!" << std::endl
                 << "narrator.talk:" << std::endl
                 << "    -# The crowd goes wild!" << std::endl
                 << "    -# Foo and Bar wave goodbye to the crowd as the curtains close and the spotlight turns off." << std::endl;
    sampleScript.close();

    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK3) `" + projectId + ".pbk` successfully created within " + projectName + ".";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
    }
    if (debugFlag == "debug" || debugFlag == "debug-printout") {
        debugInfo = "(PLAYBOOK3) SUCCESS: `" + projectName + "` was successfully built.";
        if (debugFlag == "debug") {
            std::cout << debugInfo << std::endl;
        }
        creationDbgFile << debugInfo << std::endl;
        creationDbgFile.flush();
    }
    creationDbgFile.close();
    std::cout << "Your Playbook 3 project `" << projectName << "` has been successfully created." << std::endl
              << "Please refer to the " << projectId << ".pbk in your folder to get started." << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    bool debug = false;
    bool debugPrintout = false;
    bool debugFull = false;
    bool debugFullPrintout = false;
    bool createFlag = false;
    std::string creationDebugFlag;
    std::string baseFilename;
    std::string inputFilename;
    std::string projectName;
    std::string projectId;
    std::ofstream debugFile;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--version" || arg == "--v") {
            std::cout << "Playbook version " << playbookMajorVersion << "." << playbookMinorVersion << std::endl;
            return 0;
        }
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
            if (i + 2 < argc) {  // Check if there are at least two more arguments
                projectName = argv[++i];  // Get the next argument as projectName
                projectId = argv[++i];    // Get the following argument as projectId
            } else {
                std::cerr << "Error: `create` requires a project name and a project ID." << std::endl;
                return 1;
            }
            continue;
        } else {
            baseFilename = argv[i];
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

    // Get the current working directory
    std::string currentWorkingDir = getCurrentWorkingDir();

    // Combine the current working directory with the input filename
    std::string fullInputPath = currentWorkingDir + "/" + inputFilename;

    // Check if the file exists in the current working directory
    if (!fs::exists(fullInputPath)) {
        std::cerr << "Error: " << fullInputPath << " not detected" << std::endl;
        return 1;
    }

    std::string baseName = inputFilename.substr(0, inputFilename.find_last_of('.'));
    if (!fs::exists(baseName)) {
        fs::create_directory(baseName);
    }

    // Load the emoji configuration file
    std::unordered_map<std::string, std::string> emojiMap = loadConfig("emoji_config.txt");

    std::ifstream inputFile(fullInputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: " << inputFilename << " not detected" << std::endl;
        return 1;
    }

    std::string line;
    int fileIndex = 1;
    int symbolCount = 0; // Track the number of symbols encountered
    int sectionIndex = 1; // Track section indices
    std::string currentSection = baseName; // Current section directory
    std::ofstream outputFile(currentSection + "/part_" + std::to_string(fileIndex) + ".txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }

    std::string currentEmoji;
    std::string debugInfo;
    bool skipLine = false; // Flag to handle lines after symbols
    bool sectionDefined = false; // Track if any section is defined
    bool inSection = false; // Track if currently inside a section
    bool debugEnabled = (debug || debugPrintout) || (debugFull || debugFullPrintout); // Track if any full debug arguments are used

    // Print working directory for debugging
    std::string timestamp = std::to_string(std::time(nullptr));
    debugFile.open("debug-" + timestamp + ".log");
    if (debugEnabled) {
        debugInfo = "(PLAYBOOK3) Program will now compile "+inputFilename+". Please wait...";
        if (debug || debugFull) {
            std::cout << debugInfo << std::endl;
            }
        logDebugInfo(debugInfo, debugFile);
    }
    if (debugEnabled) {
        debugInfo = "(DIRECTORY) " + getCurrentWorkingDir();
        if (debug || debugFull) {
            std::cout << debugInfo << std::endl;
        }
        logDebugInfo(debugInfo, debugFile);
    }


    while (std::getline(inputFile, line)) {
        // Print raw line for debugging
        if (debugFull || debugFullPrintout) {
            debugInfo = "(RAW LINE)  " + line;
            if (debug || debugFull) {
                std::cout << debugInfo << std::endl;
            }
            logDebugInfo(debugInfo, debugFile);
        }

        // Skip comments starting with `:::`
        if (line.find(":::") == 0) {
            continue;
        }

        // Error check: Premature section (if a ]-- is found without --[ )
        if (line.find("]--") != std::string::npos && line.find("--[") == std::string::npos) {
            std::cerr << "Error: Premature section closure detected at line: " << line << std::endl;
            return 1;
        }

        // Handle section definitions
        if (line.find("--[") != std::string::npos && line.find("]--") != std::string::npos) {
            inSection = true;
            sectionDefined = true; // Mark that a section is defined

            // Extract section name
            size_t startPos = line.find('[') + 1;
            size_t endPos = line.find(']');
            std::string sectionName = line.substr(startPos, endPos - startPos);

            // Error check: Blank section name
            if (sectionName.empty()) {
                std::cerr << "Error: Blank section name detected at line: " << line << std::endl;
                return 1;
            }

            // Create new folder for the section
            fs::path newDir = baseName + "/" + (std::to_string(sectionIndex) + "-" + sectionName);
            if (!fs::exists(newDir)) {
                fs::create_directory(newDir);
            }
            currentSection = newDir.string();
            sectionIndex++;
            fileIndex = 1; // Reset part number for the new section
            symbolCount = 0; // Reset symbol count for the new section

            outputFile.close();
            outputFile.open(currentSection + "/part_" + std::to_string(fileIndex) + ".txt");
            if (!outputFile.is_open()) {
                std::cerr << "Error opening output file!" << std::endl;
                return 1;
            }
            
            if (debugEnabled) {
                debugInfo = "(SECTION)   Switching to section: " + sectionName;
                if (debug || debugFull) {
                    std::cout << debugInfo << std::endl;
                }
                logDebugInfo(debugInfo, debugFile);
            }
            continue;
        }

        // Error check: Unterminated section
        if (line.find("--[") != std::string::npos && line.find("]--") == std::string::npos) {
            std::cerr << "Error: Unterminated section detected at line: " << line << std::endl;
            return 1;
        }

        // Check if the line is a symbol declaration
        size_t dotPos = line.find(".talk:");
        if (dotPos != std::string::npos) {
            std::string symbol = line.substr(0, dotPos);
            auto it = emojiMap.find(symbol);
            if (it != emojiMap.end()) {
                if (symbolCount >= 10) {
                    // Move to the next file
                    outputFile.close();
                    fileIndex++;
                    symbolCount = 0;
                    outputFile.open(currentSection + "/part_" + std::to_string(fileIndex) + ".txt");
                    if (!outputFile.is_open()) {
                        std::cerr << "Error opening output file!" << std::endl;
                        return 1;
                    }
                    
                    // Log file splitting info
                    debugInfo = "(SPLIT)     Splitting into part " + std::to_string(fileIndex);
                    if (debug || debugFull) {
                        std::cout << debugInfo << std::endl;
                    }
                    logDebugInfo(debugInfo, debugFile);
                }

                currentEmoji = it->second;
                skipLine = true; // Skip leading spaces and append emoji
                symbolCount++;

                if (debugEnabled) {
                    debugInfo = "(FOUND)     Found symbol: `" + symbol + "` with emoji: `" + currentEmoji + "`";
                    if (debug || debugFull) {
                        std::cout << debugInfo << std::endl;
                    }
                    logDebugInfo(debugInfo, debugFile);
                }
            } else {
                // Error check: Unknown symbol
                std::cerr << "Error: Unknown symbol '" << symbol << "' detected at line: " << line << std::endl;
                return 1;
            }
            continue;
        }

        // Error check: Muted character
        if (!currentEmoji.empty() && dotPos != std::string::npos) {
            std::cerr << "Error: Muted character (symbol with no .talk:) detected at line: " << line << std::endl;
            return 1;
        }

        // Process the line
        if (skipLine) {
            line.erase(0, 4); // Remove exactly four leading spaces
            // Prepend the emoji to the processed line
            std::string processedLine = currentEmoji + " " + line;

            if (debugEnabled) {
                debugInfo = "(PROCESSED) " + processedLine;
                if (debug || debugFull) {
                    std::cout << debugInfo << std::endl;
                }
                logDebugInfo(debugInfo, debugFile);
            }
            outputFile << processedLine << std::endl;

        // Continue removing spaces on subsequent lines until another symbol is found
        } else {
            line.erase(0, 4); // Remove exactly four leading spaces
            outputFile << line << std::endl;
        }

        // Continue removing spaces until another symbol is found
        if (line.find(".talk:") != std::string::npos) {
            skipLine = true;
        } else {
            skipLine = false;
        }
    }

    inputFile.close();
    outputFile.close();

    // Error check: No sections defined
    if (!sectionDefined) {
        std::cerr << "Error: No sections defined in the script!" << std::endl;
        return 1;
    }

    if (debugEnabled) {
        debugInfo = "(PLAYBOOK3) Program has successfully compiled `"+inputFilename+"`.";
        if (debug || debugFull) {
            std::cout << debugInfo << std::endl;
            }
        logDebugInfo(debugInfo, debugFile);
    }

    if (debugFile.is_open()) {
        debugFile.close();
    }

    std::cout << "Processing complete." << std::endl;
    return 0;
}