#ifndef SAVE_LISTENER_STRATEGY_H
#define SAVE_LISTENER_STRATEGY_H

#include "ListenerStrategy.h"

#include <unordered_map>
#include <list>
#include <string>

class SafeListenerStrategy : public ListenerStrategy
{
public:
	virtual void addListener(std::string eventName, std::function<void(Event&)> listener);
	virtual void removeListener(std::string eventName, std::function<void(Event&)> listener);
	virtual void fireEvent(Event& event);
private:
	std::unordered_map<std::string, std::list<std::function<void(Event&)>>> listeners;
};

#endif
