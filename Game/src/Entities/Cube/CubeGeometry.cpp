
#include "CubeGeometry.h"


using namespace sag;
using namespace sagame;


CubeGeometry::CubeGeometry()
{
	const unsigned int vertexCnt = 24;
	float sideLength = 0.5f;

	float v[vertexCnt * 3] = {
		// Front
		-sideLength, -sideLength, sideLength,
		sideLength, -sideLength, sideLength,
		sideLength,  sideLength, sideLength,
		-sideLength,  sideLength, sideLength,
		// Right
		sideLength, -sideLength, sideLength,
		sideLength, -sideLength, -sideLength,
		sideLength,  sideLength, -sideLength,
		sideLength,  sideLength, sideLength,
		// Back
		-sideLength, -sideLength, -sideLength,
		-sideLength,  sideLength, -sideLength,
		sideLength,  sideLength, -sideLength,
		sideLength, -sideLength, -sideLength,
		// Left
		-sideLength, -sideLength, sideLength,
		-sideLength,  sideLength, sideLength,
		-sideLength,  sideLength, -sideLength,
		-sideLength, -sideLength, -sideLength,
		// Bottom
		-sideLength, -sideLength, sideLength,
		-sideLength, -sideLength, -sideLength,
		sideLength, -sideLength, -sideLength,
		sideLength, -sideLength, sideLength,
		// Top
		-sideLength,  sideLength, sideLength,
		sideLength,  sideLength, sideLength,
		sideLength,  sideLength, -sideLength,
		-sideLength,  sideLength, -sideLength
	};

	float n[vertexCnt * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Right
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		// Back
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		// Left
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		// Bottom
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		// Top
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	float tex[vertexCnt * 2] = {
		// Front
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Right
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Back
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Left
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Bottom
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Top
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	GLuint el[] = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	unsigned int handle[4];
	glGenBuffers(4, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexCnt * 3 * sizeof(float), v, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, vertexCnt * 3 * sizeof(float), n, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ARRAY_BUFFER, vertexCnt * 2 * sizeof(float), tex, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(2);  // Texture coords

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), el, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void CubeGeometry::draw()
{
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
