
#include "ComparableObject.h"


unsigned int ComparableObject::idCnt = 0;


bool operator== (const ComparableObject &n1, const ComparableObject &n2)
{
	return n1.id == n2.id;
}

bool operator!= (ComparableObject &n1, ComparableObject &n2)
{
	return !(n1 == n2);
}

ComparableObject::ComparableObject() :
	id(idCnt++)
{

}
