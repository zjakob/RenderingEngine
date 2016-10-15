#ifndef MOUSE_MOVE_EVENT_H
#define MOUSE_MOVE_EVENT_H

#include <string>

#include "..\..\util\ioHelper\keyboardHelper.h"

#include "Event.h"

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

#endif // MOUSE_MOVE_EVENT_H
