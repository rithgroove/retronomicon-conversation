#pragma once
#include "conversation_scene.h"
#include "retronomicon/lib/core/system.h"

namespace retronomicon::lib::conversation {

class ConversationSystem : public retronomicon::lib::core::System {
public:
    void update(float dt, ConversationScene* scene);
    void render(SDL_Renderer* renderer, ConversationScene* scene);
};

} // namespace retronomicon::lib::conversation
