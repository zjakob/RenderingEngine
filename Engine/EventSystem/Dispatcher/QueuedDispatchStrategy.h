#ifndef QUEUED_DISPATCH_STRATEGY_H
#define QUEUED_DISPATCH_STRATEGY_H

#include <list>
#include <memory>

#include "DispatchStrategy.h"

class QueuedDispatchStrategy : public DispatchStrategy
{
public:
	QueuedDispatchStrategy(ListenerStrategy& listenerStrategy) : 
		listenerStrategy(listenerStrategy), 
		eventList(new std::list<std::unique_ptr<Event>>()), 
		eventListForUpdate(new std::list<std::unique_ptr<Event>>())
	{ }
	virtual void dispatchEvent(Event* event);
	virtual void update();
	virtual void setListenerStrategy(ListenerStrategy& listenerStrategy) { this->listenerStrategy = listenerStrategy; }

private:
	std::list<std::unique_ptr<Event>>* eventList;
	std::list<std::unique_ptr<Event>>* eventListForUpdate;
	ListenerStrategy& listenerStrategy;
};

#endif
