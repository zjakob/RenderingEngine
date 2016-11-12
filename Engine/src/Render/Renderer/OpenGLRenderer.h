#ifndef SAG_OPENGL_RENDERER_H
#define SAG_OPENGL_RENDERER_H

#include <list>

#include "RenderWindow.h"
#include "./RenderPass/RenderPass.h"
#include "../Scene/SceneManager.h"


namespace sag
{

class OpenGLRenderer
{
public:
	OpenGLRenderer(RenderWindow& renderWindow);

	void render(SceneManager& scene);
	void addRenderPass(RenderPass* pass);

private:
	RenderWindow& renderWindow;
	std::list<RenderPass*> renderPasses;

};

} // namespace sag


#endif // SAG_OPENGL_RENDERER_H
