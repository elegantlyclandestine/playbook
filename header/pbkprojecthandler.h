#pragma once
#ifndef PBK_PROJECT_HANDLER_H
#define PBK_PROJECT_HANDLER_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>

int buildNewProject(std::string projectName, std::string projectId, std::string debugFlag);

#endif