
#include "Geometry.h"


Geometry::Geometry()
{

}

Geometry::Geometry(std::vector<GLfloat>&& vertexPositions, std::vector<GLushort>&& vertexIndices)
	: vertexPositions(std::move(vertexPositions)), vertexIndices(std::move(vertexIndices))
{
	init();
}

Geometry::~Geometry()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Geometry::init()
{
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		vertexPositions.size() * sizeof(GLfloat),
		this->vertexPositions.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		this->vertexIndices.size() * sizeof(GLushort),
		this->vertexIndices.data(),
		GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Geometry::setVertices(std::vector<GLfloat>&& vertexPositions, std::vector<GLushort>&& vertexIndices)
{
	this->vertexPositions = std::move(vertexPositions);
	this->vertexIndices = std::move(vertexIndices);

	init();
}

void Geometry::draw()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}
