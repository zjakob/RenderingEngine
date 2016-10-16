#include "Material.h"

#include <glm/gtc/type_ptr.hpp>
#include <utility>

#include "..\..\util\ShaderHelper\glslHelper.h"


using namespace sag;

Material::Material()
{

}

Material::Material(GlslShaderProgram&& shader) :
	shader(std::move(shader))
{
}

Material::~Material()
{
}

Material::Material(Material&& other) :
	shader(std::move(other.shader))
{
}

void Material::setShader(GlslShaderProgram&& shader)
{
	this->shader = std::move(shader);
}

void Material::apply(const glm::mat4& viewProjectionMatrix)
{
	shader.use();
	shader.setUniform("mvp", viewProjectionMatrix);
}
