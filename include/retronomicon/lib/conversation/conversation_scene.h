#pragma once
#include "retronomicon/lib/engine/game_engine.h"
#include "retronomicon/lib/core/scene.h"
#include "retronomicon/lib/asset/asset_manager.h"
#include "retronomicon/lib/asset/image_asset.h"
#include "retronomicon/lib/asset/font_asset.h"
#include "retronomicon/lib/engine/game_engine.h"
#include "retronomicon/lib/conversation/data/conversation_node.h"
#include "retronomicon/lib/graphic/sprite_component.h"
#include "retronomicon/lib/animation/animation_component.h"
#include "vn_textbox_component.h"
#include "retronomicon/lib/input/input_system.h"
#include <unordered_map>

namespace retronomicon::lib::conversation {
    using retronomicon::lib::asset::ImageAsset;
    using retronomicon::lib::asset::AssetManager;
    using retronomicon::lib::asset::FontAsset;
    using retronomicon::lib::engine::GameEngine;
    using retronomicon::lib::conversation::data::ConversationNode;
    using retronomicon::lib::input::InputSystem;
    using retronomicon::lib::graphic::SpriteComponent;
    using retronomicon::lib::animation::AnimationComponent;
    class VNTextboxComponent;
    class ConversationScene : public retronomicon::lib::core::Scene {
    public:
        ConversationScene();
        void init() override;
        // void update(float dt) override;
        // void render() override{}
        void reset() override{}
        void shutdown() override{}

        void setEngine(GameEngine* engine) noexcept{
            m_engine= engine;
            m_assetManager = engine->getAssetManager();
        }

        void changeFont(std::string path,std::string name, int size){
            m_fontPath = m_fontPath;
            m_fontName = name;
            m_fontSize = size;
            loadFont();
        }

        void loadFont(){
            if (m_assetManager){
                m_font = m_assetManager->loadFont(m_fontPath,m_fontName,m_fontSize);
            }else{
                std::cout << "[ConversationScene] AssetManager is not set, have you called setEngine yet?"<<std::endl;
            }            
        }

        void setTextBoxBackground(std::string path, std::string name){
            m_nineSliceImagePath = path;
            m_nineSliceName = name;           
            loadTextBoxBackground();
        }
        void loadTextBoxBackground(){
            if (m_assetManager){
                m_nineSliceImage = m_assetManager->loadImage(m_nineSliceImagePath,m_nineSliceName);
            }else{
                std::cout << "[ConversationScene] AssetManager is not set, have you called setEngine yet?"<<std::endl;
            }            
        }
        void registerBackground(std::string path, std::string name);

        void setCurrentNode(const std::string& nodeId);
        ConversationNode* getCurrentNode(){
            return m_currentNode;
        }
        std::unordered_map<std::string, ConversationNode> m_nodes;
        void loadImage(std::string filePath,std::string key);

        bool isCurrentTextboxFinished(){
            return m_textBoxComponent->isFinished();
        }

        void finishCurrenTextbox(){
            m_textBoxComponent->skipToFullText();
        }
        void setBackground(std::string name);
    private:
        std::string m_fontPath = "asset/font/manaspc.ttf";
        std::string m_fontName = "manaspc.ttf";
        int m_fontSize = 22;

        std::shared_ptr<FontAsset> m_font = nullptr;

        std::string m_nineSliceImagePath = "asset/image/space2.png";
        std::string m_nineSliceName = "space2.png";
        std::shared_ptr<ImageAsset> m_nineSliceImage = nullptr;

        GameEngine* m_engine;
        std::shared_ptr<AssetManager> m_assetManager;

        ConversationNode* m_currentNode;
        VNTextBoxComponent *m_textBoxComponent;
        SpriteComponent *m_backgroundComponent;
        AnimationComponent *m_mainCharaComponent;

        std::unordered_map<std::string, std::shared_ptr<ImageAsset>> m_backgrounds;
        std::unordered_map<std::string, std::string> m_backgroundPaths;
        void setupVNTextBox();
        void setupSystem();
        InputMap* generateInputMap();
        void loadBackgrounds();
        void setupBackground();
        void setupCharacter(std::string name);
    };
 
} // namespace retronomicon::lib::conversation
