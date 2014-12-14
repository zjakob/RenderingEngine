#include "SaveListenerStrategy.h"

void SaveListenerStrategy::addListener(std::string eventName, EventListener<Event>* listener)
{
	auto listenerList = listeners.find(eventName);

	if (listenerList != listeners.end())	// listeners found
	{
		listenerList->second.push_back(listener);
	}
	else // no listeners found, add new list
	{
		std::list<EventListener<Event>*> newListenerList{ listener };
		auto pairtest = std::make_pair(eventName, newListenerList);

		listeners.insert(pairtest);
	}
}

void SaveListenerStrategy::removeListener(std::string eventName, EventListener<Event>* listener)
{
	auto listenerList = listeners.find(eventName);
	listenerList->second.remove(listener);
}

void SaveListenerStrategy::fireEvent(Event& event)
{
	auto listenerList = listeners.find(event.getEventName());

	if (listenerList != listeners.end())	// listeners found
	{		
		for (auto listener : listenerList->second)
		{
			listener->handleEvent(event);
		}
	}
}
