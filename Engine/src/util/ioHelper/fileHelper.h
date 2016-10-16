#ifndef SAG_IO_HELPER
#define SAG_IO_HELPER

#include <fstream>
#include <string>
#include <sstream>

#include <iostream>


namespace sag
{
namespace fileHelper
{

class FileHelperException : public std::runtime_error {
public:
	FileHelperException(const std::string& msg) : std::runtime_error(msg) { }
};

/**
 * Method to load the shader contents from a string
 */
std::string readFile(const char* filename);

} // namespace fileHelper
} // namespace sag


#endif // SAG_IO_HELPER
