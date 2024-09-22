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
void interpreterDebugHandler(std::ofstream& debugFile, int callCode, std::string debugInfo);
int interpreterErrorHandler(int callCode, int lineIndex, std::string errorInfo);

#endif

