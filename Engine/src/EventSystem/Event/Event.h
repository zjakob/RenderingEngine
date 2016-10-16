#ifndef SAG_EVENT_H
#define SAG_EVENT_H

#include <string>


namespace sag
{

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

} // namespace sag


#endif // SAG_EVENT_H
