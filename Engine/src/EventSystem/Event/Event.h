#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
	Event(std::string eventName) : eventName(eventName)
	{
	}

	virtual const std::string& getEventName()
	{
		return eventName;
	}

protected:
	std::string eventName;

};

#endif