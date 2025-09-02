#pragma once
#include <string>
#include <memory>
#include "retronomicon/lib/core/entity.h"  // assuming this exists in your ECS

namespace retronomicon::lib::conversation::data{

	class Speaker {
	public:
	    Speaker(std::string id, retronomicon::lib::core::Entity* entity)
	        : m_id(std::move(id)), m_entity(entity) {}

	    const std::string& getId() const { return m_id; }
	    retronomicon::lib::core::Entity* getEntity() const { return m_entity; }

	    void setExpression(const std::string& expression);

	    std::string toString() const;

	private:
	    std::string m_id;   // "npc1", "hero", etc.
	    retronomicon::lib::core::Entity* m_entity; // pointer to ECS entity with sprite/animation
	    std::string m_currentExpression; // "smile", "angry", "neutral"
	};

	inline std::ostream& operator<<(std::ostream& os, const Speaker& s) {
	    return os << s.toString();
	}

} // namespace retronomicon::lib::conversation
