#pragma once
#ifndef PLAYBOOK_CORE_H
#define PLAYBOOK_CORE_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>

std::ofstream createDebugFile(std::string debugFlag);
std::string getCurrentWorkingDir();
std::unordered_map<std::string, std::string> loadConfig(const std::string& configFilePath);
void printDebug(std::string debugInfo, std::string debugFlag, std::string debugType);
void logDebugInfo(const std::string& debugInfo, std::ofstream& dbgFile);
int commandArgumentHandler(int argCount, char* argValues[]);

// debug and error specific
int refreshDebug_Project(std::string projectName, std::string projectId, std::string configFilePath, std::string scriptFilePath);

#endif