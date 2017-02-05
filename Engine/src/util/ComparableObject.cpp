
#include "ComparableObject.h"


using namespace sag;

unsigned int ComparableObject::idCnt = 0;

ComparableObject::ComparableObject() :
	id(idCnt++)
{

}