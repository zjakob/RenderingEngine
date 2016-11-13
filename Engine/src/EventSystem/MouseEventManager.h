#ifndef SAG_MOUSE_EVENT_MANAGER_H
#define SAG_MOUSE_EVENT_MANAGER_H

#include "EventManager.h"
#include "Event\MouseMoveEvent.h"
#include "Listener\Strategy\SafeEventCallbackStrategy.h"
#include "Dispatcher\QueuedEventDispatchStrategy.h"

namespace sag
{

using SafeMouseMoveCallbackStartegy = SafeEventCallbackStrategy<MouseMoveEvent>;
using QueuedSafeMouseMoveDispatchStrategy = QueuedEventDispatchStrategy<MouseMoveEvent, SafeEventCallbackStrategy<MouseMoveEvent> >;


class MouseEventManager
{

public:
	static MouseEventManager& getInstance();

	void update()
	{
		eventManager.update();
	}

	void dispatchEvent(std::unique_ptr<MouseMoveEvent>&& event)
	{
		eventManager.dispatchEvent(std::move(event));
	}

	void addEventCallback(std::function<void(MouseMoveEvent&)> callback)
	{
		eventManager.addEventCallback(callback);
	}

private:
	MouseEventManager() {}

	EventManager<MouseMoveEvent, SafeMouseMoveCallbackStartegy, QueuedSafeMouseMoveDispatchStrategy> eventManager;

};

} // namespace sag


#endif // SAG_MOUSE_EVENT_MANAGER_H
