#ifndef LISTENER_STRATEGY_H
#define LISTENER_STRATEGY_H

#include "..\..\Event\Event.h"
#include "..\EventListener.h"

class ListenerStrategy
{
public:
	virtual void addListener(std::string eventName, EventListener<Event>* listener) = 0;
	virtual void removeListener(std::string eventName, EventListener<Event>* listener) = 0;
	virtual void fireEvent(Event& event) = 0;
private:
	
};

#endif