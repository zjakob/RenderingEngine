#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include <string>

#include "..\..\util\keyboardHelper.h"

#include "Event.h"

class KeyDownEvent : public Event
{
public:

	KeyDownEvent(const float deltaTime, const keyboardHelper::KeyboardKey key)
		: deltaTime(deltaTime), key(key)
	{

	}

	const keyboardHelper::KeyboardKey getKey() { return key; }
	const float getDeltaTime() { return deltaTime; }

private:
	const keyboardHelper::KeyboardKey key;
	const float deltaTime;
};

#endif // KEY_DOWN_EVENT_H
