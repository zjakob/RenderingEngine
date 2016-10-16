#ifndef SAG_QUEUED_DISPATCH_STRATEGY_H
#define SAG_QUEUED_DISPATCH_STRATEGY_H

#include <list>
#include <memory>


namespace sag
{

template <typename EventType, typename ListenerStrategy>
class QueuedEventDispatchStrategy
{
public:

	void dispatchEvent(std::unique_ptr<EventType>&& event)
	{
		eventList.push_back(std::move(event));
	}

	void update(ListenerStrategy& listenerStrategy)
	{
		std::list<std::unique_ptr<EventType>> tmpEventList;
		std::swap(tmpEventList, eventList);

		for (auto& event : tmpEventList) {
			listenerStrategy.fireEvent(*event.get());
		}
	}

private:
	std::list<std::unique_ptr<EventType>> eventList;
};

} // namespace sag

#endif // SAG_QUEUED_DISPATCH_STRATEGY_H
