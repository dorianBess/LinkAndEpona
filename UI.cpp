#include "UI.h"
#include <iostream>
#include "TextureManager.h"

UI::UI()
{
	lifeBar.setSize(sf::Vector2f(lifeBarX, lifeBarY));
	lifeBar.setFillColor(sf::Color::Green);
	lifeBarSprite.setTexture(*TextureManager::Instance()->GetTexture("Lifebar"));
	lifeBarSprite.setScale(3,3);
}

void UI::draw(sf::RenderWindow& window)
{
	
	lifeBar.setPosition(window.getView().getCenter().x - window.getView().getSize().x/2 + 10 * 3 + 7, window.getView().getCenter().y - window.getView().getSize().y / 2 + 10 * 3 - 2);
	window.draw(lifeBar);
	lifeBarSprite.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2 + 10, window.getView().getCenter().y - window.getView().getSize().y / 2 + 10);
	window.draw(lifeBarSprite);
}

void UI::update(double deltaTime,Player& player)
{	
	float ratio = static_cast<float>(player.getCurrentHealth()) / player.getHealth();
	lifeBar.setSize(sf::Vector2f(lifeBarX * ratio, lifeBarY));
	lifeBar.setFillColor(sf::Color(255 - 255 * ratio, 255 * ratio, 0));
}
