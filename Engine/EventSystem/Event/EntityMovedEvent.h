#ifndef ENTITY_MOVED_EVENT_H
#define ENTITY_MOVED_EVENT_H

#include <string>

#include "Event.h"
#include "..\..\Entities\IEntity.h"

class EntityMovedEvent : public Event
{
public:
	static const std::string ENTITY_MOVED_EVENT_TYPE;

	EntityMovedEvent(IEntity* entity);

private:
	char key;
};

#endif