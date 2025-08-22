#pragma once
#include <string>

namespace retronomicon::lib::conversation{
    class Choice {
        public: 
            /***************************** Constructor *****************************/
            /**
             * @brief constuctor
             * 
             * @param text saved to m_text
             * @param next saved to m_next
             */
            Choice(std::string text, std::string next);

            /***************************** Setter *****************************/

            /**
             * @brief setter for m_text
             * 
             * @param text (the text)
             */
            void setText(std::string text) { m_text = text;}

            /**
             * @brief setter for m_next
             * 
             * @param next (the next)
             */
            void setNext(std::string next) { m_next = next;}

            /***************************** Getter *****************************/

            /**
             * @brief getter for m_text
             * 
             * @return the text
             */
            std::string getText() {return m_text;}

            /**
             * @brief getter for m_next
             * 
             * @return the m_next value
             */
            std::string getNext() {return m_next;}

            /***************************** Operator Overload *****************************/

            /**
             * @brief overloading operator << to call to_string()
             */
            friend std::ostream& operator<<(std::ostream& os, const Choice& obj) {
                return os << obj.to_string();
            }

            /***************************** To String *****************************/

            /**
             * @brief a method to help people debug this object
             * 
             * @return Brief summary of this object in string
             */
            std::string to_string() const;

        private:
            /***************************** Attribute *****************************/
            std::string m_text;
            std::string m_next;

    };

}
