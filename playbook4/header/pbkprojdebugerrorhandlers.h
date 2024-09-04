#pragma once
#ifndef PBK_PROJ_DEBUGERROR_HANDLERS_H
#define PBK_PROJ_DEBUGERROR_HANDLERS_H

#include <string>
#include <filesystem>

int projDebugHandler(int invokeDebug, std::ofstream& debugFile, std::string debugType, std::string debugInfo, std::string debugFlag);

#endif

