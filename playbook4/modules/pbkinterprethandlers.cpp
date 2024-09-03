#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include "../header/playbookcore.h"
#include "../header/playbookinterpreter.h"
#include "../header/pbkenvironmentvariables.h"
#include "../header/pbkinterprethandlers.h"

void interpreterDebugHandler(std::ofstream& debugFile, std::string debugType, std::string debugInfo, std::string debugFlag) {
    std::unordered_map<int, std::string, std::string> debugCodes = {
    {2001, "(PLAYBOOK"+std::to_string(playbookMajorVersion)+")", "ProgramOutput"},
    {2002, "(DIRECTORY) ", "DirectoryPrint"},
    {2003, "(RAW LINE)  ", "RawOutput"},
    {2004, "(FOUND)     ", "SymbolDetected"},
    {2005, "(SECTION)   ", "SectionSwitch"},
    {2006, "(PROCESSED) ", "ProcessedEmojiAndText"},
    {2007, "(SPLIT)     ", "FileSplit"}
};
}