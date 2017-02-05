#ifndef SAG_EVENT_MANAGER_H
#define SAG_EVENT_MANAGER_H

#include <string>
#include <memory>
#include <cassert>
#include <functional>

#include <iostream>


namespace sag
{

class Event;

template <typename EventType, typename ListenerStrategy, typename DispatchStrategy>
class EventManager
{

public:
	EventManager()
	{
		static_assert(std::is_base_of<Event, EventType>::value, "EventManager template typename must be of type Event!");
	}

	void update() 
	{
		dispatchStrategy.update(listenerStrategy);
	}

	void dispatchEvent(std::unique_ptr<EventType>&& event)
	{ 
		dispatchStrategy.dispatchEvent(std::move(event));
	}

	void addEventCallback(std::function<void(EventType&)> callback)
	{
		listenerStrategy.addCallback(std::move(callback));
	}

private:
	DispatchStrategy dispatchStrategy;
	ListenerStrategy listenerStrategy;

};

} // namespace sag


#endif // SAG_EVENT_MANAGER_H
