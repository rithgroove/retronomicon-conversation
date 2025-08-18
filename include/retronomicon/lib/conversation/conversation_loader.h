#pragma once
#include "conversation_scene.h"
#include <string>

namespace retronomicon::lib::conversation {

class ConversationLoader {
public:
    static ConversationScene* loadFromJSON(const std::string& filename);
};

} // namespace retronomicon::lib::conversation
