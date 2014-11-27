#ifndef KEY_UP_EVENT_H
#define KEY_UP_EVENT_H

#include <string>

#include "Event.h"

class KeyUpEvent : public Event
{
public:
	static const std::string KEY_UP_EVENT_TYPE;

	KeyUpEvent(char key);
	char getKey() { return key; }

private:
	char key;
};

#endif