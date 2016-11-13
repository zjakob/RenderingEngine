
#include "KeyboardEventManager.h"


using namespace sag;

KeyboardEventManager& KeyboardEventManager::getInstance()
{
	static KeyboardEventManager singletonInstance;
	return singletonInstance;
}
