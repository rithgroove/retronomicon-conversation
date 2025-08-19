#include "retronomicon/lib/conversation/conversation_scene.h"
#include <iostream>

namespace retronomicon::lib::conversation{
    ConversationScene::ConversationScene()
    : Scene("conversation"),m_currentNode(nullptr) {}

    void ConversationScene::init() {
        if (!m_nodes.empty()) {
            // Default to the node called "start" if it exists
            auto it = m_nodes.find("start");
            if (it != m_nodes.end()) {
                m_currentNode = &it->second;
            }
        }
    }

    void ConversationScene::update(float dt) {
        // Example: simple debug print of current node
        if (m_currentNode) {
            std::cout << m_currentNode->speaker << ": " 
                      << m_currentNode->text << std::endl;
        }
    }

    // void ConversationScene::render(SDL_Renderer* renderer) {
    //     // For now, placeholder. You’ll eventually render portraits + text box here.
    // }

    void ConversationScene::setCurrentNode(const std::string& nodeId) {
        auto it = m_nodes.find(nodeId);
        if (it != m_nodes.end()) {
            m_currentNode = &it->second;
        }
    }

    ConversationNode* ConversationScene::getCurrentNode() {
        return m_currentNode;
    }

}

