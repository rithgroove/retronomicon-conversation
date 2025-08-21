#pragma once
#include <string>
#include <vector>
#include <optional>

namespace retronomicon::lib::conversation {

struct Action {
    std::string type;   // e.g. "expression", "sound", "shake"
    std::string target; // e.g. "Hero", "screen"
    std::string value;  // e.g. "sad", "footstep.wav"
    float duration = 0.0f; // optional
};

struct ConversationNode {
    std::string id;
    std::string speaker;
    std::string text;
    std::string expression;
    std::vector<Choice> choices;
    std::optional<std::string> next;
    std::vector<Action> actions;
};

} // namespace retronomicon::lib::conversation
