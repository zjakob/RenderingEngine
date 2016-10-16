#ifndef SAG_SAVE_EVENT_CALLBACK_STRATEGY_H
#define SAG_SAVE_EVENT_CALLBACK_STRATEGY_H

#include <list>
#include <string>


namespace sag
{

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

} // namespace sag


#endif // SAG_SAVE_EVENT_CALLBACK_STRATEGY_H
