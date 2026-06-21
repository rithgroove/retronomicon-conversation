#pragma once

#include "retronomicon/conversation/conversation_node.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace retronomicon::conversation {

struct ValidationIssue {
    std::string message;
};

class ConversationDocument {
public:
    using BackgroundMap = std::unordered_map<std::string, std::string>;
    using NodeMap = std::unordered_map<std::string, ConversationNode>;

    void setStartNodeId(std::string id);
    const std::string& getStartNodeId() const;

    void addBackground(std::string id, std::string path);
    const BackgroundMap& getBackgrounds() const;

    void addNode(ConversationNode node);
    bool hasNode(const std::string& id) const;
    const ConversationNode* findNode(const std::string& id) const;
    const NodeMap& getNodes() const;

    std::vector<ValidationIssue> validate() const;

private:
    std::string m_startNodeId = "start";
    BackgroundMap m_backgrounds;
    NodeMap m_nodes;
};

} // namespace retronomicon::conversation
