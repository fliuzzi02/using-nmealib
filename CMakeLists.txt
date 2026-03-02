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
set(NMEALIB_VERSION "v0.2.1")
FetchContent_Declare(
    nmealib
    URL "https://github.com/fliuzzi02/nmealib/releases/download/${NMEALIB_VERSION}/nmealib-linux64.tar.gz"
    URL_HASH SHA256=29dc85e1cebe5f67516770d9929a41e9c93997e0468c1a867094be49cde3dfc3
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nmealib)

# Create an interface target that exposes headers and only the used libraries.
# The --start-group/--end-group linker flags (GNU ld) allow multiple passes
# over the archive group to resolve cross-library dependencies.
add_library(nmealib_bundle INTERFACE)
target_include_directories(nmealib_bundle INTERFACE "${nmealib_SOURCE_DIR}/include")
target_link_libraries(nmealib_bundle INTERFACE
    -Wl,--start-group
    # Core library (NmeaException and base message interface)
    "${nmealib_SOURCE_DIR}/lib/libnmealib_core.a"
    # NMEA 0183 support: base class, factory, and message registry
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_base.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_factory.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_registry.a"
    # NMEA 0183 sentence types used in this project
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_gga.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_rmc.a"
    # Additional NMEA 0183 sentence types (required by the registry)
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_gll.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_gsa.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_vtg.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_zda.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_dbt.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_mwv.a"
    "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea0183_vhw.a"
    # NMEA 2000 support (not used in this project; uncomment to enable)
    # "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea2000_base.a"
    # "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea2000_factory.a"
    # "${nmealib_SOURCE_DIR}/lib/libnmealib_nmea2000_registry.a"
    -Wl,--end-group
)

add_executable(using-nmealib main.cpp)
target_link_libraries(using-nmealib PRIVATE nmealib_bundle)
