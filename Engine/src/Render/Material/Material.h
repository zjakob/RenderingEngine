#ifndef SAG_MATERIAL_H
#define SAG_MATERIAL_H

#include <glm/mat4x4.hpp>
#include <GL/glew.h>

#include "Shader/GlslShaderProgram.h"


namespace sag
{

class Material
{
public:
	Material();
	Material(GlslShaderProgram&& shader);
	~Material();
	Material(Material&& other);
	
	void setShader(GlslShaderProgram&& shader);
	void apply(const glm::mat4& viewProjectionMatrix);

private:
	GlslShaderProgram shader;

};

} // namespace sag


#endif // SAG_MATERIAL_H
