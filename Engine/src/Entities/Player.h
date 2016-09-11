#ifndef PLAYER_H
#define PLAYER_H

#include "IEntity.h"
#include "..\EventSystem\Event\KeyDownEvent.h"
#include "..\EventSystem\Event\EntityMovedEvent.h"

class Player : public IEntity
{
public:
	Player(std::string name);

	virtual void handleKeyDownEvent(KeyDownEvent& event);

	virtual const std::string& getId() const;

private:
	std::string name;

	void moveUp();
	void moveDown();
};

#endif // PLAYER_H