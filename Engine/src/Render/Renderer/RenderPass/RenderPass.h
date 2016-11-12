#ifndef SAG_RENDER_PASS_H
#define SAG_RENDER_PASS_H

#include "RenderPassData.h"
#include "../../Scene/SceneManager.h"

namespace sag
{

class RenderPass
{
public:
	virtual void render(const SceneManager& scene, RenderPassData* renderPassDataExchange) const = 0;

};

} // namespace sag


#endif // SAG_RENDER_PASS_H
