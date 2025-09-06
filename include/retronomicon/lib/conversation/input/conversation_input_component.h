#pragma once

#include <string>
#include <memory>
#include "retronomicon/lib/input/input_component.h"
#include "retronomicon/lib/conversation/conversation_scene.h"
#include "retronomicon/lib/input/input_state.h"

namespace retronomicon::lib::conversation::input {
    using retronomicon::lib::input::InputState;
    using retronomicon::lib::conversation::ConversationScene;
    using retronomicon::lib::input::InputComponent;
    class ConversationInputComponent : public InputComponent {
        public:

            ConversationInputComponent() noexcept = default;

            void start() override;
            /// Call once per frame to update typewriter progression
            void updateFromState(std::shared_ptr<InputState> state, float dt) override;
        private:
            bool active = true;
            ConversationScene* m_conversationScene;
    };

} // namespace retronomicon::lib::scene::menu
