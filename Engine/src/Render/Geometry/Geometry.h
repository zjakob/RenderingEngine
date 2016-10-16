#ifndef SAG_GEOMETRY_H
#define SAG_GEOMETRY_H

#include <vector>

#include <GL/glew.h>


namespace sag
{

class Geometry
{
public:
	Geometry();
	Geometry(std::vector<GLfloat>&& vertexPositions, std::vector<GLushort>&& vertexIndices);
	virtual ~Geometry();

	void setVertices(std::vector<GLfloat>&& vertexPositions, std::vector<GLushort>&& vertexIndices);
	void draw();

private:
	std::vector<GLfloat> vertexPositions;
	std::vector<GLushort> vertexIndices;

	GLuint vertexArrayObject;
	GLuint positionBuffer;
	GLuint indexBuffer;

	void init();

};

} // namespace sag


#endif // SAG_GEOMETRY_H
