#include "retronomicon/lib/conversation/conversation_loader.h"
#include "retronomicon/lib/conversation/conversation_node.h"
#include "retronomicon/lib/conversation/choice.h"
#include "retronomicon/lib/conversation/action.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using namespace retronomicon::lib::conversation;
using json = nlohmann::json;

ConversationScene* ConversationLoader::loadFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ConversationLoader] Failed to open file: " << filename << std::endl;
        return nullptr;
    }

    json j;
    file >> j;

    auto* scene = new ConversationScene();

    if (j.contains("nodes")) {
        for (auto& [id, nodeData] : j["nodes"].items()) {
            ConversationNode node;
            node.id = id;

            if (nodeData.contains("speaker")) node.speaker = nodeData["speaker"];
            if (nodeData.contains("text")) node.text = nodeData["text"];
            if (nodeData.contains("expression")) node.expression = nodeData["expression"];

            if (nodeData.contains("next") && !nodeData["next"].is_null()) {
                node.next = nodeData["next"];
            }

            if (nodeData.contains("choices")) {
                for (auto& choiceData : nodeData["choices"]) {
                    Choice c(choiceData["text"],choiceData["next"]);
                    node.choices.push_back(c);
                }
            }

            if (nodeData.contains("actions")) {
                std::cout<< "To Do : Actions"<<std::endl;
                for (auto& actionData : nodeData["actions"]) {
                    Action a(actionData.value("type", ""),actionData.value("target", ""),actionData.value("value", ""),actionData.value("duration", 0.0f));
                    node.actions.push_back(a);
                }
            }

            scene->m_nodes[id] = node;
        }
    }

    return scene;
}
