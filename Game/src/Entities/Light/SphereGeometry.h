#ifndef SAGAME_SPHERE_GEOMETRY_H
#define SAGAME_SPHERE_GEOMETRY_H

#include <Render/Geometry/Geometry.h>
#include <vector>
#include <GL/glew.h>


namespace sagame
{

class SphereGeometry : public sag::Geometry
{
public:
	SphereGeometry(float radius, GLuint axisSubdivision, GLuint heightSubdivision);

	virtual void draw();

private:
	unsigned int vaoHandle;
	GLuint nVerts, elements;
	float radius;
	GLuint axisSubdivision;
	GLuint heightSubdivision;

	void generateVerts(float* verts, float* norms, float* tex, unsigned int* el);

};

} // namespace sagame


#endif // SAGAME_SPHERE_GEOMETRY_H
