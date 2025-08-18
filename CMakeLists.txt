cmake_minimum_required(VERSION 3.15)
project(retronomicon VERSION 0.1 LANGUAGES CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(RETRO_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Retronomicon include path")
set(RETRO_CONVERSATION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Retronomicon Conversation Module include path")

# External libraries
add_subdirectory(external/json)

# Engine source (will add retronomicon conversation library)
add_subdirectory(src)

# Public include paths
include_directories(
    ${RETRO_INCLUDE_DIR}/include
    ${RETRO_CONVERSATION_INCLUDE_DIR}/external/json/include
)

#add_subdirectory(tests)

# Optional: Message info
message(STATUS "Building retronomicon conversation as a library ✅")
