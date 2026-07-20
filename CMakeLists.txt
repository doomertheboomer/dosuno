cmake_minimum_required(VERSION 3.10)
project(DosUno C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.c

    # fake86 stuff
    src/cpu/cpu.c
    src/cpu/cpu.h
    src/cpu/modregrm.h
    src/cpu/config.h    

    # my stuff
    src/hle/dos.c
    src/hle/bios.c
    src/hle/video.c
)

if(WIN32)
    list(APPEND SOURCES src/platform/console/consoleWindows.c)
else()
    list(APPEND SOURCES src/platform/console/consolePosix.c)
endif()

add_executable(dos-emu ${SOURCES})