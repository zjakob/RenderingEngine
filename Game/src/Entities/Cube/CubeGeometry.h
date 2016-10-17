#ifndef SAGAME_CUBE_GEOMETRY_H
#define SAGAME_CUBE_GEOMETRY_H

#include <Render\Geometry\Geometry.h>
#include <vector>
#include <GL/glew.h>


namespace sagame
{

class CubeGeometry : public sag::Geometry
{
public:
	CubeGeometry();

	virtual void draw();

private:
	unsigned int vaoHandle;

};

} // namespace sagame


#endif // SAGAME_CUBE_GEOMETRY_H
