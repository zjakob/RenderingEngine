#ifndef SAGAME_FLOOR_H
#define SAGAME_FLOOR_H

#include <GL/glew.h>

#include <Render\Scene\RenderableObject.h>
#include <Render\Scene\SceneNode.h>
#include <Render\Light.h>

#include <memory>


namespace sagame
{

class FloorEntity : public sag::RenderableObject
{
public:
	FloorEntity();

	void render(const glm::mat4& view, const glm::mat4& projection, const std::list<sag::Light*>& lights) override;

	void setPosition(glm::vec3& position);
	void scale(glm::vec3& scale);

private:
	std::weak_ptr<sag::SceneNode> sceneNode;


};

} // namespace sagame


#endif // SAGAME_FLOOR_H
