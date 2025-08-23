#include "retronomicon/lib/conversation/conversation_node.h"

namespace retronomicon::lib::conversation {

    ConversationNode::ConversationNode() 
        : m_id(""),
          m_speaker(""),
          m_text(""),
          m_expression(""),
          m_choices(),
          m_next(std::nullopt),
          m_actions() {}

    ConversationNode::ConversationNode(
        std::string id,
        std::string speaker,
        std::string text,
        std::string expression,
        std::vector<Choice> choices,
        std::optional<std::string> next,
        std::vector<Action> actions)
        : m_id(std::move(id)),
          m_speaker(std::move(speaker)),
          m_text(std::move(text)),
          m_expression(std::move(expression)),
          m_choices(std::move(choices)),
          m_next(std::move(next)),
          m_actions(std::move(actions)) {}

} // namespace retronomicon::lib::conversation
