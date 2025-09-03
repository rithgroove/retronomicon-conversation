#include "retronomicon/lib/conversation/conversation_loader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "retronomicon/lib/conversation/data/conversation_node.h"
#include "retronomicon/lib/conversation/data/choice.h"
#include "retronomicon/lib/conversation/data/action.h"
#include "retronomicon/lib/graphic/sprite_component.h"
namespace retronomicon::lib::conversation {
    using json = nlohmann::json;
    using retronomicon::lib::conversation::data::ConversationNode;
    using retronomicon::lib::conversation::data::Choice;
    using retronomicon::lib::conversation::data::Action;
    using retronomicon::lib::graphic::SpriteComponent;

    std::shared_ptr<ConversationScene> ConversationLoader::loadFromJSON(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[ConversationLoader] Failed to open file: " << filename << std::endl;
            return nullptr;
        }

        json j;
        file >> j;
        return parseJson(j);
    }

    std::shared_ptr<ConversationScene> ConversationLoader::loadFromString(const std::string& jsonString) {
        json j;
        try {
            j = json::parse(jsonString);
        } catch (const json::parse_error& e) {
            std::cerr << "[ConversationLoader] Failed to parse JSON string: " << e.what() << std::endl;
            return nullptr;
        }
        return parseJson(j);
    }

    std::shared_ptr<ConversationScene> ConversationLoader::loadFromTextAsset(
        const std::shared_ptr<retronomicon::lib::asset::TextAsset> asset) 
    {
        if (!asset) {
            std::cerr << "[ConversationLoader] Null TextAsset provided" << std::endl;
            return nullptr;
        }
        return loadFromString(asset->getContent());
    }

    std::shared_ptr<ConversationScene> ConversationLoader::parseJson(const json& j) {
        auto scene = std::make_shared<ConversationScene>();
        if (j.contains("background")){
            for (auto it = j["background"].begin(); it != j["background"].end(); ++it)
            {
                std::cout << "[Loader] "<<it.key() <<" : "<< it.value() <<std::endl;
                scene->loadBackground(it.value(),it.key());
            }
        }
        if (j.contains("nodes")) {
            for (auto& [id, nodeData] : j["nodes"].items()) {
                ConversationNode node;
                node.setId(id);

                if (nodeData.contains("background")) 
                    node.setBackground(nodeData["background"].get<std::string>());
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
}
