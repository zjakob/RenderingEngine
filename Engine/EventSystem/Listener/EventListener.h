#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <String>

#include "..\Event\Event.h"

class EventListener
{
public:
	virtual void processEvent(Event* event) = 0;
	virtual bool operator==(const EventListener &rhs) const;
	std::string getName();

protected:
	std::string name;
};

#endif