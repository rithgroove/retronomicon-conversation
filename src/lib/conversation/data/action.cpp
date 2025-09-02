#include <sstream>
#include "retronomicon/lib/conversation/data/action.h"

namespace retronomicon::lib::conversation::data{

    /***************************** Construtor *****************************/

    /**
     * @brief constuctor
     * 
     * @param text saved to m_text
     * @param next saved to m_next
     */
    Action::Action(
        std::string type, 
        std::string target, 
        std::string value, 
        float duration): 
            m_type(type),
            m_target(target),
            m_value(value),
            m_duration(duration){}

    /***************************** To String *****************************/
    
    /**
     * @brief a method to help people debug this object
     * 
     * @return Brief summary of this object in string
     */
    std::string Action::to_string() const{
        std::ostringstream oss;
        oss << "[Action]\n";
        oss << "values:\n";
        oss << "- type    = "<< m_type <<"\n";
        oss << "- target   = "<< m_target <<"\n";
        oss << "- value    = "<< m_value <<"\n";
        oss << "- duration   = "<< m_duration <<"\n";
        return oss.str();
    }

}
