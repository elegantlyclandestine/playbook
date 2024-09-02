#pragma once
#ifndef PLAYBOOK_INTERPRETER_H
#define PLAYBOOK_INTERPRETER_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>

// a lot of these are unused for now.
// will separate big `interpretScript()` function later
void sectionHandler();
void messageHandler();
void symbolHandler();
void emojiConfigHandler();
void outputHandler(std::ofstream outputFile);
void debugHandler(std::string debugInfo, std::string debugFlag, std::string debugType);
int interpretScript(std::ifstream& scriptFile, std::string fileName);

#endif