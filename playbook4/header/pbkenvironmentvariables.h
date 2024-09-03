#pragma once
#ifndef PBK_ENVIRONMENT_VARIABLES_H
#define PBK_ENVIRONMENT_VARIABLES_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <utility>
#include <unistd.h>

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
extern std::string timestamp;
extern std::string debugInfo;
extern int playbookMajorVersion;
extern int playbookMinorVersion;
extern std::unordered_map<int, std::pair<std::string, std::string>> debugCodes;
extern std::unordered_map<int, std::pair<std::string, std::string>> errorCodes;

#endif
