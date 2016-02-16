#ifndef IO_HELPER
#define IO_HELPER

#include <fstream>
#include <string>
#include <sstream>

#include <iostream>

namespace ioHelper
{
	/**
	 * Method to load the shader contents from a string
	 */
	void loadFromFile(const std::string &filename, char** shaderSource, int& shaderLength);
}

#endif // IO_HELPER