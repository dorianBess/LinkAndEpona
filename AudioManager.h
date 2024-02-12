#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include <map>
#include <string>
#include <SFML/Audio.hpp>


class AudioManager
{

private:
	static AudioManager* sInstance;

	std::map<std::string, sf::Sound*> mSound;
	std::map<std::string, sf::SoundBuffer*> mSoundBuffer;
	sf::Music music;

public:
	static AudioManager* Instance();
	static void Release();

	sf::Sound* GetSound(std::string filename);

private:
	AudioManager();
	~AudioManager();
};

#endif

