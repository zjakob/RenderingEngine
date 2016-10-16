
#include "ComparableObject.h"


using namespace sag;

unsigned int ComparableObject::idCnt = 0;

bool sag::operator== (const ComparableObject &n1, const ComparableObject &n2)
{
	return n1.id == n2.id;
}

bool sag::operator!= (const ComparableObject &n1, const ComparableObject &n2)
{
	return !(n1 == n2);
}

ComparableObject::ComparableObject() :
	id(idCnt++)
{

}
