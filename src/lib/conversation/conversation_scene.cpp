#include "retronomicon/lib/conversation/conversation_scene.h"
#include "retronomicon/lib/conversation/conversation_system.h"
#include "retronomicon/lib/ui/nine_slice_panel_component.h"
#include "retronomicon/lib/graphic/sprite_component.h"
#include "retronomicon/lib/graphic/render_system.h"
#include "retronomicon/lib/input/input_system.h"
#include "retronomicon/lib/conversation/input/conversation_input_component.h"
#include <iostream>

namespace retronomicon::lib::conversation{
    using retronomicon::lib::ui::NineSlicePanelComponent;
    using retronomicon::lib::graphic::Window;
    using retronomicon::lib::graphic::RenderSystem;
    using retronomicon::lib::graphic::SpriteComponent;
    using retronomicon::lib::conversation::input::ConversationInputComponent;
    ConversationScene::ConversationScene()
    : Scene("conversation"),m_currentNode(nullptr) {}

    void ConversationScene::init() {
        std::cout<<"init kepanggil" << std::endl;
        this->setupSystem();
        if (!m_font){
            if (m_assetManager){
                
            }

        }


        // ----------------- Panel size (customize later)--------------------
        int windowWidth = Window::getWidth();
        int windowHeight = Window::getHeight();
        int panelWidth = windowWidth/2;
        int panelHeight = 200;



        this->addComponent<ConversationInputComponent>();
        if (!m_nodes.empty()) {

            for (const auto& [key, value] : m_backgroundPaths) {
                m_backgrounds[key] = m_assetManager->loadImage(value,key);
            }            
            std::cout<<"m_nodes ga empty" << std::endl;
            // Default to the node called "start" if it exists
            auto it = m_nodes.find("start");
            if (it != m_nodes.end()) {
                m_currentNode = &it->second;
            }


            Entity* imageBackground = new Entity("VN Text Box");

            //-------- Build Sprite Component for background ---------------
            std::cout << "[ConversationScene]current background " << m_currentNode->getBackground()<<std::endl;
            const std::string& bgKey = m_currentNode->getBackground();

            auto it2 = m_backgrounds.find(bgKey);


            if (it2 == m_backgrounds.end() || !(it2->second) ){
                std::cout << "[ConversationScene] Background not found or failed to load: " << bgKey << std::endl;
                return; // or fallback to default background
            }


            std::shared_ptr<ImageAsset> backgroundAsset = m_backgrounds[m_currentNode->getBackground()];
            std::cout << "[ConversationScene] backgroundAsset aman"<<std::endl;
            std::cout << backgroundAsset->to_string() <<std::endl;
            int imageWidth = backgroundAsset->getWidth();
            int imageHeight = backgroundAsset->getHeight();
            std::cout << "[ConversationScene] crash di get witdh/ height"<<std::endl;
            float scaling = float(windowWidth) / float(imageWidth);
            if (float(windowHeight)/float(imageHeight)> scaling){
                scaling = float(windowHeight)/float(imageHeight);
            }

            auto* spriteBackground = imageBackground->addComponent<SpriteComponent>(backgroundAsset);
            // imageBackground->setInvisible();

            // spriteBackground->setImageAsset(this->m_nineSliceImage);
            // spriteBackground->setSlices(16, 16, 16, 16); // default slice sizes, adjust as needed
            // spriteBackground->setSize(windowWidth, panelHeight);

            TransformComponent* imageBackgroundTransform = imageBackground->addComponent<TransformComponent>(windowWidth/2.0f,windowHeight/2.0f,0.0f,1.0f,1.0f);
            imageBackgroundTransform->setRotation(0.0f);

            //--------- initiate background -------------------
            imageBackground->start();

            //--------- add background as child entity -------------------
            this->addChildEntity(imageBackground);


            auto cdb = m_engine->getCharacterDatabase();
            auto jenna = cdb->getCharacter("jenna");
            auto jennaVNEntity = jenna->getModuleEntity("retronomicon-conversation");


            if (jennaVNEntity){
                auto jenna_transform =  jennaVNEntity->getComponent<TransformComponent>();
                jenna_transform->setPosition(windowWidth/2.0f,windowHeight);
                jenna_transform->setAnchor(0.5f,1.0f);  
                jenna->setActiveModule("retronomicon-conversation");
                jennaVNEntity->start();
                this->addChildEntity(jennaVNEntity);

            }else{
                std::cout << "###########################\nNULL KK\n###########################\n"<<std::endl;
            }
            // auto jenna_transform =  jennaVNEntity->getComponent<TransformComponent>();
            // jenna_transform->setPosition(windowWidth/2.0f,windowHeight);
            // jenna_transform->setAnchor(0.5f,1.0f);  


            Entity* background = new Entity("VN Text Box");

            //-------- Build Transform Component for background ---------------
            TransformComponent* backgroundTransform = background->addComponent<TransformComponent>(windowWidth/2.0,windowHeight,0.0f,1.0f,1.0f);
            backgroundTransform->setAnchor(0.5f,1.0f);
            backgroundTransform->setRotation(0.0f);



            //-------- Build nineslice Component for  text background ---------------
            m_textBoxComponent = background->addComponent<VNTextBoxComponent>(m_font, 800,20);
            m_textBoxComponent->setNode(m_currentNode);
            m_textBoxComponent->m_transform = backgroundTransform;

            auto* nineSlice = background->addComponent<NineSlicePanelComponent>();
            nineSlice->setImageAsset(this->m_nineSliceImage);
            nineSlice->setSlices(16, 16, 16, 16); // default slice sizes, adjust as needed
            nineSlice->setSize(panelWidth, panelHeight);

            m_textBoxComponent->setBackgroundPanel(nineSlice);

            //--------- initiate background -------------------
            background->start();

            //--------- add background as child entity -------------------
            this->addChildEntity(background);
            this->start();
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

    void ConversationScene::loadBackground(std::string filePath,std::string key){
        m_backgroundPaths[key] =filePath;
    }

    InputMap* ConversationScene::generateInputMap(){
        std::cout << "[Splash Scene] setup input map" <<std::endl;
        InputMap* inputMap = new InputMap();
        inputMap->bindAction(SDL_SCANCODE_SPACE, "confirm");
        inputMap->bindAction(SDL_SCANCODE_RETURN, "confirm");
        inputMap->bindAction(SDL_SCANCODE_A, "left");
        inputMap->bindAction(SDL_SCANCODE_W, "up");
        inputMap->bindAction(SDL_SCANCODE_S, "down");
        inputMap->bindAction(SDL_SCANCODE_D, "right");
        inputMap->bindAction(SDL_SCANCODE_ESCAPE,"quit");
        return inputMap;        
    }

    void ConversationScene::setupSystem(){
        //setup input map and update inputstate to use thesep
        auto inputState = m_engine->getInputState();
        inputState->setInputMap(this->generateInputMap());

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
        this->addSystem(std::make_unique<InputSystem>(inputState));
        // this->addSystem(std::make_unique<MenuInteractionSystem>(inputState));
        // this->addSystem(std::make_unique<ExitGameSystem>(m_engine));
    }

}

