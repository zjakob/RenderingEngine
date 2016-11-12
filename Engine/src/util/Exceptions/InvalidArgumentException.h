#ifndef SAG_INVALIDA_ARGUMENT_EXCEPTION_H
#define SAG_INVALIDA_ARGUMENT_EXCEPTION_H

#include <stdexcept>

namespace sag
{

class InvalidArgumentException : public std::runtime_error {
public:
	InvalidArgumentException(const std::string& msg) : std::runtime_error(msg) { }
};

} // namespace sag


#endif // SAG_INVALIDA_ARGUMENT_EXCEPTION_H
