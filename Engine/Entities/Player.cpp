#include "Player.h"

#include <iostream>

#include "..\EventSystem\Event\KeyUpEvent.h"


void Player::processEvent(Event* event)
{
	if (KeyUpEvent* keyUpEvent = dynamic_cast<KeyUpEvent*>(event))
	{
		switch (keyUpEvent->getKey())
		{
		case 38:	// up arrow
			moveUp();
			break;
		}
	}
}

void Player::moveUp()
{
	std::cout << "player moves up" << std::endl;
}
