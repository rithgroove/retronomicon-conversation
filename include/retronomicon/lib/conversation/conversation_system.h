#pragma once
#include "conversation_scene.h"
#include "retronomicon/lib/core/system.h"

namespace retronomicon::lib::conversation {

class ConversationSystem : public retronomicon::lib::core::System {
    public:
        /**
         * @brief method to update all component
         * 
         * @param dt time interval since last update
         * @param objects the game objects (might change to Entity Later)
         */
        void update(float dt, retronomicon::lib::core::Entity* entities)  override;
    };

} // namespace retronomicon::lib::conversation
