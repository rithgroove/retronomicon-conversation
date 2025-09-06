#include "retronomicon/lib/conversation/input/conversation_input_component.h"
#include "retronomicon/lib/scene/scene_change_component.h"
#include "retronomicon/lib/core/entity.h"
namespace retronomicon::lib::conversation::input{
    using retronomicon::lib::scene::SceneChangeComponent;
    using retronomicon::lib::core::Entity;

    void ConversationInputComponent::start() {
        m_conversationScene = static_cast<ConversationScene*>(this->getOwner());
    }

    void ConversationInputComponent::updateFromState(std::shared_ptr<InputState> state, float dt){
        if (state->wasActionJustPressed("confirm")){
            if (m_conversationScene->isCurrentTextboxFinished()){
                auto* currentNode = m_conversationScene->getCurrentNode();
                if (currentNode) {
                    if (auto next = currentNode->getNext()) { // this is an std::optional<std::string>
                        m_conversationScene->setCurrentNode(*next); // dereference to get the std::string
                    }
                }                
            }else{
                m_conversationScene->finishCurrenTextbox();
            }


        }
    }


}