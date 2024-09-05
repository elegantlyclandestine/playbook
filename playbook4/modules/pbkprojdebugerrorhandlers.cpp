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

void projWriteoutDebugHandler(int invokeDebug, std::string debugType, std::string debugInfo, std::string debugFlag) {

}

int projDebugHandler(int invokeDebug, std::string debugType, std::string debugInfo, std::string debugFlag) {
    //debug and error codes defined in `pbkenvironmentvariables.cpp`
    projWriteoutDebugHandler(invokeDebug, debugType, debugInfo, debugFlag);
}