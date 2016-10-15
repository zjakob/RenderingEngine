#ifndef _SAG_CUBE_H
#define _SAG_CUBE_H

#include <GL/glew.h>

#include <Render\Geometry\Geometry.h>
#include <Render\Material\Material.h>
#include <Render\Material\Shader\GlslShaderProgram.h>
#include <Render\Scene\RenderableObject.h>
#include <Render\Scene\SceneNode.h>

#include <memory>

class CubeEntity : public RenderableObject
{
public:
	CubeEntity();

	void render(const glm::mat4& viewProjectionMatrix);

	void setPosition(glm::vec3& position);

private:
	std::weak_ptr<SceneNode> sceneNode;


};

#endif // _SAG_CUBE_H
