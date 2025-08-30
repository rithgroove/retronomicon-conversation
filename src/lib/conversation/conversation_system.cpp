#include "retronomicon/lib/conversation/conversation_system.h"
#include "retronomicon/lib/conversation/vn_textbox_component.h"
#include <iostream>

namespace retronomicon::lib::conversation{

    /**
     * @brief method to update all component
     * 
     * @param dt time interval since last update
     * @param entity the parent entity, will call this method recursively
     */
    void ConversationSystem::update(float dt, retronomicon::lib::core::Entity* entity){
        auto animation = entity->getComponent<VNTextBoxComponent>();
        if (animation){
            animation->update(dt);
        }

        for (Entity* obj : entity->getChilds()) {
            // render logic
             this->update(dt,obj);
        }
    }
}

