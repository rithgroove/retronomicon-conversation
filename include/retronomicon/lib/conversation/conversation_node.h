#pragma once
#include <string>
#include <vector>
#include <optional>
#include "choice.h"
#include "action.h"
namespace retronomicon::lib::conversation {

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
