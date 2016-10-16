#include "glslHelper.h"


using namespace sag;

GLuint glslHelper::makeShader(GLenum shaderType, const char* source, GLint sourceLength)
{
	GLuint shader;
	GLint shader_ok;
	GLsizei log_length;
	char info_log[8192];

	shader = glCreateShader(shaderType);
	if (shader != 0)
	{
		glShaderSource(shader, 1, &source, &sourceLength);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
		if (shader_ok != GL_TRUE)
		{
			std::string shaderTypeName;
			switch (shaderType)
			{
			case GL_FRAGMENT_SHADER:
				shaderTypeName = "fragment";
				break;
			case GL_VERTEX_SHADER:
				shaderTypeName = "vertex";
				break;
			default:
				shaderTypeName = "unspecified";
				break;
			}
			std::cerr << "ERROR: Failed to compile " << shaderTypeName << " shader\n" << std::endl;
			glGetShaderInfoLog(shader, 8192, &log_length, info_log);
			std::cerr << "ERROR: \n%s\n\n" << info_log << std::endl;
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}


GLuint glslHelper::makeShaderProgram(const char* vsSource, GLint vsLen, const char* fsSource, GLint fsLen)
{
	GLuint program = 0u;
	GLint program_ok;
	GLuint vertex_shader = 0u;
	GLuint fragment_shader = 0u;
	GLsizei log_length;
	char info_log[8192];

	vertex_shader = glslHelper::makeShader(GL_VERTEX_SHADER, vsSource, vsLen);
	if (vertex_shader != 0u)
	{
		fragment_shader = glslHelper::makeShader(GL_FRAGMENT_SHADER, fsSource, fsLen);
		if (fragment_shader != 0u)
		{
			/* make the program that connect the two shader and link it */
			program = glCreateProgram();
			if (program != 0u)
			{
				/* attach both shader and link */
				glAttachShader(program, vertex_shader);
				glAttachShader(program, fragment_shader);
				glLinkProgram(program);
				glGetProgramiv(program, GL_LINK_STATUS, &program_ok);

				if (program_ok != GL_TRUE)
				{
					std::cerr << "ERROR, failed to link shader program\n" << std::endl;
					glGetProgramInfoLog(program, 8192, &log_length, info_log);
					std::cerr << "ERROR: \n%s\n\n" << std::endl;
					glDeleteProgram(program);
					glDeleteShader(fragment_shader);
					glDeleteShader(vertex_shader);
					program = 0u;
				}
			}
		}
		else
		{
			std::cerr << "ERROR: Unable to load fragment shader\n" << std::endl;
			glDeleteShader(vertex_shader);
		}
	}
	else
	{
		std::cerr << "ERROR: Unable to load vertex shader\n" << std::endl;
	}
	return program;
}
