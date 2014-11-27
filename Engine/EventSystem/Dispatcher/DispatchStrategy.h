#ifndef DISPATCH_STRATEGY_H
#define DISPATCH_STRATEGY_H

#include "..\Event\Event.h"
#include "..\Listener\Strategy\ListenerStrategy.h"

class DispatchStrategy
{
public:
	virtual void dispatchEvent(Event* event) = 0;
	virtual void update() = 0;
	virtual void setListenerStrategy(ListenerStrategy& listenerStrategy) = 0;
};

#endif