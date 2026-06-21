#include "retronomicon/conversation/conversation_document.h"

#include <utility>

namespace retronomicon::conversation {

void ConversationDocument::setStartNodeId(std::string id) {
    m_startNodeId = std::move(id);
}

const std::string& ConversationDocument::getStartNodeId() const {
    return m_startNodeId;
}

void ConversationDocument::addBackground(std::string id, std::string path) {
    m_backgrounds[std::move(id)] = std::move(path);
}

const ConversationDocument::BackgroundMap& ConversationDocument::getBackgrounds() const {
    return m_backgrounds;
}

void ConversationDocument::addNode(ConversationNode node) {
    m_nodes[node.id] = std::move(node);
}

bool ConversationDocument::hasNode(const std::string& id) const {
    return m_nodes.find(id) != m_nodes.end();
}

const ConversationNode* ConversationDocument::findNode(const std::string& id) const {
    const auto it = m_nodes.find(id);
    return it == m_nodes.end() ? nullptr : &it->second;
}

const ConversationDocument::NodeMap& ConversationDocument::getNodes() const {
    return m_nodes;
}

std::vector<ValidationIssue> ConversationDocument::validate() const {
    std::vector<ValidationIssue> issues;

    if (m_nodes.empty()) {
        issues.push_back({"conversation contains no nodes"});
        return issues;
    }

    if (!hasNode(m_startNodeId)) {
        issues.push_back({"start node '" + m_startNodeId + "' does not exist"});
    }

    for (const auto& [id, node] : m_nodes) {
        if (node.id.empty()) {
            issues.push_back({"node has an empty id"});
        }

        if (!node.background.empty() && m_backgrounds.find(node.background) == m_backgrounds.end()) {
            issues.push_back({"node '" + id + "' references unknown background '" + node.background + "'"});
        }

        if (node.next.has_value() && !hasNode(*node.next)) {
            issues.push_back({"node '" + id + "' references unknown next node '" + *node.next + "'"});
        }

        for (const auto& choice : node.choices) {
            if (!hasNode(choice.next)) {
                issues.push_back({"node '" + id + "' choice '" + choice.text + "' references unknown next node '" + choice.next + "'"});
            }
        }
    }

    return issues;
}

} // namespace retronomicon::conversation
