#pragma once

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

#include "conversation_scene.h"
#include "retronomicon/lib/asset/text_asset.h"

namespace retronomicon::lib::conversation {

    using retronomicon::lib::asset::TextAsset;
    using json = nlohmann::json;

    class ConversationLoader {
        public:
            /**
             * @brief Load a conversation scene directly from a JSON file.
             *
             * @param filename Path to the JSON file.
             * @return Pointer to a new ConversationScene, or nullptr on failure.
             */
            static ConversationScene* loadFromJSON(const std::string& filename);

            /**
             * @brief Load a conversation scene from a raw JSON string.
             *
             * @param jsonString JSON string containing conversation data.
             * @return Pointer to a new ConversationScene, or nullptr on failure.
             */
            static ConversationScene* loadFromString(const std::string& jsonString);

            /**
             * @brief Load a conversation scene from a TextAsset.
             *
             * @param asset Shared pointer to a TextAsset containing JSON conversation data.
             * @return Pointer to a new ConversationScene, or nullptr on failure.
             */
            static ConversationScene* loadFromTextAsset(const std::shared_ptr<TextAsset> asset);

        private:
            /**
             * @brief Internal helper to parse a JSON object into a ConversationScene.
             *
             * @param j JSON object already parsed.
             * @return Pointer to a new ConversationScene.
             */
            static ConversationScene* parseJson(const json& j);
    };

} // namespace retronomicon::lib::conversation
