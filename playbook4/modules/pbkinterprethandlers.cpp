#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include <utility>
#include "../header/playbookcore.h"
#include "../header/playbookinterpreter.h"
#include "../header/pbkenvironmentvariables.h"
#include "../header/pbkinterprethandlers.h"

void debugDisplay(int callCode) {
    if (debugCodes.find(callCode) != debugCodes.end()) {
        std::pair<std::string, std::string> debugInfo = debugCodes[callCode];
        std::cout << "Debug Message: " << debugInfo.first << std::endl;
        std::cout << "Technical Info: " << debugInfo.second << std::endl;
    } else {
        std::cout << "Debug code not found: " << callCode << std::endl;
    }
}

void interpreterDebugHandler(std::ofstream& debugFile, int callCode, std::string debugInfo) {
    //debug and error codes defined in `pbkenvironmentvariables.cpp`
    if (debugEnabled) {
        debugDisplay(callCode);
    }
}