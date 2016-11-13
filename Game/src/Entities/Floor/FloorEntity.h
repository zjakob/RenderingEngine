#ifndef SAGAME_FLOOR_H
#define SAGAME_FLOOR_H

#include <GL/glew.h>

#include <Render\RenderableObject.h>
#include <Scene\SceneNode.h>
#include <Render/Light/Light.h>
#include <Render/Renderer/RenderPass/RenderPassData.h>

#include <memory>


namespace sagame
{

class FloorEntity : public sag::RenderableObject
{
public:
	FloorEntity();

	void render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<sag::Light*>& lights, sag::RenderPassData* renderPassDataExchange) override;

	void setPosition(glm::vec3& position);
	void scale(glm::vec3& scale);

private:
	std::weak_ptr<sag::SceneNode> sceneNode;


};

} // namespace sagame


#endif // SAGAME_FLOOR_H
