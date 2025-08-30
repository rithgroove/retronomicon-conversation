#pragma once
#include "retronomicon/lib/core/scene.h"
#include "retronomicon/lib/asset/image_asset.h"
#include "retronomicon/lib/asset/font_asset.h"
#include "retronomicon/lib/engine/game_engine.h"
#include "conversation_node.h"
#include <unordered_map>

namespace retronomicon::lib::conversation {
    using retronomicon::lib::asset::ImageAsset;
    using retronomicon::lib::asset::FontAsset;
    using retronomicon::lib::engine::GameEngine;
class ConversationScene : public retronomicon::lib::core::Scene {
public:
    ConversationScene();
    void init() override;
    // void update(float dt) override;
    // void render() override{}
    void reset() override{}
    void shutdown() override{}


    void setCurrentNode(const std::string& nodeId);
    ConversationNode* getCurrentNode();
    std::unordered_map<std::string, ConversationNode> m_nodes;
    std::shared_ptr<ImageAsset> m_nineSliceImage = nullptr;
    std::shared_ptr<FontAsset> m_font = nullptr;
    GameEngine* m_engine;


private:
    ConversationNode* m_currentNode;
    void setupSystem();

    };
 
} // namespace retronomicon::lib::conversation
