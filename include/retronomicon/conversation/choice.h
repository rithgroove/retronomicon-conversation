#pragma once

#include <string>

namespace retronomicon::conversation {

struct Choice {
    std::string text;
    std::string next;
};

} // namespace retronomicon::conversation
