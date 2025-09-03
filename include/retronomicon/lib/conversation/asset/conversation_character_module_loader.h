#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "retronomicon/lib/core/entity.h"
#include "retronomicon/lib/core/character.h"
#include "retronomicon/lib/asset/asset_manager.h"
#include "retronomicon/lib/asset/character_module_loader.h"

namespace retronomicon::lib::conversation::asset {
    using retronomicon::lib::asset::CharacterModuleLoader;
    using retronomicon::lib::core::Character;
    class ConversationCharacterModuleLoader : public CharacterModuleLoader{
        public:
        ConversationCharacterModuleLoader();

        [[nodiscard]] bool canLoad(const nlohmann::json& json) const noexcept;
        void load(std::shared_ptr<Character>& character, const nlohmann::json& json) override;

    };

} // namespace retronomicon::lib::conversation::asset
