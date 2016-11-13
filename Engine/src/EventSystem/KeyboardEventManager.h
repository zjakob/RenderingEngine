#ifndef SAG_KEYBOARD_EVENT_MANAGER_H
#define SAG_KEYBOARD_EVENT_MANAGER_H

#include "EventManager.h"
#include "Event\KeyDownEvent.h"
#include "Listener\Strategy\SafeEventCallbackStrategy.h"
#include "Dispatcher\QueuedEventDispatchStrategy.h"

namespace sag
{

using SafeKeyDownCallbackStartegy = SafeEventCallbackStrategy<KeyDownEvent>;
using QueuedSafeKeyDownDispatchStrategy = QueuedEventDispatchStrategy<KeyDownEvent, SafeEventCallbackStrategy<KeyDownEvent> >;


class KeyboardEventManager
{

public:
	static KeyboardEventManager& getInstance();

	void update()
	{
		eventManager.update();
	}

	void dispatchEvent(std::unique_ptr<KeyDownEvent>&& event)
	{
		eventManager.dispatchEvent(std::move(event));
	}

	void addEventCallback(std::function<void(KeyDownEvent&)> callback)
	{
		eventManager.addEventCallback(callback);
	}

private:
	KeyboardEventManager() {}

	EventManager<KeyDownEvent, SafeKeyDownCallbackStartegy, QueuedSafeKeyDownDispatchStrategy> eventManager;

};

} // namespace sag


#endif // SAG_KEYBOARD_EVENT_MANAGER_H
