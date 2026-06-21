#include "retronomicon/conversation/conversation_loader.h"

#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <utility>

namespace retronomicon::conversation {
namespace {

using json = nlohmann::json;

std::string optionalString(const json& object, const char* key) {
    if (!object.contains(key) || object.at(key).is_null()) {
        return {};
    }
    return object.at(key).get<std::string>();
}

ConversationDocument parseDocument(const json& root) {
    ConversationDocument document;
    document.setStartNodeId(root.value("start", "start"));

    if (root.contains("background")) {
        if (!root.at("background").is_object()) {
            throw std::runtime_error("conversation background must be an object");
        }

        for (const auto& [id, path] : root.at("background").items()) {
            document.addBackground(id, path.get<std::string>());
        }
    }

    if (!root.contains("nodes") || !root.at("nodes").is_object()) {
        throw std::runtime_error("conversation nodes must be an object");
    }

    for (const auto& [id, nodeData] : root.at("nodes").items()) {
        ConversationNode node;
        node.id = id;
        node.background = optionalString(nodeData, "background");
        node.speaker = optionalString(nodeData, "speaker");
        node.text = optionalString(nodeData, "text");
        node.expression = optionalString(nodeData, "expression");

        if (nodeData.contains("next") && !nodeData.at("next").is_null()) {
            node.next = nodeData.at("next").get<std::string>();
        }

        if (nodeData.contains("choices")) {
            for (const auto& choiceData : nodeData.at("choices")) {
                node.choices.push_back({
                    choiceData.value("text", ""),
                    choiceData.at("next").get<std::string>()
                });
            }
        }

        if (nodeData.contains("actions")) {
            for (const auto& actionData : nodeData.at("actions")) {
                node.actions.push_back({
                    actionData.value("type", ""),
                    actionData.value("target", ""),
                    actionData.value("value", ""),
                    actionData.value("duration", 0.0f)
                });
            }
        }

        document.addNode(std::move(node));
    }

    return document;
}

} // namespace

ConversationDocument ConversationLoader::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open conversation file: " + path);
    }

    json root;
    file >> root;
    return parseDocument(root);
}

ConversationDocument ConversationLoader::loadFromString(const std::string& content) {
    return parseDocument(json::parse(content));
}

} // namespace retronomicon::conversation
