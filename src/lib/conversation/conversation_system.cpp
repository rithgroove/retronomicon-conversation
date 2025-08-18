#include "retronomicon/lib/conversation/conversation_system.h"
#include <iostream>

using namespace retronomicon::lib::conversation;

void ConversationSystem::update(float dt, ConversationScene* scene) {
    if (!scene) return;

    auto* node = scene->getCurrentNode();
    if (!node) return;

    // Example: process choices (in real use, tie into InputSystem)
    if (!node->choices.empty()) {
        std::cout << "Choices available:\n";
        for (size_t i = 0; i < node->choices.size(); i++) {
            std::cout << i << ") " << node->choices[i].text << "\n";
        }

        // For demo: always auto-pick the first choice
        scene->setCurrentNode(node->choices[0].next);
    } else if (node->next.has_value()) {
        scene->setCurrentNode(node->next.value());
    }
}

void ConversationSystem::render(SDL_Renderer* renderer, ConversationScene* scene) {
    // Eventually: draw text, portraits, etc.
    // For now, debug text is printed in update().
}
