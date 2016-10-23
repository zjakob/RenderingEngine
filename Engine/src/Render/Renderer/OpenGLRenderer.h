#ifndef SAG_OPENGL_RENDERER_H
#define SAG_OPENGL_RENDERER_H

#include <list>

#include <GL/glew.h>

#include "../Camera/Camera.h"
#include "../Light.h"
#include "../Scene/SceneNode.h"
#include "RenderWindow.h"


namespace sag
{

class OpenGLRenderer
{
public:
	OpenGLRenderer(RenderWindow& renderWindow);
	~OpenGLRenderer();

	void init();
	void render(const Camera& camera, const std::list<Light*>& lights, const std::list<RenderableObject*>& renderableObjects);

private:
	RenderWindow& renderWindow;

};

} // namespace sag


#endif // SAG_OPENGL_RENDERER_H
