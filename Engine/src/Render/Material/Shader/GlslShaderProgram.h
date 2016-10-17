#ifndef SAG_GLSL_SHADER_PROGRAM_H
#define SAG_GLSL_SHADER_PROGRAM_H

#include <string>
#include <stdexcept>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <unordered_map>

namespace sag
{


class GlslShaderProgramException : public std::runtime_error {
public:
	GlslShaderProgramException(const std::string& msg) : std::runtime_error(msg) { }
};


enum GlslShaderType {
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	TESS_CONTROL = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	COMPUTE = GL_COMPUTE_SHADER
};


class GlslShaderProgram
{
public:
	GlslShaderProgram();
	GlslShaderProgram(GlslShaderProgram&& other);
	GlslShaderProgram& operator=(GlslShaderProgram&& other);
	GlslShaderProgram(const GlslShaderProgram& other) = default;
	GlslShaderProgram& operator=(const GlslShaderProgram& other) = default;
	~GlslShaderProgram();

	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::vec3& v);
	void setUniform(const char* name, const glm::vec4& v);
	void setUniform(const char* name, const glm::mat3& m);
	void setUniform(const char* name, const glm::mat4& m);
	int getUniformLocation(const char* name);

	GLint getAttribLocation(const char* name);
	void bindAttribLocation(GLuint location, const char* name);
	void bindFragDataLocation(GLuint location, const char* name);

	void attachShader(const char* file, GlslShaderType type);
	void link();
	void use() const;

private:
	GLuint shaderProgramHandle;
	bool linked;
	std::unordered_map<std::string, int> uniformLocations;

	GLuint compileShader(const std::string& shaderSource, GlslShaderType type);

};

} // namespace sag


#endif // SAG_GLSL_SHADER_PROGRAM_H
