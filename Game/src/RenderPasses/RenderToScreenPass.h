#ifndef SAGAME_RENDER_TO_SCREEN_PASS_H
#define SAGAME_RENDER_TO_SCREEN_PASS_H

#include <Scene\SceneManager.h>
#include <Render\Renderer\RenderPass\RenderPass.h>
#include <Render\Renderer\RenderPass\RenderPassData.h>

namespace sagame
{

class RenderToScreenPass : public sag::RenderPass
{
public:
	RenderToScreenPass(unsigned int renderWindowWidth, unsigned int renderWindowHeight);

	void render(const sag::SceneManager& scene, sag::RenderPassData* renderPassDataExchange) const override;

private:
	unsigned int renderWindowWidth;
	unsigned int renderWindowHeight;

};

} // namespace sag


#endif // SAGAME_RENDER_TO_SCREEN_PASS_H
