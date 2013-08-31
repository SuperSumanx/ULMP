CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project (ULMP)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -std=c++11 ")
include_directories(include)
set(SOURCES src/main.cpp src/ulmp.cpp)
add_executable(ULMPExampleProgram ${SOURCES})
