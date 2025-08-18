# src/lib/conversation/CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

set(CONVERSATION_SOURCES
    conversation_scene.cpp
    conversation_node.cpp
    conversation_system.cpp
    conversation_loader.cpp
)

set(CONVERSATION_HEADERS
    ${RETRO_CONVERSATION_INCLUDE_DIR}/retronomicon/lib/conversation/conversation_scene.h
    ${RETRO_CONVERSATION_INCLUDE_DIR}/retronomicon/lib/conversation/conversation_node.h
    ${RETRO_CONVERSATION_INCLUDE_DIR}/retronomicon/lib/conversation/conversation_system.h
    ${RETRO_CONVERSATION_INCLUDE_DIR}/retronomicon/lib/conversation/conversation_loader.h
)

add_library(retronomicon-conversation STATIC
    ${CONVERSATION_SOURCES}
    ${CONVERSATION_HEADERS}
)

target_include_directories(retronomicon-conversation
    PUBLIC
        ${RETRO_CONVERSATION_INCLUDE_DIR}
        ${RETRO_CONVERSATION_DIR}/external/json/include
)

target_link_libraries(retronomicon-conversation
    PUBLIC
        retronomicon
        nlohmann_json::nlohmann_json
)
