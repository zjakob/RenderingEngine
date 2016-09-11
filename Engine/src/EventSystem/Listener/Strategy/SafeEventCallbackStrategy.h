#ifndef SAVE_EVENT_CALLBACK_STRATEGY_H
#define SAVE_EVENT_CALLBACK_STRATEGY_H

#include <list>
#include <string>

template <typename EventType>
class SafeEventCallbackStrategy
{
public:
	void addCallback(std::function<void(EventType&)> callback)
	{
		callbacks.push_back(callback);
	}

	void removeCallback(std::function<void(EventType&)> callback)
	{
		callbacks.remove(callback);
	}

	void fireEvent(EventType& event)
	{
		for (auto& callback : callbacks)
		{
			callback(event);
		}
	}

private:
	std::list< std::function<void(EventType&)> > callbacks;
};

#endif // SAVE_EVENT_CALLBACK_STRATEGY_H
