#pragma once

#include <string>

namespace retronomicon::conversation {

struct Action {
    std::string type;
    std::string target;
    std::string value;
    float duration = 0.0f;
};

} // namespace retronomicon::conversation
