#ifndef SAG_IO_HELPER
#define SAG_IO_HELPER

#include <fstream>
#include <string>
#include <sstream>

#include <iostream>


namespace sag
{
namespace ioHelper
{

/**
 * Method to load the shader contents from a string
 */
void loadFromFile(const std::string &filename, char** shaderSource, int& shaderLength);

} // namespace ioHelper
} // namespace sag


#endif // SAG_IO_HELPER