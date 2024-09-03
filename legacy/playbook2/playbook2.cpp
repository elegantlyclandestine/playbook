#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>

namespace fs = std::__fs::filesystem;

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

void logDebugInfo(const std::string& message, std::ofstream& debugFile) {
    if (debugFile.is_open()) {
        debugFile << message << std::endl;
    }
}

int main(int argc, char* argv[]) {
    bool debug = false;
    bool debugPrintout = false;
    std::string inputFilename;
    std::ofstream debugFile;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--debug") {
            debug = true;
        } else if (std::string(argv[i]) == "--debug-printout") {
            debugPrintout = true;
            std::string timestamp = std::to_string(std::time(nullptr));
            debugFile.open("debug-" + timestamp + ".log");
        } else {
            inputFilename = argv[i];
        }
    }

    if (inputFilename.empty()) {
        std::cerr << "Usage: ./playbook <input-file.pbk> [--debug] [--debug-printout]" << std::endl;
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

    // Print working directory for debugging
    if (debug || debugPrintout) {
        debugInfo = "(PLAYBOOK2) Program will now compile "+inputFilename+". Please wait...";
        if (debug) {
            std::cout << debugInfo << std::endl;
            }
        logDebugInfo(debugInfo, debugFile);
    }
    if (debug || debugPrintout) {
        debugInfo = "(DIRECTORY) " + getCurrentWorkingDir();
        if (debug) {
            std::cout << debugInfo << std::endl;
        }
        logDebugInfo(debugInfo, debugFile);
    }


    while (std::getline(inputFile, line)) {
        // Print raw line for debugging
        if (debug || debugPrintout) {
            debugInfo = "(RAW LINE)  " + line;
            if (debug) {
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
            
            if (debug || debugPrintout) {
                debugInfo = "(SECTION)   Switching to section: " + sectionName;
                if (debug) {
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
                    if (debug) {
                        std::cout << debugInfo << std::endl;
                    }
                    logDebugInfo(debugInfo, debugFile);
                }

                currentEmoji = it->second;
                skipLine = true; // Skip leading spaces and append emoji
                symbolCount++;

                if (debug || debugPrintout) {
                    debugInfo = "(FOUND)     Found symbol: `" + symbol + "` with emoji: `" + currentEmoji + "`";
                    if (debug) {
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

            if (debug || debugPrintout) {
                debugInfo = "(PROCESSED) " + processedLine;
                if (debug) {
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

    if (debug || debugPrintout) {
        debugInfo = "(PLAYBOOK2) Program has successfully compiled "+inputFilename;
        if (debug) {
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