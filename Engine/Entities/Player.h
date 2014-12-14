#ifndef PLAYER_H
#define PLAYER_H

#include "..\EventSystem\Listener\EventListener.h"
#include "..\EventSystem\Event\KeyUpEvent.h"
#include "..\EventSystem\Event\KeyDownEvent.h"

class Player : public EventListener<KeyUpEvent>, EventListener<KeyDownEvent>
{
public:
	Player();

	virtual void handleEvent(KeyUpEvent& event);
	virtual void handleEvent(KeyDownEvent& event);
	virtual const std::string& getName() const;

private:
	std::string name;

	void moveUp();
	void moveDown();
};

#endif