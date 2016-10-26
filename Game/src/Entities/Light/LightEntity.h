#ifndef SAGAME_LIGHTENTITY_H
#define SAGAME_LIGHTENTITY_H

#include <GL/glew.h>

#include <Render\Scene\RenderableObject.h>
#include <Render\Scene\SceneNode.h>
#include <Render\Light.h>

#include <memory>


namespace sagame
{

class LightEntity : public sag::RenderableObject
{
public:
	LightEntity();

	void render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<sag::Light*>& lights) override;

	void setPosition(glm::vec3& position);
	void rotate(float angle, glm::vec3& rotationAxis);

	sag::Light& getLight()
	{
		return light;
	}

private:
	std::weak_ptr<sag::SceneNode> translationNode;
	std::weak_ptr<sag::SceneNode> rotationNode;
	sag::Light light;


};

} // namespace sagame


#endif // SAGAME_LIGHTENTITY_H
