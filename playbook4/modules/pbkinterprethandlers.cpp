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

int debugDisplay(std::ofstream& debugOut, int callCode, std::string infoDump) {
    if (debugCodes.find(callCode) != debugCodes.end()) {
        std::pair<std::string, std::string> debugInfo = debugCodes[callCode];
        if (debugPrintout || debugFullPrintout) {
            debugOut << debugInfo.first << infoDump << std::endl;
        }
        std::cout << debugInfo.first << infoDump << std::endl;
        return 0;
    } else {
        std::cerr << "Error: debug code `" << callCode << "` not found" << std::endl;
        return 1;
    }
}

int errorDisplay(int callCode, int failedLine, std::string infoDump) {
    if (debugCodes.find(callCode) != debugCodes.end() || callCode != 100) {
        std::pair<std::string, std::string> errorInfo = errorCodes[callCode];
        std::cerr << "Error: " << errorInfo.first << "(" << errorInfo.second << ") at line " << failedLine << std::endl << infoDump << std::endl;
        return callCode;
    } else if (callCode == 100){
        std::cerr << "Error: No sections defined in any part of the whole file (NO_SECTIONS)" << std::endl;
        return callCode;
    } else {
        std::cerr << "Error: error code `" << callCode << "` not found (errorception)" << std::endl;
        return 1;
    }
}

void interpreterDebugHandler(std::ofstream& debugFile, int callCode, std::string debugInfo) {
    if (debugEnabled) {
        debugDisplay(debugFile, callCode, debugInfo);
    }
}

// feed problematic line to error handler at `errorInfo`.
int interpreterErrorHandler(int callCode, int lineIndex, std::string errorInfo) {
    if (callCode == 109) {
        std::cerr << "Error: output file not found (NO_FILE_OUT) for " << errorInfo << std::endl;
        return callCode;
    }
    return errorDisplay(callCode, lineIndex, errorInfo);
}