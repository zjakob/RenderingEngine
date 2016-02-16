
#include <iostream>
#include <memory>

#include ".\EventSystem\EventManager.h"
#include ".\Entities\Player.h"
#include ".\EventSystem\Dispatcher\QueuedDispatchStrategy.h"
#include ".\EventSystem\Listener\Strategy\SaveListenerStrategy.h"
#include ".\EventSystem\Event\KeyDownEvent.h"

using namespace std;

int main()
{
	cout << "--- Event System ---" << endl;

	EventManager mngr(new QueuedDispatchStrategy(), new SaveListenerStrategy());
	Player* player = new Player("player");

	mngr.addEventListener(KeyDownEvent::KEY_DOWN_EVENT_TYPE, static_cast<void (Player::*)(KeyDownEvent&)>(&Player::handleEvent), player);
	mngr.dispatchEvent(std::make_unique<KeyDownEvent>(38));	// 38 == up arrow
	mngr.update();

	return 0;
}
