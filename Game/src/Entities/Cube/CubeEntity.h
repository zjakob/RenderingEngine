#ifndef SAGAME_CUBE_H
#define SAGAME_CUBE_H

#include <GL/glew.h>

#include <Render/RenderableObject.h>
#include <Scene/SceneNode.h>
#include <Render/Light/Light.h>
#include <Render/Renderer/RenderPass/RenderPassData.h>

#include <memory>


namespace sagame
{

class CubeEntity : public sag::RenderableObject
{
public:
	CubeEntity();

	void render(const glm::mat4& view, const glm::mat4& viewProjection, const std::list<sag::Light*>& lights, sag::RenderPassData* renderPassDataExchange) override;

	void setPosition(const glm::vec3& position);

private:
	std::weak_ptr<sag::SceneNode> sceneNode;


};

} // namespace sagame


#endif // SAGAME_CUBE_H
