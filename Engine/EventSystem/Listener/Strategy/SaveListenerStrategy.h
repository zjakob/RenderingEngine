#ifndef SAVE_LISTENER_STRATEGY_H
#define SAVE_LISTENER_STRATEGY_H

#include "ListenerStrategy.h"

#include <unordered_map>
#include <list>
#include <string>

#include "..\EventListener.h"

class SaveListenerStrategy : public ListenerStrategy
{
public:
	virtual void addListener(std::string eventName, EventListener& listener);
	virtual void removeListener(std::string eventName, EventListener& listener);
	virtual void fireEvent(Event& event);
private:
	std::unordered_map<std::string, std::list<EventListener*>> listeners;
};

#endif
