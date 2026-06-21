#include "retronomicon/conversation/conversation_node.h"

namespace retronomicon::conversation {

bool ConversationNode::isTerminal() const {
    return !next.has_value() && choices.empty();
}

} // namespace retronomicon::conversation
