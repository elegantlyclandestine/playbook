#pragma once
#ifndef PBK_INTERPRET_HANDLERS_H
#define PBK_INTERPRET_HANDLERS_H

#include <string>
#include <filesystem>

void sectionHandler();
void messageHandler();
void symbolHandler();
void emojiConfigHandler();
void outputHandler(std::ofstream outputFile);
void errorHandler(int invokeError);
void interpreterDebugHandler(int invokeDebug, std::ofstream& debugFile, std::string debugType, std::string debugInfo, std::string debugFlag);

#endif

