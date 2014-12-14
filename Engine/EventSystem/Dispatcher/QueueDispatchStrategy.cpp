#include "QueuedDispatchStrategy.h"
#include <vector>
void QueuedDispatchStrategy::dispatchEvent(Event* event)
{
	eventList->push_back(std::unique_ptr<Event>(event));
}

void QueuedDispatchStrategy::update(ListenerStrategy& listenerStrategy)
{
	// swap pointer of initialized lists to avoid copying the lists
	std::list<std::unique_ptr<Event>>* tmp = eventListForUpdate;
	eventListForUpdate = eventList;
	eventList = tmp;

	for (auto& event : *eventListForUpdate) {
		listenerStrategy.fireEvent(*event);
	}

	eventListForUpdate->clear();
}


