#include "ioHelper.h"


using namespace sag;

void ioHelper::loadFromFile(const std::string &filename, char** shaderSource, int& shaderLength)
{
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.good())
	{
		throw std::exception("Failed to open file!");
	}

	// Create a string stream
	std::stringstream stream;

	// Dump the contents of the file into it
	stream << file.rdbuf();

	// Close the file
	file.close();

	// Convert the StringStream into a string
	std::string source = stream.str();

	shaderLength = source.size();

	*shaderSource = new char[shaderLength];
	// Get the source string as a pointer to an array of characters
	memcpy(*shaderSource, const_cast<char*>(source.c_str()), shaderLength);
}
