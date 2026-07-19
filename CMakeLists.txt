cmake_minimum_required(VERSION 3.10)
project(DosUno C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.c
    src/cpu/cpu.c
    src/cpu/instructions.c
    src/hle/dos.c
    src/hle/bios.c
)

if(WIN32)
    list(APPEND SOURCES src/platform/consoleWindows.c)
else()
    list(APPEND SOURCES src/platform/consolePosix.c)
endif()

add_executable(dos-emu ${SOURCES})