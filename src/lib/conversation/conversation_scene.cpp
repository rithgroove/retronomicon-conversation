#include "retronomicon/lib/conversation/conversation_scene.h"
#include "retronomicon/lib/conversation/conversation_system.h"
#include "retronomicon/lib/ui/nine_slice_panel_component.h"
#include "retronomicon/lib/graphic/render_system.h"
#include "retronomicon/lib/input/input_system.h"
#include "retronomicon/lib/conversation/input/conversation_input_component.h"
#include <iostream>

namespace retronomicon::lib::conversation{
    using retronomicon::lib::ui::NineSlicePanelComponent;
    using retronomicon::lib::graphic::Window;
    using retronomicon::lib::graphic::RenderSystem;
    using retronomicon::lib::conversation::input::ConversationInputComponent;
    ConversationScene::ConversationScene()
    : Scene("conversation"),m_currentNode(nullptr) {}

    void ConversationScene::init() {
        std::cout<<"init kepanggil" << std::endl;
        this->setupSystem();
        if (!m_font){
            if (m_assetManager){
                this->loadFont();
            }
        }

        // ----------------- Panel size (customize later)--------------------
        int windowWidth = Window::getWidth();
        int windowHeight = Window::getHeight();
        int panelWidth = windowWidth/2;
        int panelHeight = 200;
        this->loadBackgrounds();

        this->addComponent<ConversationInputComponent>();
        if (!m_nodes.empty()) {
            // ----------------- Find Starting Node --------------------
            auto it = m_nodes.find("start");
            if (it != m_nodes.end()) {
                m_currentNode = &it->second;
            }

            // ----------------- Setup Background --------------------
            this->setupBackground();

            // ----------------- Setup Character --------------------
            this->setupCharacter(m_currentNode->getSpeaker());

            // ----------------- Setup VNTextBox --------------------
            this->setupVNTextBox();

            this->start();
            // this->m_childEntities.push_back(background);
        }
    }

    void ConversationScene::loadBackgrounds(){
        for (const auto& [key, value] : m_backgroundPaths) {
            std::cout <<"[Conversation Scene] Init background image '" <<key<<"' = '" <<value<<"'"<<std::endl;
            m_backgrounds[key] = m_assetManager->loadImage(value,key);
        }
    }

    void ConversationScene::setBackground(std::string name){
        auto backgroundIterator = m_backgrounds.find(name);
        if (backgroundIterator == m_backgrounds.end() || !(backgroundIterator->second) ){
            std::cout << "[ConversationScene] Background not found or failed to load: " << name << std::endl;
            return; // or fallback to default background
        }else{
            if (m_backgroundComponent){
                m_backgroundComponent->changeAsset(backgroundIterator->second);
            }
        }
    }

    void ConversationScene::setupCharacter(std::string name){
        // ----------------- Panel size (customize later)--------------------
        int windowWidth = Window::getWidth();
        int windowHeight = Window::getHeight();
        int panelWidth = windowWidth;
        int panelHeight = 200;

        // ----------------- Get Character DB (customize later)--------------------
        auto cdb = m_engine->getCharacterDatabase();

        // ----------------- Get Character DB (customize later)--------------------
        auto character = cdb->getCharacter(name);
        auto characterVNEntity = character->getModuleEntity("retronomicon-conversation");


        if (characterVNEntity){
            if (m_mainCharaComponent){
                //remove previous mainCharacComponent 
                this->removeChildEntity(m_mainCharaComponent->getOwner());
            }
            auto character_transform =  characterVNEntity->getComponent<TransformComponent>();
            character_transform->setPosition(windowWidth/2.0f,windowHeight);
            character_transform->setAnchor(0.5f,1.0f);  
            character->setActiveModule("retronomicon-conversation");
            characterVNEntity->start();
            this->addChildEntity(characterVNEntity);
            // hot fix. will need to rethink render position
            if (m_textBoxComponent){
                this->removeChildEntity(m_textBoxComponent->getOwner());
                this->addChildEntity(m_textBoxComponent->getOwner());
            }
            m_mainCharaComponent = characterVNEntity->getComponent<AnimationComponent>();
        }else{
            std::cout << "###########################\nNULL KK\n###########################\n"<<std::endl;
        }
    }
    

