#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <string>
#include <memory>
#include <cassert>
#include <functional>

#include <iostream>

#include "EventManager.h"
#include "Dispatcher\QueuedEventDispatchStrategy.h"
#include "Listener\Strategy\SafeEventCallbackStrategy.h"
#include "Event\KeyDownEvent.h"

class EventSystem
{

private:

public:

	/* 
	 * TODO: 
	 * 1. EventManager factory
	 * 2. handle dispatching of events
	 * 3. store event in a single queue
	 */

};

#endif // EVENT_SYSTEM_H
