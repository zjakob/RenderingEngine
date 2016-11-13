#ifndef SAG_KEY_DOWN_EVENT_H
#define SAG_KEY_DOWN_EVENT_H

#include <string>

#include "../../util/ioHelper/keyboardHelper.h"

#include "Event.h"


namespace sag
{

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

} // namespace sag


#endif // SAG_KEY_DOWN_EVENT_H
