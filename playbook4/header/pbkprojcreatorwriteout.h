#pragma once
#ifndef PBK_PROJCREATOR_WRITEOUT_H
#define PBK_PROJCREATOR_WRITEOUT_H

#include <filesystem>
#include <fstream>

// needed by pbkprojecthandler:
// functions write out sample config and playbook file to project folder
void writeConfig(std::ofstream& configOut);
void writePbkFile(std::ofstream& pbkOut);

#endif