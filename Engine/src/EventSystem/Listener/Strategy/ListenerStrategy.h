#ifndef LISTENER_STRATEGY_H
#define LISTENER_STRATEGY_H

#include <functional>

#include "..\..\Event\Event.h"

class ListenerStrategy
{
public:
	virtual void addListener(std::string eventName, std::function<void(Event&)> listener) = 0;
	virtual void removeListener(std::string eventName, std::function<void(Event&)> listener) = 0;
	virtual void fireEvent(Event& event) = 0;
private:
	
};

#endif