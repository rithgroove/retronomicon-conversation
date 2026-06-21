#include "retronomicon/conversation/conversation_state.h"

namespace retronomicon::conversation {

ConversationState::ConversationState(const ConversationDocument& document)
    : m_document(document), m_currentNodeId(document.getStartNodeId()) {
    m_complete = (current() == nullptr);
}

const ConversationNode* ConversationState::current() const {
    if (m_complete) {
        return nullptr;
    }
    return m_document.findNode(m_currentNodeId);
}

const std::string& ConversationState::currentNodeId() const {
    return m_currentNodeId;
}

bool ConversationState::isComplete() const {
    return m_complete;
}

bool ConversationState::advance() {
    const auto* node = current();
    if (!node || !node->next.has_value()) {
        m_complete = true;
        return false;
    }
    return jumpTo(*node->next);
}

bool ConversationState::choose(std::size_t choiceIndex) {
    const auto* node = current();
    if (!node || choiceIndex >= node->choices.size()) {
        return false;
    }
    return jumpTo(node->choices[choiceIndex].next);
}

bool ConversationState::jumpTo(const std::string& nodeId) {
    if (!m_document.hasNode(nodeId)) {
        return false;
    }

    m_currentNodeId = nodeId;
    m_complete = false;
    return true;
}

} // namespace retronomicon::conversation
