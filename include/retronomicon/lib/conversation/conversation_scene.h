#pragma once
#include "retronomicon/lib/core/scene.h"
#include "conversation_node.h"
#include <unordered_map>

namespace retronomicon::lib::conversation {

class ConversationScene : public retronomicon::lib::core::Scene {
public:
    ConversationScene();
    void init() override;
    void update(float dt) override;
    void render() override{}
    void reset() override{}
    void shutdown() override{}


    void setCurrentNode(const std::string& nodeId);
    ConversationNode* getCurrentNode();
    std::unordered_map<std::string, ConversationNode> m_nodes;

private:
    ConversationNode* m_currentNode;
};

} // namespace retronomicon::lib::conversation
