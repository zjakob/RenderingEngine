#ifndef SAG_GLSL_SHADER_PROGRAM_H
#define SAG_GLSL_SHADER_PROGRAM_H

#include <string>

#include <GL/glew.h>


namespace sag
{

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

} // namespace sag


#endif // SAG_GLSL_SHADER_PROGRAM_H
