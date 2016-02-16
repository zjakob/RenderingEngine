#include "SaveListenerStrategy.h"

void SaveListenerStrategy::addListener(std::string eventName, std::function<void(Event&)> listener)
{
	auto listenerList = listeners.find(eventName);

	if (listenerList != listeners.end())	// listeners found
	{
		listenerList->second.push_back(listener);
	}
	else // no listeners found, add new list
	{
		std::list<std::function<void(Event&)>> newListenerList{ listener };
		auto pairtest = std::make_pair(eventName, newListenerList);

		listeners.insert(pairtest);
	}
}

void SaveListenerStrategy::removeListener(std::string eventName, std::function<void(Event&)> listener)
{
	// not really working at the moment
}

void SaveListenerStrategy::fireEvent(Event& event)
{
	auto listenerList = listeners.find(event.getEventName());

	if (listenerList != listeners.end())	// listeners found
	{		
		for (auto listener : listenerList->second)
		{
			listener(event);
		}
	}
}
