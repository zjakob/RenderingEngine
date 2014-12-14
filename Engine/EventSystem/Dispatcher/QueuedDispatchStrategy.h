#ifndef QUEUED_DISPATCH_STRATEGY_H
#define QUEUED_DISPATCH_STRATEGY_H

#include <list>
#include <memory>

#include "DispatchStrategy.h"

class QueuedDispatchStrategy : public DispatchStrategy
{
public:
	QueuedDispatchStrategy() : 
		eventList(new std::list<std::unique_ptr<Event>>()), 
		eventListForUpdate(new std::list<std::unique_ptr<Event>>())
	{ }

	virtual void dispatchEvent(Event* event);
	virtual void update(ListenerStrategy& listenerStrategy);

private:
	std::list<std::unique_ptr<Event>>* eventList;
	std::list<std::unique_ptr<Event>>* eventListForUpdate;
};

#endif
