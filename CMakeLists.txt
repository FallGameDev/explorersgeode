cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build for both Apple Silicon and Intel Macs
if (APPLE)
	set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

project(ExplorersFirstLevel VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED src/main.cpp)

# The Geode SDK must be installed and GEODE_SDK must point to it
if (NOT DEFINED ENV{GEODE_SDK})
	message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable.")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})
