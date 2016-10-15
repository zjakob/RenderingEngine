#ifndef _GLSL_SHADER_PROGRAM_H
#define _GLSL_SHADER_PROGRAM_H

#include <string>

#include <GL/glew.h>

class GlslShaderProgram
{
public:
	GlslShaderProgram(const std::string vertexShader, const std::string fragmentShader);
	GlslShaderProgram(GlslShaderProgram&& other);
	GlslShaderProgram& operator=(GlslShaderProgram&& other);
	GlslShaderProgram(const GlslShaderProgram& other) = default;
	GlslShaderProgram& operator=(const GlslShaderProgram& other) = default;
	~GlslShaderProgram();

	void setUniformMatrix4fv(const std::string name, const GLfloat *value);

	const GLuint getShaderProgram() const
	{
		return shaderProgram;
	}

private:
	std::string vertexShaderFile;
	std::string fragmentShaderFile;

	GLuint shaderProgram;

};

#endif // _GLSL_SHADER_PROGRAM_H
