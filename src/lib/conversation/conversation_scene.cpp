#include "retronomicon/lib/conversation/conversation_scene.h"
#include "retronomicon/lib/conversation/vn_textbox_component.h"
#include "retronomicon/lib/conversation/conversation_system.h"
#include "retronomicon/lib/ui/nine_slice_panel_component.h"
#include "retronomicon/lib/graphic/render_system.h"
#include <iostream>

namespace retronomicon::lib::conversation{
    using retronomicon::lib::ui::NineSlicePanelComponent;
    using retronomicon::lib::graphic::Window;
    using retronomicon::lib::graphic::RenderSystem;
    ConversationScene::ConversationScene()
    : Scene("conversation"),m_currentNode(nullptr) {}

    void ConversationScene::init() {
        std::cout<<"init kepanggil" << std::endl;
        this->setupSystem();
        if (!m_font){
            if (m_assetManager){
                
            }
        }

        if (!m_nodes.empty()) {
            std::cout<<"m_nodes ga empty" << std::endl;
            // Default to the node called "start" if it exists
            auto it = m_nodes.find("start");
            if (it != m_nodes.end()) {
                m_currentNode = &it->second;
            }

            Entity* background = new Entity("VN Text Box");
            // ----------------- Panel size (customize later)--------------------
            int windowWidth = Window::getWidth();
            int windowHeight = Window::getHeight();
            int panelWidth = windowWidth/2;
            int panelHeight = 200;

            //-------- Build Transform Component for background ---------------
            TransformComponent* backgroundTransform = background->addComponent<TransformComponent>(windowWidth/2.0,windowHeight,0.0f,1.0f,1.0f);
            backgroundTransform->setAnchor(0.5f,1.0f);
            backgroundTransform->setRotation(0.0f);

            //-------- Build Sprite Component for background ---------------
            auto* nineSlice = background->addComponent<NineSlicePanelComponent>();
            nineSlice->setImageAsset(this->m_nineSliceImage);
            nineSlice->setSlices(16, 16, 16, 16); // default slice sizes, adjust as needed
            nineSlice->setSize(panelWidth, panelHeight);

            auto* vnTextBox = background->addComponent<VNTextBoxComponent>(m_font, nineSlice, 800,20);
            vnTextBox->setNode(m_currentNode);
            vnTextBox->m_transform = backgroundTransform;

            //--------- initiate background -------------------
            background->start();

            //--------- add background as child entity -------------------
            this->addChildEntity(background);
            // this->m_childEntities.push_back(background);
        }
    }

    // void ConversationScene::update(float dt) {
    //     // Example: simple debug print of current node
    //     if (m_currentNode) {
    //         std::cout << m_currentNode->getSpeaker() << ": " 
    //                   << m_currentNode->getText() << std::endl;
    //     }
    // }

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


    void ConversationScene::setupSystem(){
        //setup input map and update inputstate to use thesep
        // auto inputState = m_engine->getInputState();
        // inputState->setInputMap(this->generateInputMap());

        // setup systems
        std::cout << "[Splash Scene] setup systems" <<std::endl;

        // setup animation system used for timer until changing to next scene
        // this->addSystem(std::make_unique<AnimationSystem>());
        this->addSystem(std::make_unique<ConversationSystem>());
        // setup render system used to draw to screen
        this->addSystem(std::make_unique<RenderSystem>(m_engine->getRenderer()));
        // setup scene change system to trigger scene change to the next one
        // this->addSystem(std::make_unique<SceneChangeSystem>(m_engine));
        // setup input system to skip to next scene
        // this->addSystem(std::make_unique<InputSystem>(inputState));
        // this->addSystem(std::make_unique<MenuInteractionSystem>(inputState));
        // this->addSystem(std::make_unique<ExitGameSystem>(m_engine));
    }

}

