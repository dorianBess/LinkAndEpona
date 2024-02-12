#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class UI
{
public:
	UI();
	void draw(sf::RenderWindow& window);
	void update(double deltaTime,Player& player);
private:
	sf::RectangleShape lifeBar;
	sf::Sprite lifeBarSprite;
	float lifeBarX = 162;
	float lifeBarY = 15;
};

