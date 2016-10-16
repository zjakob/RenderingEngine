#ifndef SAG_OPENGL_EXCEPTION_H
#define SAG_OPENGL_EXCEPTION_H

#include <stdexcept>
#include <string>


namespace sag
{

class OpenGLException : public std::runtime_error
{
public:
	explicit OpenGLException(const std::string& what_arg) : std::runtime_error(what_arg) { }

private:
};

} // namespace sag


#endif // SAG_OPENGL_EXCEPTION_H