#include "retronomicon/conversation/conversation_loader.h"
#include "retronomicon/conversation/conversation_state.h"

#include <catch2/catch_test_macros.hpp>

using retronomicon::conversation::ConversationLoader;
using retronomicon::conversation::ConversationState;

TEST_CASE("ConversationLoader parses nodes, backgrounds, choices, and actions") {
    const auto document = ConversationLoader::loadFromString(R"json(
        {
          "start": "intro",
          "background": {
            "room": "asset/image/room.png"
          },
          "nodes": {
            "intro": {
              "speaker": "jenna",
              "background": "room",
              "expression": "neutral",
              "text": "Hello.",
              "choices": [
                { "text": "Continue", "next": "end" }
              ],
              "actions": [
                { "type": "sound", "target": "confirm", "value": "asset/audio/ok.ogg", "duration": 0.25 }
              ]
            },
            "end": {
              "text": "Done.",
              "next": null
            }
          }
        }
    )json");

    REQUIRE(document.getStartNodeId() == "intro");
    REQUIRE(document.validate().empty());

    const auto* intro = document.findNode("intro");
    REQUIRE(intro != nullptr);
    CHECK(intro->speaker == "jenna");
    CHECK(intro->background == "room");
    CHECK(intro->choices.size() == 1);
    CHECK(intro->choices[0].next == "end");
    CHECK(intro->actions.size() == 1);
    CHECK(intro->actions[0].duration == 0.25f);
}

TEST_CASE("ConversationDocument validation reports broken links") {
    const auto document = ConversationLoader::loadFromString(R"json(
        {
          "nodes": {
            "start": {
              "background": "missing",
              "next": "nowhere"
            }
          }
        }
    )json");

    const auto issues = document.validate();
    REQUIRE(issues.size() == 2);
}

TEST_CASE("ConversationState advances through linear and choice nodes") {
    const auto document = ConversationLoader::loadFromString(R"json(
        {
          "nodes": {
            "start": { "next": "choice" },
            "choice": {
              "choices": [
                { "text": "A", "next": "end_a" },
                { "text": "B", "next": "end_b" }
              ]
            },
            "end_a": { "next": null },
            "end_b": { "next": null }
          }
        }
    )json");

    ConversationState state(document);
    REQUIRE(state.currentNodeId() == "start");
    REQUIRE(state.advance());
    REQUIRE(state.currentNodeId() == "choice");
    REQUIRE(state.choose(1));
    REQUIRE(state.currentNodeId() == "end_b");
    REQUIRE_FALSE(state.advance());
    REQUIRE(state.isComplete());
}
