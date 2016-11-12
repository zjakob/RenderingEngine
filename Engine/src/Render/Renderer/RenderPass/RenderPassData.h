#ifndef SAG_RENDER_PASS_DATA_H
#define SAG_RENDER_PASS_DATA_H

#include <string>
#include <unordered_map>
#include <utility>

#include <GL/glew.h>

#include <cassert>

namespace sag
{

class RenderPassData
{
public:
	RenderPassData()
	{
	}

	GLuint getTexture(std::string textureName)
	{
		auto t = textures.find(textureName);
		if (t != textures.end())
			return textures.at(textureName);
		else
			assert("No texture with that name was found.");
	}

	void addTexture(std::string textureName, GLuint textureId)
	{
		textures.insert(std::make_pair(textureName, textureId));
	}

private:
	std::unordered_map<std::string, GLuint> textures;
};

} // namespace sag


#endif // SAG_RENDER_PASS_DATA_H
