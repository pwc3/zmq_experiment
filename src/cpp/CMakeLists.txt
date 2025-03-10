set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define executables
add_executable(publisher src/publisher.cpp)
add_executable(subscriber src/subscriber.cpp)

# Link ZeroMQ
target_link_libraries(publisher ${ZMQ_LIBRARIES})
target_link_libraries(subscriber ${ZMQ_LIBRARIES})
