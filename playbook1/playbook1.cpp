#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    // Create the emoji map using the insert method
    std::unordered_map<std::string, std::string> emojiMap;
    emojiMap.insert({"jy", "☀️"});   // Joy
    emojiMap.insert({"sd", "💧"});  // Sadness
    emojiMap.insert({"ag", "🔥"});  // Anger
    emojiMap.insert({"ds", "🥦"});  // Disgust
    emojiMap.insert({"fr", "🍇"});  // Fear
    emojiMap.insert({"ax", "🥕"});  // Anxiety
    emojiMap.insert({"ev", "✨"});  // Envy
    emojiMap.insert({"em", "🌸"});  // Embarrassment
    emojiMap.insert({"en", "📱"});  // Ennui
    emojiMap.insert({"sc", "🎬"});  // Scene
    emojiMap.insert({"xn", "👽"});  // Xenomorph
    emojiMap.insert({"mt", "💻"});  // MU/TH/UR
    emojiMap.insert({"bb", "🍬"});  // Bing Bong
    emojiMap.insert({"bl", "💵"});  // Bill

    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }

    std::string line;
    int triggerCount = 0;
    int fileIndex = 1;
    std::ofstream outputFile("output_part_" + std::to_string(fileIndex) + ".txt");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }

    // Function to replace the first trigger with an emoji and ignore other triggers on the same line
    auto processLineWithSingleTrigger = [&](const std::string& line, int& triggerCount) {
        std::string result;
        std::string temp;
        bool triggerFound = false;
        
        for (size_t i = 0; i < line.length(); ++i) {
            temp += line[i];
            
            if (!triggerFound && emojiMap.find(temp) != emojiMap.end()) {
                result += emojiMap.at(temp);  // Replace with corresponding emoji
                triggerCount++;               // Increase trigger count
                temp.clear();
                triggerFound = true;          // Stop processing further triggers on this line
            } else if (temp.length() > 2 || (!isalpha(line[i]) && temp.length() > 1)) {
                result += temp;
                temp.clear();
            }
        }

        // Append any remaining characters not matched
        if (!temp.empty()) {
            result += temp;
        }

        return result;
    };

    while (std::getline(inputFile, line)) {
        // Skip the line if it starts with a '%'
        if (!line.empty() && line[0] == '%') {
            continue;
        }

        int currentLineTriggers = 0;
        std::string processedLine = processLineWithSingleTrigger(line, currentLineTriggers);

        // If adding the line exceeds 10 triggers, create a new file
        if (triggerCount + currentLineTriggers > 10) {
            std::cout << "Part " << fileIndex << " closed. Starting Part " << fileIndex+1 << "..." << std::endl;
            outputFile.close();
            fileIndex++;
            outputFile.open("output_part_" + std::to_string(fileIndex) + ".txt");
            triggerCount = 0;  // Reset trigger count for new file
        }

        // Write the processed line and update trigger count
        outputFile << processedLine << std::endl;
        triggerCount += currentLineTriggers;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Processing completed." << std::endl;
    return 0;
}