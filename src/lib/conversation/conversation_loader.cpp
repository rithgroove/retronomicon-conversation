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
            node.setId(id);

            if (nodeData.contains("speaker")) 
                node.setSpeaker(nodeData["speaker"].get<std::string>());
            if (nodeData.contains("text")) 
                node.setText(nodeData["text"].get<std::string>());
            if (nodeData.contains("expression")) 
                node.setExpression(nodeData["expression"].get<std::string>());

            if (nodeData.contains("next") && !nodeData["next"].is_null()) {
                node.setNext(nodeData["next"].get<std::string>());
            }

            if (nodeData.contains("choices")) {
                std::vector<Choice> choices;
                for (auto& choiceData : nodeData["choices"]) {
                    Choice c(choiceData["text"].get<std::string>(),
                             choiceData["next"].get<std::string>());
                    choices.push_back(c);
                }
                node.setChoices(choices);
            }

            if (nodeData.contains("actions")) {
                std::cout << "To Do : Actions" << std::endl;
                std::vector<Action> actions;
                for (auto& actionData : nodeData["actions"]) {
                    Action a(
                        actionData.value("type", ""),
                        actionData.value("target", ""),
                        actionData.value("value", ""),
                        actionData.value("duration", 0.0f)
                    );
                    actions.push_back(a);
                }
                node.setActions(actions);
            }

            scene->m_nodes[id] = node;
        }
    }


    return scene;
}
