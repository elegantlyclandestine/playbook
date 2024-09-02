#pragma once
#ifndef PBK_ENVIRONMENT_VARIABLES_H
#define PBK_ENVIRONMENT_VARIABLES_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>

// Declare global variables as extern
extern bool debug;
extern bool debugPrintout;
extern bool debugFull;
extern bool debugFullPrintout;
extern bool createFlag;
extern std::string creationDebugFlag;
extern std::string baseFilename;
extern std::string inputFilename;
extern std::string projectName;
extern std::string projectId;
extern std::string debugFlag;

#endif // PBK_ENVIRONMENT_VARIABLES_H
