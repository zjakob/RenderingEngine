
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
	
	EventManager mngr(new QueuedDispatchStrategy(), new SaveListenerStrategy());
	Player* player = new Player();

	mngr.addEventListener(KeyUpEvent::KEY_UP_EVENT_TYPE, player);
	mngr.dispatchEvent(new KeyUpEvent(38));	// 38 == up arrow
	mngr.update();
	/*
	Player player2;

	if (player == player2)
	{
		std::cout << "true";
	}
	*/
	return 0;
}
