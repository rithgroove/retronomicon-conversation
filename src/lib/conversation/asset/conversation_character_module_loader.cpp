#include "retronomicon/lib/conversation/asset/conversation_character_module_loader.h"
#include "retronomicon/lib/animation/animation_clip.h"
#include "retronomicon/lib/animation/animation_frame.h"
#include "retronomicon/lib/animation/animation_component.h"
#include "retronomicon/lib/graphic/sprite_component.h"
#include <iostream>

namespace retronomicon::lib::conversation::asset {

    using namespace retronomicon::lib::core;
    using namespace retronomicon::lib::graphic;
    using namespace retronomicon::lib::animation;
    using namespace retronomicon::lib::asset;

    [[nodiscard]] bool ConversationCharacterModuleLoader::canLoad(const nlohmann::json& json) const noexcept {
        return json.contains("retronomicon-conversation");
    }

    [[nodiscard]] std::shared_ptr<Character> ConversationCharacterModuleLoader::load(const nlohmann::json& json) const {
        if (!m_assetManager) {
            std::cerr << "[ConversationCharacterModuleLoader] No AssetManager set!\n";
            return nullptr;
        }

        if (!canLoad(json)) {
            std::cerr << "[ConversationCharacterModuleLoader] Invalid JSON: missing retronomicon-conversation\n";
            return nullptr;
        }

        auto character = std::make_shared<Character>();
        auto convData = json["retronomicon-conversation"];

        // --- Sprites ---
        // std::unordered_map<std::string, std::shared_ptr<ImageAsset>> spriteAssets;
        // if (convData.contains("sprites") && convData["sprites"].contains("files")) {
        //     for (const auto& spriteJson : convData["sprites"]["files"]) {
        //         std::string path = spriteJson.value("path", "");
        //         std::string spriteName = spriteJson.value("name", "");
        //         if (!spriteName.empty() && !path.empty()) {
        //             auto imageAsset = m_assetManager->loadImage(path, spriteName);
        //             if (imageAsset) {
        //                 spriteAssets[spriteName] = imageAsset;
        //             }
        //         }
        //     }
        // }

        // --- Expressions as AnimationClip ---
        // auto animationComponent = std::make_shared<AnimationComponent>();
        // if (convData.contains("sprites") && convData["sprites"].contains("expression")) {
        //     for (const auto& expr : convData["sprites"]["expression"]) {
        //         std::string exprName = expr.value("name", "");
        //         std::string assetName = expr.value("asset_name", "");
        //         int x = expr.value("asset_x_pos", 0);
        //         int y = expr.value("asset_y_pos", 0);

        //         auto it = spriteAssets.find(assetName);
        //         if (it != spriteAssets.end()) {
        //             auto sprite = std::make_shared<Sprite>(it->second, it->second->getWidth(), it->second->getHeight());
        //             auto frame = std::make_shared<AnimationFrame>(sprite, x, y);
        //             auto clip = std::make_shared<AnimationClip>();
        //             clip->addFrame(frame);
        //             animationComponent->addClip(exprName, clip);
        //         }
        //     }
        // }

        // Attach AnimationComponent to Character entity
        // character->addComponent(animationComponent);

        return character;
    }

} // namespace retronomicon::lib::conversation::asset
