#include "Player.h"

#include <iostream>

#include "..\EventSystem\Event\KeyDownEvent.h"

Player::Player(std::string name)
{
	this->name = name;
}

void Player::handleEvent(KeyDownEvent& event)
{
	switch (event.getKey())
	{
	case 38:	// up arrow
		moveUp();
		break;
	case 40:	// up arrow
		moveDown();
		break;
	}
}

void Player::handleEvent(EntityMovedEvent& event)
{
}

void Player::moveUp()
{
	std::cout << "player moves up" << std::endl;
}

void Player::moveDown()
{
	std::cout << "player moves down" << std::endl;
}

const std::string& Player::getId() const
{
	return name;
}
