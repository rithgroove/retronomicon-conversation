#include <sstream>
#include "retronomicon/lib/conversation/choice.h"

namespace retronomicon::lib::conversation{

    /***************************** Construtor *****************************/

    /**
     * @brief constuctor
     * 
     * @param text saved to m_text
     * @param next saved to m_next
     */
    Choice::Choice(std::string text, std::string next): m_text(text),m_next(next){

    }

    /***************************** To String *****************************/
    
    /**
     * @brief a method to help people debug this object
     * 
     * @return Brief summary of this object in string
     */
    std::string Choice::to_string() const{
        std::ostringstream oss;
        oss << "[Choice]\n";
        oss << "values:\n";
        oss << "- text    = "<< m_text <<"\n";
        oss << "- next   = "<< m_next <<"\n";
        return oss.str();
    }

}
