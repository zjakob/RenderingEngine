
#include <iostream>

#include ".\EventSystem\Event\KeyUpEvent.h"
#include ".\EventSystem\EventManager.h"
#include ".\Entities\Player.h"
#include ".\EventSystem\Dispatcher\QueuedDispatchStrategy.h"
#include ".\EventSystem\Listener\Strategy\SaveListenerStrategy.h"

using namespace std;

int main()
{
	cout << "--- Event System ---" << endl;

	SaveListenerStrategy listenerStrategy;
	QueuedDispatchStrategy dispatchStrategy(listenerStrategy);
	
	EventManager mngr(dispatchStrategy, listenerStrategy);
	Player player;
	
	mngr.addEventListener(player, KeyUpEvent::KEY_UP_EVENT_TYPE);
	mngr.dispatchEvent(new KeyUpEvent(38));	// 38 == up arrow
	mngr.update();

	return 0;
}
