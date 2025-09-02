#pragma once
#include <string>
#include <vector>
#include <optional>
#include "choice.h"
#include "action.h"

namespace retronomicon::lib::conversation::data{

    class ConversationNode {
    public:
        ConversationNode();
        ConversationNode(
            std::string id,
            std::string speaker,
            std::string text, 
            std::string expression, 
            std::vector<Choice> choices, 
            std::optional<std::string> next, 
            std::vector<Action> actions);

        // Getters
        const std::string& getId() const {return m_id;}
        const std::string& getSpeaker() const {return m_speaker;}
        const std::string& getText() const {return m_text;}
        const std::string& getExpression() const { return m_expression;}
        const std::string&  getBackground() const {return m_background;}
        const std::vector<Choice>& getChoices() const {return m_choices;}
        const std::optional<std::string>& getNext() const{return m_next;}
        const std::vector<Action>& getActions() const {return m_actions;}

        // Setters
        void setId(const std::string& value) { m_id = value; }  
        void setSpeaker(const std::string& value){ m_speaker = value; }
        void setText(const std::string& value){ m_text = value; }
        void setExpression(const std::string& value){ m_expression = value; }
        void setBackground(const std::string& value){ m_background = value; }
        void setChoices(const std::vector<Choice>& value){ m_choices = value; }
        void setNext(const std::optional<std::string>& value){ m_next = value; }
        void setActions(const std::vector<Action>& value){ m_actions = value; }
    private:
        std::string m_id;
        std::string m_background;
        std::string m_speaker;
        std::string m_text;
        std::string m_expression;
        std::vector<Choice> m_choices;
        std::optional<std::string> m_next;
        std::vector<Action> m_actions;
    };

} // namespace retronomicon::lib::conversation
