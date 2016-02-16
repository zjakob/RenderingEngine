#ifndef _MATH_UTIL_H
#define _MATH_UTIL_H

#define _USE_MATH_DEFINES
#include <math.h>

static float degreeToRadians(float degree)
{
	return (degree * (float)M_PI) / 180.0f;
}

#endif // _MATH_UTIL_H