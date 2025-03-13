set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all cpp files in the src directory
file(GLOB SRC_FILES src/*.cpp protobuf/*.c)

# Define executables
add_executable(zmq_experiment ${SRC_FILES})

# Include directories
target_include_directories(zmq_experiment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/protobuf)
target_include_directories(zmq_experiment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link ZeroMQ and Protobuf
target_link_libraries(zmq_experiment PRIVATE ${ZMQ_LIBRARIES} -lprotobuf-c)
