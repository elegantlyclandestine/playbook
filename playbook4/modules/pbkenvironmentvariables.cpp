#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include "pbkenvironmentvariables.h"

int playbookMajorVersion = 4;
int playbookMinorVersion = 0;

bool debug = false;
bool debugPrintout = false;
bool debugFull = false;
bool debugFullPrintout = false;
bool createFlag = false;
std::string creationDebugFlag = "";
std::string baseFilename = "";
std::string inputFilename = "";
std::string projectName = "";
std::string projectId = "";
std::string debugFlag = "";
std::string timestamp = std::to_string(std::time(nullptr));
std::string debugInfo = "";

std::string playbookOutput = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+")";
extern std::unordered_map<int, std::pair<std::string, std::string>> debugCodes = {
    {2001, {playbookOutput, "Program_Output"}},
    {2002, {"(DIRECTORY) ", "Directory_Print"}},
    {2003, {"(RAW LINE)  ", "Raw_Output"}},
    {2004, {"(FOUND)     ", "Character_Detected"}},
    {2005, {"(SECTION)   ", "Section_Switch"}},
    {2006, {"(PROCESSED) ", "Processed_Emoji_From_Symbol"}},
    {2007, {"(SPLIT)     ", "File_Split"}}
};

extern std::unordered_map<int, std::pair<std::string, std::string>> errorCodes = {
    {9001, {"No sections defined", "NO_SECTIONS"}},
    {9002, {"Input file not found", "NO_FILE_I"}},
    {9003, {"Output file not found", "NO_FILE_O"}},
    {9004, {"Muted character found (symbol without .talk:)", "CHARACTER_WITHOUT_DIALOGUE"}},
    {9005, {"Section not closed", "UNCLOSED_SECTION"}},
    {9006, {"Section closed early ", "SECTION_WITHOUT_OPENING"}},
    {9007, {"Symbol to emoji configuration file not found", "NO_CONFIG_FILE"}},
    {9008, {"Undefined section found", "UNNAMED_SECTION"}},
    {9009, {"Project name is empty", "NO_PROJECT_NAME_PROJECT_CREATOR"}},
};