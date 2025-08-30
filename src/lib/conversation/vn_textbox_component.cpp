#include "retronomicon/lib/conversation/vn_textbox_component.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>

using namespace retronomicon::lib::conversation;

VNTextBoxComponent::VNTextBoxComponent(std::shared_ptr<asset::FontAsset> font,
                                       NineSlicePanelComponent* panel,
                                       int maxWidth,
                                       int padding)
    : m_font(std::move(font)),
      m_panel(std::move(panel)),
      m_maxWidth(maxWidth),
      m_padding(padding) {}

void VNTextBoxComponent::setNode(ConversationNode* node) {
    m_node = std::move(node);
    m_currentCharIndex = 0;
    m_timeAccumulator = 0.0f;
    m_finished = false;
    regenerateWrappedText();
}

void VNTextBoxComponent::update(float deltaTime) {
    std::cout<< "Masuk Update" <<std::endl;
    if (!m_node){
        std::cout<< "[update] nul" <<std::endl;
        return;
    }
    if (m_finished){
        std::cout<< "[update] m_finished" <<std::endl;
        return;        
    }

    m_timeAccumulator += deltaTime;
    while (m_timeAccumulator >= m_charDelay) {
        m_timeAccumulator -= m_charDelay;

        if (m_currentCharIndex < m_node->getText().size()) {
            m_currentCharIndex++;
        } else {
            m_finished = true;
            break;
        }
    }
}

void VNTextBoxComponent::render(SDL_Renderer* renderer) {
    std::cout<< "Masuk render" <<std::endl;
    if (!m_node){
        std::cout<< "[render] m_node nul" <<std::endl;
        return;
    }
    if (!m_transform){
        std::cout<< "[render] m_transform null" <<std::endl;
        return;        
    }

    // Position comes from TransformComponent
    Vec2 renderPos = m_transform->getRenderPosition();
    int x = renderPos.x;
    int y = renderPos.y;

    int boxW = m_maxWidth - 2 * m_padding;
    int boxH = static_cast<int>(m_wrappedLines.size()) * m_font->getLineHeight() + 2 * m_padding;
    if (boxH < m_minHeight){
        boxH = m_minHeight;
    }

    m_panel->setSize(boxW, boxH);
    m_panel->render(renderer);

    size_t charsRemaining = m_currentCharIndex;
    int drawY = y + m_padding;

    for (const auto& line : m_wrappedLines) {
        if (charsRemaining == 0) break;

        size_t charsToDraw = std::min(charsRemaining, line.size());
        std::string visible = line.substr(0, charsToDraw);
        std::cout << "visible = " <<visible<<std::endl;
        std::cout << "x =  " << x + m_padding <<std::endl;
        std::cout << "y =  " << drawY <<std::endl;
        m_font->renderText(renderer, visible, x + m_padding, drawY,SDL_Color{255, 255, 255, 255});

        charsRemaining -= charsToDraw;
        drawY += m_font->getLineHeight();
    }
}

Rect VNTextBoxComponent::getSize(){
    return m_panel->getSize();
}

void VNTextBoxComponent::skipToFullText() {
    if (!m_node) return;
    m_currentCharIndex = m_node->getText().size();
    m_finished = true;
}

void VNTextBoxComponent::regenerateWrappedText() {
    m_wrappedLines.clear();
    if (!m_node) return;

    std::string text = m_node->getText();
    std::string currentLine;
    std::string currentWord;

    for (char c : text) {
        if (c == ' ' || c == '\n') {
            // Try placing the word
            int testWidth = m_font->measureTextWidth(currentLine + currentWord + " ");
            if (testWidth > m_maxWidth && !currentLine.empty()) {
                m_wrappedLines.push_back(currentLine);
                currentLine = currentWord + " ";
            } else {
                currentLine += currentWord + " ";
            }
            currentWord.clear();

            if (c == '\n') {
                m_wrappedLines.push_back(currentLine);
                currentLine.clear();
            }
        } else {
            currentWord += c;
        }
    }

    // Handle trailing word
    if (!currentWord.empty()) {
        int testWidth = m_font->measureTextWidth(currentLine + currentWord);
        if (testWidth > m_maxWidth && !currentLine.empty()) {
            m_wrappedLines.push_back(currentLine);
            currentLine = currentWord;
        } else {
            currentLine += currentWord;
        }
    }

    if (!currentLine.empty()) {
        m_wrappedLines.push_back(currentLine);
    }
}
