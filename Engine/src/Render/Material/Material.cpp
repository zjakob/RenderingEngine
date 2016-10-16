#include "Material.h"

#include <glm/gtc/type_ptr.hpp>
#include <utility>

#include "..\..\util\ShaderHelper\glslHelper.h"


using namespace sag;

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

void Material::apply(const glm::mat4& viewProjectionMatrix)
{
	glUseProgram(shader.getShaderProgram());
	shader.setUniformMatrix4fv("mvp", glm::value_ptr(viewProjectionMatrix));
}
