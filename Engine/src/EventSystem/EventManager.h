#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <memory>
#include <cassert>
#include <functional>

#include <iostream>

class Event;

template <typename EventType, typename ListenerStrategy, typename DispatchStrategy>
class EventManager
{

private:
	DispatchStrategy dispatchStrategy;
	ListenerStrategy listenerStrategy;

public:
	EventManager()
	{
		static_assert(std::is_base_of<Event, EventType>::value, "EventManager template typename must be of type Event!");
	}

	void update() 
	{
		dispatchStrategy.update(listenerStrategy);
	}

	template <typename EventType>
	void dispatchEvent(std::unique_ptr<EventType>&& event)
	{ 
		dispatchStrategy.dispatchEvent(std::move(event));
	}

	template<typename EventType>
	void addEventCallback(std::function<void(EventType&)> callback)
	{
		listenerStrategy.addCallback(std::move(callback));
	}

};

#endif // EVENT_MANAGER_H
