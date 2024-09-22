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

namespace fs = std::filesystem;

int errorDisplay(int callCode, int failedLine, std::string infoDump) {
    if (debugCodes.find(callCode) != debugCodes.end() && (callCode != 100 && callCode != 111)) {
        std::pair<std::string, std::string> errorInfo = errorCodes[callCode];
        std::cerr << "Error: " << errorInfo.first << " (" << errorInfo.second << ") at line " << failedLine << std::endl << infoDump << std::endl;
        return callCode;
    } else if (callCode == 100){
        std::cerr << "Error: No sections defined in any part of the whole file (NO_SECTIONS)" << std::endl;
        return callCode;
    } else if (callCode == 111){
        std::cerr << "Error: Failed to write out to debug file (DEBUG_FILE_FAIL)" << std::endl;
        return callCode;
    } else if (callCode == 112){
        std::cerr << "Error: Failed to write debug information (DEBUG_INFO_FAIL)" << std::endl;
        return callCode;
    } else {
        std::cerr << "Error: error code `" << callCode << "` not found (ERRORCEPTION)" << std::endl;
        return 1;
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

int debugDisplay(std::ofstream& debugOut, int callCode, std::string infoDump) {
    if (debugCodes.find(callCode) != debugCodes.end()) {
        std::pair<std::string, std::string> debugInfo = debugCodes[callCode];
        if (debugPrintout || debugFullPrintout) {
            if (!debugOut.is_open()) {
                interpreterErrorHandler(111, 0, "N/A");
            } else {
                debugOut << debugInfo.first << infoDump << std::endl;
                if (debugOut.fail()) {
                    interpreterErrorHandler(112, 0, "N/A");
                }
            }
        }
        std::cout << debugInfo.first << infoDump << std::endl;
        return 0;
    } else {
        std::cerr << "Error: debug code `" << callCode << "` not found" << std::endl;
        return 1;
    }
}

void interpreterDebugHandler(std::ofstream& debugFile, int callCode, std::string debugInfo) {
    if ((debug || debugPrintout) || (debugFull || debugFullPrintout)) {
        debugDisplay(debugFile, callCode, debugInfo);
    }
}