cmake_minimum_required(VERSION 3.21)

project(Emulator)

file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Emulator ${HEADERS} ${SOURCES})
target_include_directories(Emulator PUBLIC include)

set_target_properties(Emulator PROPERTIES
    VS_DEBUGGER_COMMAND_ARGUMENTS "< code.bin > out.bin"
)



