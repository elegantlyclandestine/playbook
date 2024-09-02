#include <string>
#include <fstream>
#include <filesystem>
#include "pbkenvironmentvariables.h"

bool debug = false;
bool debugPrintout = false;
bool debugFull = false;
bool debugFullPrintout = false;
bool createFlag = false;
std::string creationDebugFlag = "";
std::string baseFilename = "";
std::string inputFilename = "";
std::string projectName = "";
std::string projectId = "";
std::string debugFlag = "";
std::string timestamp = std::to_string(std::time(nullptr));
std::string debugInfo = "";