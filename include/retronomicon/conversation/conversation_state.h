#pragma once

#include "retronomicon/conversation/conversation_document.h"

#include <cstddef>
#include <string>

namespace retronomicon::conversation {

class ConversationState {
public:
    explicit ConversationState(const ConversationDocument& document);

    const ConversationNode* current() const;
    const std::string& currentNodeId() const;
    bool isComplete() const;

    bool advance();
    bool choose(std::size_t choiceIndex);
    bool jumpTo(const std::string& nodeId);

private:
    const ConversationDocument& m_document;
    std::string m_currentNodeId;
    bool m_complete = false;
};

} // namespace retronomicon::conversation
