cmake_minimum_required(VERSION 3.10)

project(PlaybookProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the build type (can be overridden from the command line)
set(CMAKE_BUILD_TYPE Debug)

# Add custom compiler flags for debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE};cp playbook4 /usr/local/playbook")

# Include header files
include_directories(header)

# Add the source files
add_executable(playbook4
    playbook4.cpp
    modules/pbkenvironmentvariables.cpp
    modules/pbkprojecthandler.cpp
    modules/playbookcore.cpp
    modules/playbookinterpreter.cpp
    modules/pbkprojcreatorwriteout.cpp
    modules/pbkinterprethandlers.cpp
)

# Optionally, link libraries (if needed)
# target_link_libraries(playbook4 ${LIBS})
