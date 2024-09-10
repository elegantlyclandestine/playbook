#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include "header/playbookcore.h"
#include "header/playbookinterpreter.h"
#include "header/pbkprojecthandler.h"
#include "header/pbkenvironmentvariables.h"

namespace fs = std::__fs::filesystem;

int main(int argc, char* argv[]) {
    debug = false;
    debugPrintout = false;
    debugFull = false;
    debugFullPrintout = false;
    createFlag = false;
    if (commandArgumentHandler(argc, argv) == 0) {
        std::string fullInputPath = getCurrentWorkingDir() + "/" + inputFilename;
        if (!fs::exists(fullInputPath)) {
            std::cerr << "Error: " << fullInputPath << " not detected" << std::endl;
            return 1;
        }

        std::string baseName = inputFilename.substr(0, inputFilename.find_last_of('.'));
        if (!fs::exists(baseName)) {
            fs::create_directory(baseName);
        }

        std::ifstream inputFile(fullInputPath);
        if (!inputFile.is_open()) {
            std::cerr << "Error: " << inputFilename << " not detected" << std::endl;
            return 1;
        }
        interpretScript(inputFile, baseName);
        std::cout << "Processing complete." << std::endl;  
    } else {
        return 1;
    }
    return 0;
}