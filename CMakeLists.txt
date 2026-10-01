cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(FrameWindowDetector VERSION 0.1.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
message(STATUS "=== DEBUG GEODE VERSION ===")
message(STATUS "GEODE_VERSION=${GEODE_VERSION}")
message(STATUS "GEODE_VERSION_FULL=${GEODE_VERSION_FULL}")
message(STATUS "GEODE_SDK=$ENV{GEODE_SDK}")
execute_process(
    COMMAND git -C "$ENV{GEODE_SDK}" rev-parse HEAD
    OUTPUT_VARIABLE GEODE_SDK_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "GEODE_SDK_COMMIT=${GEODE_SDK_COMMIT}")
message(STATUS "=== END DEBUG ===")

setup_geode_mod(${PROJECT_NAME})
