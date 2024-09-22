cmake_minimum_required(VERSION 3.10)

project(Playbook4)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(header)

# Add the source files
add_executable(playbook
    playbook.cpp
    modules/pbkenvironmentvariables.cpp
    modules/pbkprojecthandler.cpp
    modules/playbookcore.cpp
    modules/playbookinterpreter.cpp
    modules/pbkprojcreatorwriteout.cpp
    modules/pbkinterprethandlers.cpp
    modules/pbkprojdebugerrorhandlers.cpp
)
