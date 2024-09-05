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
std::unordered_map<int, std::pair<std::string, std::string>> debugCodes = {
    {0x101, {playbookOutput, "Default_Output"}},
    {0x102, {"(DIRECTORY) ", "Directory_Print"}},
    {0x103, {"(RAW LINE)  ", "Raw_Output"}},
    {0x104, {"(FOUND)     ", "Character_Detected"}},
    {0x105, {"(SECTION)   ", "Section_Switch"}},
    {0x106, {"(PROCESSED) ", "Processed_Emoji_From_Symbol"}},
    {0x107, {"(SPLIT)     ", "File_Split"}},
    {0x108, {"(WARNING)   ", "Default_Warning"}}
};

std::unordered_map<int, std::pair<std::string, std::string>> errorCodes = {
    {0x201, {"No sections defined", "NO_SECTIONS"}},
    {0x202, {"Input file not found", "NO_FILE_I"}},
    {0x203, {"Output file not found", "NO_FILE_O"}},
    {0x204, {"Muted character found (symbol without .talk:)", "CHARACTER_WITHOUT_DIALOGUE"}},
    {0x205, {"Section not closed", "UNCLOSED_SECTION"}},
    {0x206, {"Section closed early ", "SECTION_WITHOUT_OPENING"}},
    {0x207, {"Symbol to emoji configuration file not found", "NO_CONFIG_FILE"}},
    {0x208, {"Undefined section found", "UNNAMED_SECTION"}},
    {0x209, {"Project name is empty", "NO_PROJECT_NAME_PROJECT_CREATOR"}},
};

std::unordered_map<int, std::string, std::string> debugOuts = {
    // project creation specific
    {0x1001, "Attempting to create project directory `" + projectName + "` with project ID `" + projectId + "`"},
    {0x1002, "Same name directory detected."},
    {0x1003, "Warning ignored, overwriting `" + projectName + "`"},
    {0x1004, "Project creation aborted."},
    {0x1005, "Successfully created directory: " + projectName},
    {0x1006, "Project creation failed. An `std::__fs::filesystem error` may have occurred. Terminating project creation..."},
    {0x1007, "Config file path: " + configFilePath},
    {0x1008, "Script file path: " + scriptFilePath},
    {0x1009, "Project creation failed. `emojiconfig.txt` could not be created within the project folder."},
    {0x100A, "Project creation failed. `" + projectId + ".pbk` could not be created within the project folder."},
    {0x100B, "Now creating `emoji_config.txt` within " + projectName + "..."},
    {0x100C, "`emoji_config.txt` successfully created within " + projectName + "."},
    {0x100D, "Now creating `" + projectId + ".pbk` within " + projectName + "..."},
    {0x100E, projectId + ".pbk` successfully created within " + projectName + "."},
    {0x100F, "SUCCESS: `" + projectName + "` was successfully built."},
    
    // script compilation specific
    {0x1010, "Now creating `" + projectId + ".pbk` within " + projectName + "..."},
    {0x1011, projectId + ".pbk` successfully created within " + projectName + "."}
};

std::unordered_map<int, std::string, std::string> errorOuts = {
    {0x2001, {"No sections defined", "NO_SECTIONS"}},
    {0x2002, {"Input file not found", "NO_FILE_I"}},
    {0x2003, {"Output file not found", "NO_FILE_O"}},
    {0x2004, {"Muted character found (symbol without .talk:)", "CHARACTER_WITHOUT_DIALOGUE"}},
    {0x2005, {"Section not closed", "UNCLOSED_SECTION"}},
    {0x2006, {"Section closed early ", "SECTION_WITHOUT_OPENING"}},
    {0x2007, {"Symbol to emoji configuration file not found", "NO_CONFIG_FILE"}},
    {0x2008, {"Undefined section found", "UNNAMED_SECTION"}},
    {0x2009, {"Project name is empty", "NO_PROJECT_NAME_PROJECT_CREATOR"}},
};