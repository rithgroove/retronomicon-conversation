#pragma once

#include "retronomicon/conversation/action.h"
#include "retronomicon/conversation/choice.h"

#include <optional>
#include <string>
#include <vector>

namespace retronomicon::conversation {

struct ConversationNode {
    std::string id;
    std::string background;
    std::string speaker;
    std::string text;
    std::string expression;
    std::vector<Choice> choices;
    std::optional<std::string> next;
    std::vector<Action> actions;

    bool isTerminal() const;
};

} // namespace retronomicon::conversation
