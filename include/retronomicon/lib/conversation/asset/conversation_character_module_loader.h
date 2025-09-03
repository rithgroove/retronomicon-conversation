#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "retronomicon/lib/core/entity.h"
#include "retronomicon/lib/core/character.h"
#include "retronomicon/lib/asset/asset_manager.h"

namespace retronomicon::lib::conversation::asset {

class ConversationCharacterModuleLoader {
public:
    ConversationCharacterModuleLoader() = default;

    void setAssetManager(std::shared_ptr<retronomicon::lib::asset::AssetManager> assetManager) noexcept {
        m_assetManager = std::move(assetManager);
    }

    [[nodiscard]] bool canLoad(const nlohmann::json& json) const noexcept;
    [[nodiscard]] std::shared_ptr<retronomicon::lib::core::Character> load(const nlohmann::json& json) const;

private:
    std::shared_ptr<retronomicon::lib::asset::AssetManager> m_assetManager;
};

} // namespace retronomicon::lib::conversation::asset
