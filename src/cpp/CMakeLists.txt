cmake_minimum_required(VERSION 3.10)
project(ZeroMQ_CPP)

set(CMAKE_CXX_STANDARD 17)

# Find ZeroMQ
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

# Platform-specific include paths
if(APPLE)
    # Use `brew --prefix` to find Homebrew's install location dynamically
    execute_process(COMMAND brew --prefix OUTPUT_VARIABLE BREW_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(ZMQ_INCLUDE_DIR "${BREW_PREFIX}/include")
    set(ZMQ_LIBRARY_DIR "${BREW_PREFIX}/lib")
elseif(UNIX)
    # Assume standard locations on Raspberry Pi / Linux
    set(ZMQ_INCLUDE_DIR "/usr/include")
    set(ZMQ_LIBRARY_DIR "/usr/lib")
endif()

# Include directories
include_directories(${ZMQ_INCLUDE_DIR})

# Link directories
link_directories(${ZMQ_LIBRARY_DIR})

# Define executables
add_executable(publisher src/publisher.cpp)
add_executable(subscriber src/subscriber.cpp)

# Link ZeroMQ
target_link_libraries(publisher ${ZMQ_LIBRARIES})
target_link_libraries(subscriber ${ZMQ_LIBRARIES})