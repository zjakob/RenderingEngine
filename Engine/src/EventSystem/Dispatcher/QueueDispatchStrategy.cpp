#include "QueuedDispatchStrategy.h"
#include <vector>

void QueuedDispatchStrategy::dispatchEvent(std::unique_ptr<Event> event)
{
	eventList.push_back(std::move(event));
}

void QueuedDispatchStrategy::update(ListenerStrategy& listenerStrategy)
{
	std::list<std::unique_ptr<Event>> tmpEventList;
	std::swap(tmpEventList, eventList);

	for (auto& event : tmpEventList) {
		listenerStrategy.fireEvent(*event);
	}
}
