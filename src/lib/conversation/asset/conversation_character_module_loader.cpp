#include "retronomicon/lib/conversation/asset/conversation_character_module_loader.h"
#include "retronomicon/lib/animation/animation_clip.h"
#include "retronomicon/lib/animation/animation_frame.h"
#include "retronomicon/lib/animation/animation_component.h"
#include "retronomicon/lib/core/transform_component.h"
#include "retronomicon/lib/graphic/sprite_component.h"
#include <iostream>
#include <sstream>

namespace retronomicon::lib::conversation::asset {

    using namespace retronomicon::lib::core;
    using namespace retronomicon::lib::graphic;
    using namespace retronomicon::lib::animation;
    using namespace retronomicon::lib::asset;
    ConversationCharacterModuleLoader::ConversationCharacterModuleLoader(){

    }

    [[nodiscard]] bool ConversationCharacterModuleLoader::canLoad(const nlohmann::json& json) const noexcept {
        return json.contains("retronomicon-conversation");
    }

    void ConversationCharacterModuleLoader::load(std::shared_ptr<Character>& character, const nlohmann::json& json) {
        if (!m_assetManager) {
            std::cerr << "[ConversationCharacterModuleLoader] No AssetManager set!\n";
            return;
        }

        if (!canLoad(json)) {
            std::cerr << "[ConversationCharacterModuleLoader] Invalid JSON: missing retronomicon-conversation\n";
            return;
        }

        auto convData = json["retronomicon-conversation"];

        // --- Sprites ---
        std::shared_ptr<ImageAsset> asset = nullptr;
        if (convData.contains("sprite") && convData["sprite"].contains("filepath")) {
            auto asset = m_assetManager->loadImage(convData["sprite"]["filepath"], convData["sprite"]["asset_name"]);
        }

        Entity* vnEntity = new Entity("tachi");              // construct directly
        vnEntity->setVisible();

        vnEntity->addComponent<SpriteComponent>(asset);

        vnEntity->addComponent<TransformComponent>();


        int width = convData["sprite"]["width"];
        int height = convData["sprite"]["width"];
        // --- Expressions as AnimationClip ---
        if (convData.contains("sprites") && convData["sprites"].contains("expression")) {
            shared_ptr<AnimationClip> defaultClip = nullptr;
            std::vector<shared_ptr<AnimationClip>> clips;
            for (const auto& expr : convData["sprites"]["expression"]) {
                std::string exprName = expr.value("name", "");
                int x = expr.value("asset_x_pos", 0) * width;
                int y = expr.value("asset_y_pos", 0) * height;
                std::vector<AnimationFrame> frames;
                frames.push_back(AnimationFrame(x, y,width,height,6000)) ;
                auto clip = std::make_shared<AnimationClip>(frames,exprName,true);
                if (exprName == "default"){
                    defaultClip = clip;
                }else{
                    clips.push_back(clip);
                }
            }
            auto animationComponent = vnEntity->addComponent<AnimationComponent>(defaultClip);
            for (auto clip : clips){
                animationComponent->addClip(clip);
            }
        }

        character->registerModuleEntity("retronomicon-conversation", vnEntity); 
        // Attach AnimationComponent to Character entity
        // character->addComponent(animationComponent);
    }

} // namespace retronomicon::lib::conversation::asset
