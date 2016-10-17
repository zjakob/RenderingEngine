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

Material& Material::operator=(Material&& other)
{
	this->shader = std::move(other.shader);
	return *this;
}

Material::~Material()
{
}

Material::Material(Material&& other) :
	shader(std::move(other.shader))
{
}
