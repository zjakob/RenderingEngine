#include "Player.h"

#include <iostream>

#include "..\EventSystem\Event\KeyDownEvent.h"

Player::Player(std::string name)
{
	this->name = name;
}

void Player::handleKeyDownEvent(KeyDownEvent& event)
{
	switch (event.getKey())
	{
	default:
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

const std::string& Player::getId() const
{
	return name;
}
