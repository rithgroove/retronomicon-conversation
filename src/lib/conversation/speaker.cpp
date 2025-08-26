#include "retronomicon/lib/conversation/speaker.h"
#include "retronomicon/lib/animation/animation_component.h"
#include <iostream>

namespace retronomicon::lib::conversation {

void Speaker::setExpression(const std::string& expression) {
    m_currentExpression = expression;

    if (!m_entity) return;

    auto anim = m_entity->getComponent<retronomicon::lib::animation::AnimationComponent>();
    if (anim) {
        anim->changeClip(expression);  // assumes AnimationManager supoprts named states
    } else {
        std::cout << "[Speaker] Entity has no AnimationManager, cannot set expression "
                  << expression << "\n";
    }
}

std::string Speaker::toString() const {
    return "Speaker[" + m_id + "] expression=" + m_currentExpression;
}

} // namespace retronomicon::lib::conversation
