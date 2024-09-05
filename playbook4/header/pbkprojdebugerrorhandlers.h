#pragma once
#ifndef PBK_PROJ_DEBUGERROR_HANDLERS_H
#define PBK_PROJ_DEBUGERROR_HANDLERS_H

#include <string>
#include <filesystem>

// Only specific to project creation debugging. Debug file creation on `playbookcore.h`
void projWriteoutDebugHandler(int invokeDebug, std::string debugType, std::string debugInfo, std::string debugFlag);
int projDebugHandler(int invokeDebug, std::string debugType, std::string debugInfo, std::string debugFlag);

#endif

