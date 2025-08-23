#include "retronomicon/lib/conversation/conversation_system.h"
#include <iostream>

using namespace retronomicon::lib::conversation;

void ConversationSystem::update(float dt, ConversationScene* scene) {
    if (!scene) return;

    auto* node = scene->getCurrentNode();
    if (!node) return;

    const auto& choices = node->getChoices();
    if (!choices.empty()) {
        std::cout << "Choices available:\n";
        for (size_t i = 0; i < choices.size(); i++) {
            std::cout << i << ") " << choices[i].getText() << "\n";
        }

        // For demo: always auto-pick the first choice
        scene->setCurrentNode(choices[0].getNext());
    } else if (node->getNext().has_value()) {
        scene->setCurrentNode(node->getNext().value());
    }
}

void ConversationSystem::render(SDL_Renderer* renderer, ConversationScene* scene) {
    // Eventually: draw text, portraits, etc.
    // For now, debug text is printed in update().
}
