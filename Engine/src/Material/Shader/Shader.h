#ifndef _SHADER_H
#define _SHADER_H

#include <string>

class Shader
{
private:
	std::string shaderFilePath;

public:
	char** shaderSource;
	int shaderLength;

	Shader(std::string shaderFilePath);

	void init();

};

#endif // _SHADER_H
