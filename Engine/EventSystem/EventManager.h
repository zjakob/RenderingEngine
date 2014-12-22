#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <memory>
#include <cassert>
#include <functional>

#include ".\Dispatcher\DispatchStrategy.h"
#include ".\Listener\Strategy\ListenerStrategy.h"
#include ".\Event\Event.h"


class EventManager
{
public:
	/*
	 * since dependency injection is used for the strategy pattern
	 * object lifetime should also be handled by the injecting caller and not by EventManager. (this should also be reflected in the documentation!)
	 * to avoid depending on an already deleted/freed object, a factory class needs to be created to inject the dependencies into EventManager. Otherwise EventManager needs ownership of the dependencies!
	 * if ownership is required by EventManager then smart-pointers (shared ptrs for all ownerships and weak ptrs for plain references) must be used here instead of references/raw-pointers
	 * never copy the object by value since it can cause object-slicing (losing information of the derived class when copied to super class)
	 * if pointers are used for the member variables, then ideally the dependencies should still be passed as references to the constructor (passing NULL is impossible) but then be assigned to the pointer member variables
	 */
	EventManager(DispatchStrategy* dispatchStrategy, ListenerStrategy* listenerStrategy)
		: dispatchStrategy(dispatchStrategy), listenerStrategy(listenerStrategy)
	{
		assert(dispatchStrategy != nullptr);
		assert(listenerStrategy != nullptr);
	}

	inline void update() 
	{ 
		dispatchStrategy->update(*(listenerStrategy.get()));
	}

	inline void dispatchEvent(Event* event) 
	{ 
		dispatchStrategy->dispatchEvent(event); 
	}

	template<typename T1, typename T2>
	inline void addEventListener(std::string eventType, T1 callbackFct, T2* listenerObj) 
	{
		//void (T2::*eventCallbackFct)(Event&) = (void (T2::*)(Event&)) (callbackFct);
		auto eventCallbackFct = reinterpret_cast<void (T2::*)(Event&)>(callbackFct);

		listenerStrategy->addListener(eventType, std::bind(eventCallbackFct, listenerObj, std::placeholders::_1));
	};

private:
	// using references as member variables can cause issues when copying an object.
	// so either prevent an object from being copied (private copy-constr/assignm-op)
	// or use pointers instead of references
	// pointers are prefereable/only way if member should be resetable (which is the case for the strategies)
	std::unique_ptr<DispatchStrategy> dispatchStrategy;
	std::unique_ptr<ListenerStrategy> listenerStrategy;
};

#endif