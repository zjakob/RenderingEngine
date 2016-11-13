
#include "MouseEventManager.h"


using namespace sag;

MouseEventManager& MouseEventManager::getInstance()
{
	static MouseEventManager singletonInstance;
	return singletonInstance;
}
