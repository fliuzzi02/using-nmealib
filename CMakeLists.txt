cmake_minimum_required(VERSION 3.20)
project(using-nmealib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# This project fetches the pre-compiled nmealib binary for Linux x86-64.
# Only Linux x86-64 binaries are published in the nmealib releases.
if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64"))
    message(FATAL_ERROR "Only Linux x86-64 is supported by the pre-built nmealib release.")
endif()

include(FetchContent)

# Fetch the pre-compiled nmealib binary release
set(NMEALIB_VERSION "0.3.1")
FetchContent_Declare(
    nmealib
    URL "https://github.com/fliuzzi02/nmealib/releases/download/v${NMEALIB_VERSION}/nmealib-${NMEALIB_VERSION}-linux64.tar.gz"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nmealib)

# Add the nmealib cmake directory to the prefix path so find_package can locate it
list(APPEND CMAKE_PREFIX_PATH "${nmealib_SOURCE_DIR}/lib/cmake")

find_package(nmealib REQUIRED)

add_executable(unpackExample unpackExample.cpp)
target_link_libraries(unpackExample PRIVATE nmealib::nmealib)
add_executable(packExample packExample.cpp)
target_link_libraries(packExample PRIVATE nmealib::nmealib)
