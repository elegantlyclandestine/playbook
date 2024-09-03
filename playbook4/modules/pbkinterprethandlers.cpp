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

void interpreterDebugHandler(std::ofstream& debugFile, std::string debugType, std::string debugInfo, std::string debugFlag) {
    //debug and error codes defined in `pbkenvironmentvariables.cpp`

}