#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include <memory>

#include "retronomicon/lib/asset/font_asset.h"
#include "retronomicon/lib/conversation/conversation_node.h"
#include "retronomicon/lib/ui/nine_slice_panel_component.h"
#include "retronomicon/lib/core/component.h"
#include "retronomicon/lib/core/transform_component.h"
#include "retronomicon/lib/core/renderable.h"

namespace retronomicon::lib::conversation {

    /**
     * @brief A visual novel style textbox that renders dialog nodes with typewriter effect.
     */
    class VNTextBoxComponent : public core::Component,public core::Renderable {
    public:
        VNTextBoxComponent(std::shared_ptr<asset::FontAsset> font,
                           std::shared_ptr<ui::NineSlicePanelComponent> panel,
                           int maxWidth,
                           int padding = 12);

        void setNode(std::shared_ptr<ConversationNode> node);

        /// Call once per frame to update typewriter progression
        void update(float deltaTime) override;

        // Now matches Renderable
        void render(SDL_Renderer* renderer) override;

        /// Advance to show the full text immediately
        void skipToFullText();

        /// Check if the entire node text has been revealed
        bool isFinished() const { return m_finished; }

    private:
        std::shared_ptr<asset::FontAsset> m_font;
        std::shared_ptr<ui::NineSlicePanelComponent> m_panel;
        std::shared_ptr<ConversationNode> m_node;
        core::TransformComponent* m_transform = nullptr;

        std::vector<std::string> m_wrappedLines;

        int m_maxWidth;
        int m_padding;

        float m_charDelay = 0.03f;     // seconds between letters
        float m_timeAccumulator = 0.0f;
        size_t m_currentCharIndex = 0;
        bool m_finished = false;

        /// Generate wrapped lines from current node text
        void regenerateWrappedText();
    };

}
