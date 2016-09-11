#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
private:
	static int idCnt;

public:
	Event() : id(idCnt++)
	{
	}

	virtual int eventId() const
	{
		return id;
	}

protected:
	const int id;

};

#endif // EVENT_H
