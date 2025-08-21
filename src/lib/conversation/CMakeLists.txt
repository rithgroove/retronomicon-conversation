file(GLOB_RECURSE CONVERSATION_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(retronomicon-conversation ${CONVERSATION_SRC})

target_include_directories(retronomicon-conversation
    PUBLIC
        ${RETRO_CONVERSATION_DIR}/include
        ${RETRO_CONVERSATION_DIR}/external/json/include
        ${RETRO_INCLUDE_DIR}   # retronomicon's include directory
)

target_link_libraries(retronomicon-conversation
    PUBLIC
        retronomicon          # link the base engine
        nlohmann_json::nlohmann_json
)
