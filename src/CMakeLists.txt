add_subdirectory(binary_chunk)

add_executable(demo main.cpp)
target_link_libraries(demo BinaryChunk)