#include "AudioManager.h"
#include <iostream>

AudioManager* AudioManager::sInstance = NULL;

AudioManager* AudioManager::Instance()
{
    if (sInstance == NULL) {
        sInstance = new AudioManager();
    }
    return sInstance;
}

void AudioManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

AudioManager::~AudioManager()
{
    for (auto sound : mSound)
    {
        delete sound.second;
        sound.second = NULL;
    }
    for (auto buffer : mSoundBuffer)
    {
        delete buffer.second;
        buffer.second = NULL;
    }
    mSound.clear();
    mSoundBuffer.clear();
}

AudioManager::AudioManager()
{
    music.openFromFile("Assets/Music.mp3");
    music.setVolume(0.25f);
    music.play();

    mSound["Sword"] = new sf::Sound();
    mSoundBuffer["Sword"] = new sf::SoundBuffer();
    mSoundBuffer["Sword"]->loadFromFile("Assets/Sword.wav");
    mSound["Sword"]->setBuffer(*mSoundBuffer["Sword"]);
    mSound["Sword"]->setVolume(0.5f);

    mSound["Damage"] = new sf::Sound();
    mSoundBuffer["Damage"] = new sf::SoundBuffer();
    mSoundBuffer["Damage"]->loadFromFile("Assets/Damage.wav");
    mSound["Damage"]->setBuffer(*mSoundBuffer["Damage"]);
    mSound["Damage"]->setVolume(0.5f);

    mSound["Heal"] = new sf::Sound();
    mSoundBuffer["Heal"] = new sf::SoundBuffer();
    mSoundBuffer["Heal"]->loadFromFile("Assets/Heal.wav");
    mSound["Heal"]->setBuffer(*mSoundBuffer["Heal"]);
    mSound["Heal"]->setVolume(0.5f);


}

sf::Sound* AudioManager::GetSound(std::string name)
{
    return mSound[name];
}