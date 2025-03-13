set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)
include_directories(${ZMQ_INCLUDE_DIRS})

pkg_check_modules(absl REQUIRED absl)
include_directories(${absl_INCLUDE_DIRS})

# Find all cpp files in the src directory
file(GLOB SRC_FILES src/*.cpp protobuf/*.cc)

# Define executables
add_executable(zmq_experiment ${SRC_FILES})

# Include directories
target_include_directories(zmq_experiment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/protobuf)
target_include_directories(zmq_experiment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(zmq_experiment PRIVATE ${Protobuf_INCLUDE_DIRS})

# Link ZeroMQ and Protobuf
target_link_libraries(zmq_experiment PRIVATE
    ${ZMQ_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${absl_LIBRARIES})
