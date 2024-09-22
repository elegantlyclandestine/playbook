#pragma once
#ifndef PLAYBOOK_INTERPRETER_H
#define PLAYBOOK_INTERPRETER_H

#include <string>
#include <filesystem>

int interpretScript(std::ifstream& scriptFile, std::string fileName);

#endif