    void ConversationScene::setupVNTextBox(){
        // ----------------- Panel size (customize later)--------------------
        int windowWidth = Window::getWidth();
        int windowHeight = Window::getHeight();
        int panelWidth = windowWidth;
        int panelHeight = 200;

        // ----------------- Setup VN TextBox --------------------
        Entity* textbox = new Entity("VN Text Box");

        //-------- Build Transform Component for textbox ---------------
        TransformComponent* backgroundTransform = textbox->addComponent<TransformComponent>(windowWidth/2.0,windowHeight,0.0f,1.0f,1.0f);
        backgroundTransform->setAnchor(0.5f,1.0f); // setup anchor bottom mid

        //-------- Build vn textbox component ---------------
        m_textBoxComponent = textbox->addComponent<VNTextBoxComponent>(m_font, 800,20);
        m_textBoxComponent->setNode(m_currentNode);

        //-------- Build nine slice component ---------------
        auto* nineSlice = textbox->addComponent<NineSlicePanelComponent>();
        nineSlice->setImageAsset(this->m_nineSliceImage);
        nineSlice->setSlices(16, 16, 16, 16); // default slice sizes, adjust as needed
        nineSlice->setSize(panelWidth, panelHeight);

        //--------- initiate background -------------------
        textbox->start();

        //--------- add background as child entity -------------------
        this->addChildEntity(textbox);
    }
    
    void ConversationScene::setupBackground(){
        //-------- Create background entity ---------------
        Entity* imageBackground = new Entity("VN Background");

        //-------- Get active background name in current node ---------------
        const std::string& bgKey = m_currentNode->getBackground();

        //-------- Get the asset ---------------
        std::shared_ptr<ImageAsset> backgroundAsset = m_backgrounds[bgKey];

        //-------- Recalculate scaling ---------------
        int windowWidth = Window::getWidth();
        int windowHeight = Window::getHeight();
        int imageWidth = backgroundAsset->getWidth();
        int imageHeight = backgroundAsset->getHeight();
        
        float scaling = float(windowWidth) / float(imageWidth);
        if (float(windowHeight)/float(imageHeight)> scaling){
            scaling = float(windowHeight)/float(imageHeight);
        }

        //-------- Build Sprite Component for background ---------------
        m_backgroundComponent = imageBackground->addComponent<SpriteComponent>(backgroundAsset);

        //-------- Build Transform Component for background ---------------
        TransformComponent* imageBackgroundTransform = imageBackground->addComponent<TransformComponent>(windowWidth/2.0f,windowHeight/2.0f,0.0f,scaling,scaling);

        //--------- initiate background -------------------
        imageBackground->start();

        //--------- add background as child entity -------------------
        this->addChildEntity(imageBackground);
    }


    void ConversationScene::setCurrentNode(const std::string& nodeId) {
 
        //--------- find the target node -------------------
        auto it = m_nodes.find(nodeId);
        if (it != m_nodes.end()) {
            //--------- set current node target node -------------------
            m_currentNode = &it->second;

            //--------- set textbox node to use the newly updated m_currentNode -------------------
            m_textBoxComponent->setNode(m_currentNode);

            //--------- check if the background is empty -------------------
            if (!m_currentNode->getBackground().empty()) {
                this->setBackground(m_currentNode->getBackground());
            }

            //--------- check if the character is empty -------------------
            if (!m_currentNode->getSpeaker().empty()) {
                this->setupCharacter(m_currentNode->getSpeaker());
            }

            //--------- change expression -------------------
            if (!m_currentNode->getExpression().empty()) {
                const auto& expression = m_currentNode->getExpression();
                m_mainCharaComponent->changeClip(expression);
            }
        }
    }

    void ConversationScene::registerBackground(std::string filePath,std::string key){
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

