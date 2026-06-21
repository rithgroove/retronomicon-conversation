#pragma once

#include "retronomicon/conversation/conversation_document.h"

#include <string>

namespace retronomicon::conversation {

class ConversationLoader {
public:
    static ConversationDocument loadFromFile(const std::string& path);
    static ConversationDocument loadFromString(const std::string& content);
};

} // namespace retronomicon::conversation
