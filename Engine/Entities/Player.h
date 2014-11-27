#ifndef PLAYER_H
#define PLAYER_H

#include "..\EventSystem\Listener\KeyEventListener.h"

class Player : public KeyEventListener
{
public:
	virtual void processEvent(Event* event);

private:
	void moveUp();
};

#endif