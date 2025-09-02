#pragma once
#include <string>

namespace retronomicon::lib::conversation::data{
    class Action {
        public:
            /***************************** Constructor *****************************/
            /**
             * @brief constuctor
             * 
             * @param type saved to m_type
             * @param target saved to m_target
             * @param value saved to m_value
             * @param duration saved to m_duration
             */
            Action(std::string type, std::string target,std::string value, float duration);

            /***************************** Setter *****************************/

            /**
             * @brief setter for m_type
             * 
             * @param type (the type)
             */
            void setType(std::string type) { m_type = type;}

            /**
             * @brief setter for m_target
             * 
             * @param target (the target)
             */
            void setTarget(std::string target) { m_target = target;}

            /**
             * @brief setter for m_value
             * 
             * @param value (the value)
             */
            void setValue(std::string value) { m_value = value;}

            /**
             * @brief setter for m_duration
             * 
             * @param duration (the duration)
             */
            void setDuration(float duration) { m_duration = duration;}

            /***************************** Getter *****************************/

            /**
             * @brief getter for m_type
             * 
             * @return the type
             */
            std::string getType() {return m_type;}

            /**
             * @brief getter for m_target
             * 
             * @return the target
             */
            std::string getTarget() {return m_target;}

            /**
             * @brief getter for m_value
             * 
             * @return the value
             */
            std::string getValue() {return m_value;}

            /**
             * @brief getter for m_duration
             * 
             * @return the duration
             */
            float getDuration() {return m_duration;}

            /***************************** Operator Overload *****************************/

            /**
             * @brief overloading operator << to call to_string()
             */
            friend std::ostream& operator<<(std::ostream& os, const Action& obj) {
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
            std::string m_type;   // e.g. "expression", "sound", "shake"
            std::string m_target; // e.g. "Hero", "screen"
            std::string m_value;  // e.g. "sad", "footstep.wav"
            float m_duration = 0.0f; // optional
    };
    
}