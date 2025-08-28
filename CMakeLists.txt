cmake_minimum_required(VERSION 3.15)
project(retronomicon-conversation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RETRO_CONVERSATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RETRO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../retronomicon/include)

# External libraries
# add_subdirectory(external/json)

# Build conversation sources
add_subdirectory(src)

# Link retronomicon explicitly
# (retronomicon is already built by the workspace root CMakeLists.txt)
message(STATUS "Building retronomicon-conversation as standalone lib ✅")
