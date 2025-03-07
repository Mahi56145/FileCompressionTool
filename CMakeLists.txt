cmake_minimum_required(VERSION 3.10)
project(CppCompressionApp)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/compression)
include_directories(${PROJECT_SOURCE_DIR}/zlib)  # Add zlib include directory

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add zlib source files
file(GLOB ZLIB_SOURCES "${PROJECT_SOURCE_DIR}/zlib/*.c")

# Add executable
add_executable(CppCompressionApp ${SOURCES} ${ZLIB_SOURCES})

# Link against ws2_32 library
target_link_libraries(CppCompressionApp ws2_32)

target_include_directories(CppCompressionApp PRIVATE
    ${CMAKE_SOURCE_DIR}/zlib
    ${CMAKE_SOURCE_DIR}/src/compression
    ${CMAKE_SOURCE_DIR}/src/decompression
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/web
)