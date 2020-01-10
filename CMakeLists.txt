cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_STANDARD 14)
#add_subdirectory(unit-tests)
#add_definitions(-D$ENV{ROBOT}_car)
#message("robot set to $ENV{ROBOT}")

#include_directories(/usr/local/include/opencv4)
link_directories(/usr/local/lib)

set(CPP_FILES
    logger.cpp
    web_server.cpp
    string_utils.cpp
    system.cpp
)
add_executable(web-server ${CPP_FILES})
target_compile_options(web-server PRIVATE -Wno-psabi)
target_link_libraries(web-server pthread)
