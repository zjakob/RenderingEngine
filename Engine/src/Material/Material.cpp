#include "Material.h"

#include "..\util\ShaderHelper\glslHelper.h"

void Material::init()
{
	GLuint shaderProg = glslHelper::makeShaderProgram(*vsShader->shaderSource, vsShader->shaderLength, *fsShader->shaderSource, fsShader->shaderLength);

}
