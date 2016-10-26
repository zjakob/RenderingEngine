
#include "SphereGeometry.h"

#include <glm/gtc/constants.hpp>
#include <cmath>

using namespace sag;
using namespace sagame;


SphereGeometry::SphereGeometry(float radius, GLuint axisSubdivision, GLuint heightSubdivision) :
	radius(radius), axisSubdivision(axisSubdivision), heightSubdivision(heightSubdivision)
{
	nVerts = (axisSubdivision + 1) * (heightSubdivision + 1);
	elements = (axisSubdivision * 2 * (heightSubdivision - 1)) * 3;

	// Verts
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];
	// Tex coords
	float * tex = new float[2 * nVerts];
	// Elements
	unsigned int * el = new unsigned int[elements];

	// Generate the vertex data
	generateVerts(v, n, tex, el);

	// Create and populate the buffer objects
	unsigned int handle[4];
	glGenBuffers(4, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ARRAY_BUFFER, (2 * nVerts) * sizeof(float), tex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), el, GL_STATIC_DRAW);

	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	// Create the VAO
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);  // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);  // Vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glEnableVertexAttribArray(2);  // Texture coords
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);

	glBindVertexArray(0);
}

void SphereGeometry::generateVerts(float* verts, float* norms, float* tex, unsigned int* el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / axisSubdivision;
	GLfloat phiFac = glm::pi<float>() / heightSubdivision;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= axisSubdivision; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / axisSubdivision;
		for (GLuint j = 0; j <= heightSubdivision; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / heightSubdivision;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx; verts[idx + 1] = radius * ny; verts[idx + 2] = radius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (GLuint i = 0; i < axisSubdivision; i++) {
		GLuint heightSubdivisiontart = i * (heightSubdivision + 1);
		GLuint nextheightSubdivisiontart = (i + 1) * (heightSubdivision + 1);
		for (GLuint j = 0; j < heightSubdivision; j++) {
			if (j == 0) {
				el[idx] = heightSubdivisiontart;
				el[idx + 1] = heightSubdivisiontart + 1;
				el[idx + 2] = nextheightSubdivisiontart + 1;
				idx += 3;
			}
			else if (j == heightSubdivision - 1) {
				el[idx] = heightSubdivisiontart + j;
				el[idx + 1] = heightSubdivisiontart + j + 1;
				el[idx + 2] = nextheightSubdivisiontart + j;
				idx += 3;
			}
			else {
				el[idx] = heightSubdivisiontart + j;
				el[idx + 1] = heightSubdivisiontart + j + 1;
				el[idx + 2] = nextheightSubdivisiontart + j + 1;
				el[idx + 3] = nextheightSubdivisiontart + j;
				el[idx + 4] = heightSubdivisiontart + j;
				el[idx + 5] = nextheightSubdivisiontart + j + 1;
				idx += 6;
			}
		}
	}
}

void SphereGeometry::draw()
{
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
