#include <iostream>
#include "TextureCache.h"
#include "ImageLoader.h"


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	auto mit = _textureMap.find(texturePath);

	if (mit == _textureMap.end()) {
		GLTexture NewTexture = ImageLoader::loadPNG(texturePath);
		_textureMap.insert(make_pair(texturePath, NewTexture));
		std::cout << "\nLoaded Texture !!!";
		return NewTexture;
	}
	std::cout << "\nLoaded Texture Cache !!!";
	return mit->second;
}
