#include "Player.h"

#include <iostream>


Player::Player()
{
	name = "player";
}

void Player::handleEvent(KeyUpEvent& event)
{
	switch (event.getKey())
	{
	case 38:	// up arrow
		moveUp();
		break;
	}
}

void Player::handleEvent(KeyDownEvent& event)
{
	switch (event.getKey())
	{
	case 40:	// up arrow
		moveDown();
		break;
	}
}

void Player::moveUp()
{
	std::cout << "player moves up" << std::endl;
}

void Player::moveDown()
{
	std::cout << "player moves down" << std::endl;
}

const std::string& Player::getName() const
{
	return name;
}
