#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include "../header/playbookmaster.h"

namespace fs = std::filesystem;

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

std::string playbookOutput = "(PLAYBOOK"+std::to_string(playbookMajorVersion)+") ";
std::unordered_map<int, std::pair<std::string, std::string>> debugCodes = {
    {900, {playbookOutput, "Default_Output"}},
    {901, {"(DIRECTORY) ", "Directory_Print"}},
    {902, {"(RAW LINE)  ", "Raw_Output"}},
    {903, {"(FOUND)     ", "Character_Detected"}},
    {904, {"(SECTION)   ", "Section_Switch"}},
    {905, {"(PROCESSED) ", "Processed_Emoji_From_Symbol"}},
    {906, {"(SPLIT)     ", "File_Split"}},
    {907, {"(WARNING)   ", "Default_Warning"}}
};

std::unordered_map<int, std::pair<std::string, std::string>> errorCodes = {
    // 100 is hardcoded in `playbookinterpreter.cpp`, means 'no sections defined'
    {101, {"Input file not found", "NO_FILE_I"}},
    {102, {"Output file not found", "NO_FILE_O"}},
    {103, {"Muted character found; symbol without `.talk:`", "CHARACTER_WITHOUT_DIALOGUE"}},
    {104, {"Section not closed", "UNCLOSED_SECTION"}},
    {105, {"Section closed early", "SECTION_WITHOUT_OPENING"}},
    {106, {"Symbol to emoji configuration file not found", "NO_CONFIG_FILE"}},
    {107, {"Undefined section found", "UNNAMED_SECTION"}},
    {108, {"Project name is empty", "NO_PROJECT_NAME_PROJECT_CREATOR"}},
    // 109 is hardcoded in `pbkinterprethandlers.cpp`, means 'output file not found'
    {110, {"Symbol does not exist in configuration file", "CHARACTER_SYMBOL_NOT_FOUND"}},
    // 111 is hardcoded in `pbkinterprethandlers.cpp`, means 'failed to write out to debug file'
    // 112 is hardcoded in `pbkinterprethandlers.cpp`, means 'failed to write debug information'
};