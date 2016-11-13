#ifndef SAGAME_FLOOR_GEOMETRY_H
#define SAGAME_FLOOR_GEOMETRY_H

#include <Render/Geometry/Geometry.h>
#include <vector>
#include <GL/glew.h>


namespace sagame
{

class FloorGeometry : public sag::Geometry
{
public:
	FloorGeometry();

	virtual void draw();

private:
	unsigned int vaoHandle;

};

} // namespace sagame


#endif // SAGAME_FLOOR_GEOMETRY_H
