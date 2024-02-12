#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "GameManager.h"
#include "AudioManager.h"

int main()
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	float zoomFactor = 2.0f;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "RPG Game", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	TextureManager* textMgr = TextureManager::Instance();

	GameManager* game = GameManager::Instance();

	AudioManager* audio = AudioManager::Instance();

	sf::Clock clock;

	while (window.isOpen() && !game->finishGame)
	{
		sf::Time deltaTimeTimer = clock.restart();
		double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		game->update(deltaTime);

		sf::Vector2f playerPosition = game->GetPlayer().getSprite().getPosition();
		sf::View playerView(sf::FloatRect(playerPosition.x - SCREEN_WIDTH/2 / zoomFactor, playerPosition.y - SCREEN_HEIGHT/2 / zoomFactor, SCREEN_WIDTH /zoomFactor, SCREEN_HEIGHT /zoomFactor));
		window.setView(playerView);

		//window.clear(sf::Color(30,124,184));
		window.clear(sf::Color::Black);
		game->draw(window);
		window.display();
	}

	GameManager::Release();
	TextureManager::Release();
	AudioManager::Release();

	return 0;
}