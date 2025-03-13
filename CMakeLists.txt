cmake_minimum_required(VERSION 3.10)
project(ZeroMQ_CPP)

set(CMAKE_CXX_STANDARD 17)

# Find ZeroMQ
find_package(PkgConfig REQUIRED)
find_package(absl RE)
pkg_check_modules(ZMQ REQUIRED libzmq)
pkg_check_modules(Protobuf REQUIRED protobuf)

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

# Include and link directories
include_directories(${ZMQ_INCLUDE_DIR})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${absl_INCLUDE_DIRS})

link_directories(${ZMQ_LIBRARY_DIR})
link_directories(${Protobuf_LIBRARY_DIRS})
link_directories(${absl_LIBRARY_DIRS})

# Add subdirectory for C++ source files
add_subdirectory(src/cpp)
