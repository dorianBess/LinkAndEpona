#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::sInstance = NULL;

TextureManager* TextureManager::Instance()
{
    if (sInstance == NULL) {
        sInstance = new TextureManager();
    }
    return sInstance;
}

void TextureManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

TextureManager::~TextureManager()
{
    for (auto text : mTexture)
    {
        delete text.second;
        text.second = NULL;
    }
    mTexture.clear();
}

TextureManager::TextureManager()
{

    mTexture["Player"] = new sf::Texture();
    mTexture["Player"]->loadFromFile("Assets/character.png");

    mTexture["Horse"] = new sf::Texture();
    mTexture["Horse"]->loadFromFile("Assets/horse.png");

    mTexture["Heart"] = new sf::Texture();
    mTexture["Heart"]->loadFromFile("Assets/objects.png", sf::IntRect(64, 1, 14, 14));

    mTexture["Sword"] = new sf::Texture();
    mTexture["Sword"]->loadFromFile("Assets/character.png", sf::IntRect(0, 120, 16, 16));

    mTexture["Lifebar"] = new sf::Texture();
    mTexture["Lifebar"]->loadFromFile("Assets/lifebar.png");

}

sf::Texture* TextureManager::GetTexture(std::string name)
{
    if (mTexture[name] == nullptr)
    {
        mTexture[name] = new sf::Texture();
        int i = stoi(name) -1;
        mTexture[name]->loadFromFile("Assets/OverworldAll.png", sf::IntRect((i % 40) * 16, (i / 40)* 16, 16, 16));
        
    }
    return mTexture[name];
}