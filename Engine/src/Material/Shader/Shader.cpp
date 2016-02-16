#include "Shader.h"

#include "..\..\util\ioHelper\ioHelper.h"

Shader::Shader(std::string shaderFilePath)
{
	this->shaderFilePath = shaderFilePath;
}

void Shader::init()
{
	ioHelper::loadFromFile(shaderFilePath, shaderSource, shaderLength);
}
