
#include "EntityMovedEvent.h"

const std::string EntityMovedEvent::ENTITY_MOVED_EVENT_TYPE = "ENTITY_MOVED_EVENT";

EntityMovedEvent::EntityMovedEvent(IEntity* entity) : Event(ENTITY_MOVED_EVENT_TYPE)
{

}
