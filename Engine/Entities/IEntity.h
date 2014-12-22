#ifndef ENITY_H
#define ENITY_H

#include <string>

class IEntity
{
public:
	virtual const std::string& getId() const = 0;
};

#endif