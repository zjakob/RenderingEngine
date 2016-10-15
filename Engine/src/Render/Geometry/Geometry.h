#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

#include <GL/glew.h>

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

#endif // GEOMETRY_H
