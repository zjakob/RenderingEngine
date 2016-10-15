
#include "../../../util/ioHelper/ioHelper.h"
#include "../../../util/ShaderHelper/glslHelper.h"

#include "GlslShaderProgram.h"


GlslShaderProgram::GlslShaderProgram(const std::string vertexShaderFile, const std::string fragmentShaderFile) :
	vertexShaderFile(vertexShaderFile), fragmentShaderFile(fragmentShaderFile)
{
	char* vsSource;
	GLint vsLen;
	ioHelper::loadFromFile(vertexShaderFile, &vsSource, vsLen);
	char* fsSource;
	GLint fsLen;
	ioHelper::loadFromFile(fragmentShaderFile, &fsSource, fsLen);
	this->shaderProgram = glslHelper::makeShaderProgram(vsSource, vsLen, fsSource, fsLen);
}

GlslShaderProgram::~GlslShaderProgram()
{
	if (this->shaderProgram >= 0)
		glDeleteProgram(this->shaderProgram);
}

GlslShaderProgram::GlslShaderProgram(GlslShaderProgram&& other) :
	vertexShaderFile(std::move(other.vertexShaderFile)),
	fragmentShaderFile(std::move(other.fragmentShaderFile)),
	shaderProgram(std::move(other.shaderProgram))
{
	other.shaderProgram = -1; // avoid deletion of shader when invoking the other-destructor after move
}

GlslShaderProgram& GlslShaderProgram::operator=(GlslShaderProgram&& other)
{
	this->vertexShaderFile = std::move(other.vertexShaderFile);
	this->fragmentShaderFile = std::move(other.fragmentShaderFile);
	this->shaderProgram = std::move(other.shaderProgram);

	other.shaderProgram = -1; // avoid deletion of shader when invoking the other-destructor after move

	return *this;
}

void GlslShaderProgram::setUniformMatrix4fv(const std::string name, const GLfloat* value)
{
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);
}
