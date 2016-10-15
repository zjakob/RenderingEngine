#ifndef OPENGL_EXCEPTION_H
#define OPENGL_EXCEPTION_H

#include <stdexcept>
#include <string>


class OpenGLException : public std::runtime_error
{
public:
	explicit OpenGLException(const std::string& what_arg) : std::runtime_error(what_arg)
	{

	}

private:
};

#endif // OPENGL_EXCEPTION_H