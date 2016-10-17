
#include "../../../util/ioHelper/fileHelper.h"

#include "GlslShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>
#include <cassert>


using namespace sag;

GlslShaderProgram::GlslShaderProgram() :
	linked(false)
{
	if (shaderProgramHandle <= 0)
	{
		shaderProgramHandle = glCreateProgram();
		if (shaderProgramHandle == 0)
			throw GlslShaderProgramException("Unable to create shader program.");
	}
}

GlslShaderProgram::~GlslShaderProgram()
{
	if (shaderProgramHandle == 0) return;

	// Query the number of attached shaders
	GLint numShaders = 0;
	glGetProgramiv(shaderProgramHandle, GL_ATTACHED_SHADERS, &numShaders);

	// Get the shader names
	GLuint* shaderNames = new GLuint[numShaders];
	glGetAttachedShaders(shaderProgramHandle, numShaders, NULL, shaderNames);

	// Delete the shaders
	for (int i = 0; i < numShaders; i++)
		glDeleteShader(shaderNames[i]);

	// Delete the program
	glDeleteProgram(shaderProgramHandle);

	delete[] shaderNames;
}

GlslShaderProgram::GlslShaderProgram(GlslShaderProgram&& other) :
	shaderProgramHandle(other.shaderProgramHandle)
{
	other.shaderProgramHandle = 0; // avoid deletion of shader when invoking the other-destructor after move
}

GlslShaderProgram& GlslShaderProgram::operator=(GlslShaderProgram&& other)
{
	this->shaderProgramHandle = other.shaderProgramHandle;
	other.shaderProgramHandle = 0; // avoid deletion of shader when invoking the other-destructor after move
	return *this;
}

void GlslShaderProgram::setUniform(const char* name, float x, float y, float z)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc, x, y, z);
}

void GlslShaderProgram::setUniform(const char* name, const glm::vec3& v)
{
	this->setUniform(name, v.x, v.y, v.z);
}

void GlslShaderProgram::setUniform(const char* name, const glm::vec4& v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void GlslShaderProgram::setUniform(const char* name, const glm::mat3& m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GlslShaderProgram::setUniform(const char* name, const glm::mat4& m)
{
	GLint uniformLocation = glGetUniformLocation(this->shaderProgramHandle, name);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
}

int GlslShaderProgram::getUniformLocation(const char* name)
{
	std::unordered_map<std::string, int>::const_iterator pos;
	pos = uniformLocations.find(name);

	if (pos == uniformLocations.end())
	{
		uniformLocations[name] = glGetUniformLocation(shaderProgramHandle, name);
	}

	return uniformLocations[name];
}

GLint GlslShaderProgram::getAttribLocation(const char* name)
{
	return glGetAttribLocation(shaderProgramHandle, name);
}

void GlslShaderProgram::bindAttribLocation(GLuint location, const char* name)
{
	glBindAttribLocation(shaderProgramHandle, location, name);
}

void GlslShaderProgram::bindFragDataLocation(GLuint location, const char* name)
{
	glBindFragDataLocation(shaderProgramHandle, location, name);
}

void GlslShaderProgram::attachShader(const char* file, GlslShaderType type)
{
	assert(shaderProgramHandle > 0 && "Shader program needs to be created before a shader can be attached.");

	std::string shaderSource = fileHelper::readFile(file);

	int shaderHandle = compileShader(shaderSource, type);

	glAttachShader(shaderProgramHandle, shaderHandle);
}

GLuint GlslShaderProgram::compileShader(const std::string& shaderSource, GlslShaderType type)
{
	GLuint shaderHandle = glCreateShader(type);

	const char* shaderSourceChar = shaderSource.c_str();
	glShaderSource(shaderHandle, 1, &shaderSourceChar, NULL);

	// Compile the shader
	glCompileShader(shaderHandle);

	// Check for errors
	int result;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		// Compile failed, get log
		int length = 0;
		std::string msg = "Shader compilation failed: ";
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			char* log = new char[length];
			int written = 0;
			glGetShaderInfoLog(shaderHandle, length, &written, log);
			msg += log;
			delete[] log;
		}
		throw GlslShaderProgramException(msg);
	}

	return shaderHandle;
}

void GlslShaderProgram::link()
{
	assert(shaderProgramHandle > 0 && "Shader program needs to be created before it can be linked.");
	assert(!this->linked && "Shader has already been linked.");

	glLinkProgram(shaderProgramHandle);

	int status = 0;
	glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status)
	{
		// Store log and return false
		int length = 0;
		std::string msg = "Program link failed: ";
		glGetProgramiv(shaderProgramHandle, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			char* log = new char[length];
			int written = 0;
			glGetProgramInfoLog(shaderProgramHandle, length, &written, log);
			msg += log;
			delete[] log;
		}
		throw GlslShaderProgramException(msg);
	}
	else
	{
		uniformLocations.clear();
		linked = true;
	}
}

void GlslShaderProgram::use() const
{
	assert(shaderProgramHandle > 0 && "Shader program needs to be created before it can be used.");
	assert(this->linked && "Shader has already been linked.");

	glUseProgram(shaderProgramHandle);
}
