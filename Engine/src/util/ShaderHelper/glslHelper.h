#ifndef GL_HELPER
#define GL_HELPER

#include <iostream>
#include <string>

#include <GL/glew.h>

namespace glslHelper
{
	/** 
	 * Creates a program object using the specified vertex and fragment text
	 */
	GLuint makeShader(GLenum shaderType, const char* source, GLint sourceLength);

	/**
	 * Creates a shader object of the specified type using the specified text
	 */
	GLuint makeShaderProgram(const char* vsSource, GLint vsLen, const char* fsSource, GLint fsLen);
}

#endif // GL_HELPER