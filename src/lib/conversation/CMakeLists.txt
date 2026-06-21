add_library(retronomicon-conversation
    ${RETRO_CONVERSATION_DIR}/src/conversation/conversation_document.cpp
    ${RETRO_CONVERSATION_DIR}/src/conversation/conversation_loader.cpp
    ${RETRO_CONVERSATION_DIR}/src/conversation/conversation_node.cpp
    ${RETRO_CONVERSATION_DIR}/src/conversation/conversation_state.cpp
)

target_include_directories(retronomicon-conversation
    PUBLIC
        ${RETRO_CONVERSATION_DIR}/include
        ${RETRO_INCLUDE_DIR}
)

target_link_libraries(retronomicon-conversation
    PUBLIC
        retronomicon
        nlohmann_json::nlohmann_json
)

if(TARGET Catch2::Catch2WithMain)
    add_executable(retronomicon-conversation-tests
        ${RETRO_CONVERSATION_DIR}/tests/test_conversation_loader.cpp
    )

    target_link_libraries(retronomicon-conversation-tests
        PRIVATE
            retronomicon-conversation
            Catch2::Catch2WithMain
    )

    include(${RETRO_DIR}/external/catch2/extras/Catch.cmake)
    catch_discover_tests(retronomicon-conversation-tests)

    add_custom_command(TARGET retronomicon-conversation-tests POST_BUILD
        COMMAND retronomicon-conversation-tests
        COMMENT "Running retronomicon-conversation tests..."
    )
endif()
