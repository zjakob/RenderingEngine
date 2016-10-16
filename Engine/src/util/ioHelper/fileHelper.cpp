#include "fileHelper.h"


using namespace sag;

std::string fileHelper::readFile(const char* filename)
{
	std::ifstream file;
	file.open(filename);
	if (!file.good())
	{
		throw FileHelperException("Failed to open file!");
	}

	// Create a string stream
	std::stringstream stream;

	// Dump the contents of the file into it
	stream << file.rdbuf();

	// Close the file
	file.close();

	return stream.str();
}
