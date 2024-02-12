#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>


class TextureManager
{

private:
	static TextureManager* sInstance;

	std::map<std::string, sf::Texture*> mTexture;

public:
	static TextureManager* Instance();
	static void Release();

	sf::Texture* GetTexture(std::string filename);

private:
	TextureManager();
	~TextureManager();
};

#endif
