#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <glm/mat4x4.hpp>
#include <GL/glew.h>

#include "Shader/GlslShaderProgram.h"

class Material
{
public:
	Material(GlslShaderProgram&& shader);
	~Material();
	Material(Material&& other);
	
	void apply(const glm::mat4& viewProjectionMatrix);

private:
	GlslShaderProgram shader;

};

#endif // _MATERIAL_H
