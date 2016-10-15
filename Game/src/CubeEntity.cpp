
#include "CubeEntity.h"

#include <Render\Scene\SceneManager.h>


CubeEntity::CubeEntity() :
	RenderableObject(Material(GlslShaderProgram(".\\src\\ShaderSource\\movingtri.vs", ".\\src\\ShaderSource\\movingtri.fs")))
{
	std::vector<GLfloat> vertexPos{
		-0.25f, -0.25f, -0.25f,
		-0.25f, 0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,
		0.25f, 0.25f, -0.25f,
		0.25f, -0.25f, 0.25f,
		0.25f, 0.25f, 0.25f,
		-0.25f, -0.25f, 0.25f,
		-0.25f, 0.25f, 0.25f
	};
	std::vector<GLushort> vertexIdx{
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		6, 0, 2,
		2, 4, 6,
		7, 5, 3,
		7, 3, 1
	};

	this->geometry.setVertices(std::move(vertexPos), std::move(vertexIdx));

	sceneNode = SceneManager::getInstance().getRootSceneNode().lock()->createChildSceneNode();
	if (auto lockedSceneNode = sceneNode.lock())
	{
		lockedSceneNode->attachObject(*this);
	}
}

void CubeEntity::render(const glm::mat4& viewProjectionMatrix)
{
	glm::mat4 mvpMat = viewProjectionMatrix * modelMatrix;
	material.apply(mvpMat);
	geometry.draw();
}

void CubeEntity::setPosition(glm::vec3& position)
{
	if (auto lockedSceneNode = sceneNode.lock())
	{
		auto localMat = lockedSceneNode->getLocalTransformation();
		auto modelMat = glm::translate(localMat, position);
		lockedSceneNode->setLocalTransformation(modelMat);
	}
}