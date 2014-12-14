#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include <string>

#include "Event.h"

class KeyDownEvent : public Event
{
public:
	static const std::string KEY_DOWN_EVENT_TYPE;

	KeyDownEvent(char key);

	char getKey() { return key; }

private:
	char key;
};

#endif