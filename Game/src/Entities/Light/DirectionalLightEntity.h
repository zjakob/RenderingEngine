#ifndef SAGAME_LIGHTENTITY_H
#define SAGAME_LIGHTENTITY_H

#include <GL/glew.h>

#include <Render/RenderableObject.h>
#include <Scene/SceneNode.h>
#include <Render/Light/DirectionalLight.h>
#include <Render/Renderer/RenderPass/RenderPassData.h>

#include <memory>


namespace sagame
{

class DirectionalLightEntity : public sag::RenderableObject
{
public:
	DirectionalLightEntity(glm::vec3 center, float fovyDeg, float aspect);

	void render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<sag::Light*>& lights, sag::RenderPassData* renderPassDataExchange) override;

	void setDirectionalLightCenter(const glm::vec3& center) { this->light.setCenter(center); }
	void setPosition(const glm::vec3& position);
	void rotate(float angle, glm::vec3& rotationAxis);

	sag::Light& getLight()
	{
		return light;
	}

private:
	std::weak_ptr<sag::SceneNode> translationNode;
	std::weak_ptr<sag::SceneNode> rotationNode;
	sag::DirectionalLight light;


};

} // namespace sagame


#endif // SAGAME_LIGHTENTITY_H
