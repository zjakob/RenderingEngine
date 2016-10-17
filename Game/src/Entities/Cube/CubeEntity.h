#ifndef SAGAME_CUBE_H
#define SAGAME_CUBE_H

#include <GL/glew.h>

#include <Render\Scene\RenderableObject.h>
#include <Render\Scene\SceneNode.h>

#include <memory>


namespace sagame
{

class CubeEntity : public sag::RenderableObject
{
public:
	CubeEntity();

	void render(const glm::mat4& view, const glm::mat4& viewProjectionMatrix);

	void setPosition(glm::vec3& position);

private:
	std::weak_ptr<sag::SceneNode> sceneNode;


};

} // namespace sagame


#endif // SAGAME_CUBE_H
