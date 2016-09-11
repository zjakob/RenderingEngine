#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include <string>

#include "..\..\util\keyboardHelper.h"

#include "Event.h"

class KeyDownEvent : public Event
{
public:

	KeyDownEvent(keyboardHelper::KeyboardKey key) 
		: key(key)
	{

	}

	keyboardHelper::KeyboardKey getKey() { return key; }

private:
	keyboardHelper::KeyboardKey key;
};

#endif // KEY_DOWN_EVENT_H
