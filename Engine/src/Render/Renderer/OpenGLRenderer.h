#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <list>

#include <GL/glew.h>

#include "../Camera/Camera.h"
#include "../Scene/SceneNode.h"
#include "RenderWindow.h"

class OpenGLRenderer
{
public:
	OpenGLRenderer(RenderWindow& renderWindow);
	~OpenGLRenderer();

	void init();
	void render(const std::list<RenderableObject*>& renderableSceneNodes, const Camera& camera);

private:
	RenderWindow& renderWindow;

};

#endif // OPENGL_RENDERER_H
