#ifndef PORTABLE_PIXMAP_IMAGE_HELPER_H
#define PORTABLE_PIXMAP_IMAGE_HELPER_H

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace PortablePixMapImageHelper
{

void writePortablePixmap(string outputFileName, unsigned char* data, unsigned int width, unsigned int height)
{
	ofstream outputStream(outputFileName, std::ofstream::out | ios::binary);
	ostringstream header;
	header << "P6\n" << "# SAG Engine\n" << width << " " << height << "\n" << 0xFF << "\n";
	outputStream.write(header.str().c_str(), header.str().size());
	outputStream.write(reinterpret_cast<char*>(data), width * height * 3);
	outputStream.close();
}

};

#endif // PORTABLE_PIXMAP_IMAGE_HELPER_H
