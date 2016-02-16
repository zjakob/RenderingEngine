#ifndef _MATERIAL_H
#define _MATERIAL_H

#include ".\Shader\Shader.h"

class Material
{
private:


public:
	short* vertexIndices;
	float* vertexPositions;

	Shader* vsShader;
	Shader* fsShader;

	Material();
	
	void init();

};

#endif // _MATERIAL_H
