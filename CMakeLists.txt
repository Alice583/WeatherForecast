cmake_minimum_required(VERSION 3.20)

project(
        labwork7-Alice583
        VERSION 1.0
        DESCRIPTION "C++ Year 2024 labword7"
        LANGUAGES CXX C
)


set(CMAKE_CXX_STANDARD 17)
#
#SET(GCC_COVERAGE_LINK_FLAGS    "-Bstatic")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

file(GLOB curses_SRC
        "third-party/curses/pdcurses/*.h"
        "third-party/curses/pdcurses/*.c"
)

include_directories(third-party/curses/pdcurses)

add_subdirectory(lib)
add_subdirectory(bin)
#
if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if(POLICY CMP0079 )
    cmake_policy(SET CMP0079 NEW)
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)

if(POLICY CMP0135 )
    cmake_policy(SET CMP0135 NEW)
endif()
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

#add_library(curses SHARED ${PROJECT_SOURCE_DIR}/third-party/PDCurses-3.9/wincon/pdcurses.dll)
#set_target_properties(curses PROPERTIES LINKER_LANGUAGE CXX)
#
#target_link_libraries(${PROJECT_NAME} PRIVATE curses)

#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
