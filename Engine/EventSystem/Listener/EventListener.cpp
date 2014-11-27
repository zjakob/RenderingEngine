#include "EventListener.h"

bool EventListener::operator==(const EventListener &rhs) const
{
	return this->name.compare(rhs.name) == 0 ? true : false;
}
