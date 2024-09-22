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
#include "../header/pbkprojdebugerrorhandlers.h"

namespace fs = std::filesystem;

void projWriteoutDebugHandler(int invokeDebug, std::string debugType, std::string debugInfo, std::string debugFlag) {
    // works the same way, except tailor made for project debugging. to be implemented.
}

int projDebugHandler(int invokeDebug, std::string debugType, std::string debugInfo, std::string debugFlag) {
    //debug and error codes defined in `pbkenvironmentvariables.cpp`
    projWriteoutDebugHandler(invokeDebug, debugType, debugInfo, debugFlag);
    return 0;
}