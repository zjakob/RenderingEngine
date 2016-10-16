#ifndef SAG_GL_HELPER
#define SAG_GL_HELPER

#include <iostream>
#include <string>

#include <GL/glew.h>

namespace sag
{
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

} // namespace glslHelper

} // namespace sag


#endif // SAG_GL_HELPER