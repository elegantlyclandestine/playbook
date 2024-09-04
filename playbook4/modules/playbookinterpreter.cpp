#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include "../header/playbookcore.h"
#include "../header/playbookinterpreter.h"
#include "../header/pbkenvironmentvariables.h"
#include "../header/pbkinterprethandlers.h"

namespace fs = std::__fs::filesystem;

int interpretScript(std::ifstream& inputFile, std::string baseName) {
    std::string currentEmoji;
    std::string debugInfo;
    std::string line;
    int fileIndex = 1;
    int symbolCount = 0;
    int sectionIndex = 1;
    std::string currentSection = baseName;
    std::ofstream outputFile;
    std::ofstream debugFile;
    bool skipLine = false;
    bool sectionDefined = false;
    bool inSection = false;
    // used if any debug flags are set, full or not
    bool debugEnabled = (debug || debugPrintout) || (debugFull || debugFullPrintout);

    // Print working directory for debugging
    if (debugEnabled) {
        std::string timestamp = std::to_string(std::time(nullptr));
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+") Program will now compile "+inputFilename+". Please wait...";
        if (debug || debugFull) {
            std::cout << debugInfo << std::endl;
            }
        debugFile.open("debug-" + timestamp + ".log");
        logDebugInfo(debugInfo, debugFile);
    }
    if (debugEnabled) {
        debugInfo = "(DIRECTORY) " + getCurrentWorkingDir();
        if (debug || debugFull) {
            std::cout << debugInfo << std::endl;
        }
        logDebugInfo(debugInfo, debugFile);
    }

    // Load the emoji configuration file
    std::unordered_map<std::string, std::string> emojiMap = loadConfig("emoji_config.txt");

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
            if (!outputFile.is_open()) {
                std::cerr << "Error opening output file!" << std::endl;
                return 1;
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
        debugInfo = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+" Program has successfully compiled `"+inputFilename+"`.";
        if (debug || debugFull) {
            std::cout << debugInfo << std::endl;
            }
        logDebugInfo(debugInfo, debugFile);
    }

    if (debugFile.is_open()) {
        debugFile.close();
    }
    return 0;
}