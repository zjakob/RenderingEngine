#ifndef PLAYER_H
#define PLAYER_H

#include "IEntity.h"
#include "..\EventSystem\Listener\EventListener.h"
#include "..\EventSystem\Event\KeyDownEvent.h"
#include "..\EventSystem\Event\EntityMovedEvent.h"

class Player : public IEntity, EventListener<KeyDownEvent>, EventListener<EntityMovedEvent>
{
public:
	Player(std::string name);

	virtual const std::string& getId() const;
	virtual void handleEvent(KeyDownEvent& event);
	virtual void handleEvent(EntityMovedEvent& event);

private:
	std::string name;

	void moveUp();
	void moveDown();
};

#endif