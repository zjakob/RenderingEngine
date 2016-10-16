#ifndef SAG_MOUSE_MOVE_EVENT_H
#define SAG_MOUSE_MOVE_EVENT_H

#include <string>

#include "Event.h"


namespace sag
{

class MouseMoveEvent : public Event
{
public:

	MouseMoveEvent(const float deltaTime, const float deltaX, const float deltaY)
		: deltaTime(deltaTime), deltaX(deltaX), deltaY(deltaY)
	{

	}

	const float getDeltaTime() { return deltaTime; }
	const float getDeltaX() { return deltaX; }
	const float getDeltaY() { return deltaY; }

private:
	const float deltaTime;
	const float deltaX;
	const float deltaY;
};

} // namespace sag


#endif // SAG_MOUSE_MOVE_EVENT_H
