#include "Item.h"
#include "TextureManager.h"


Item::Item()
{
	sprite = sf::Sprite();
	sprite.setTexture(*TextureManager::Instance()->GetTexture("Heart"));
	collisionBox = sprite.getGlobalBounds();
}

Item::~Item()
{
	
}

void Item::utiliserObjet(Entity& entite)
{
	entite.changeCurrentHP(valeur);
}

std::string Item::getNom() const
{
	return nom;
}

int Item::getValue() const
{
	return valeur;
}

const sf::Sprite& Item::getSprite() const
{
	return sprite;
}

sf::FloatRect& Item::getCollisionBox()
{
	return collisionBox;
}

void Item::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	collisionBox = sprite.getGlobalBounds();
}

void Item::draw(sf::RenderWindow& window)
{
	if (alreadyUse) return;
	window.draw(sprite);

	sf::FloatRect collisionBox = getCollisionBox();
	sf::RectangleShape collisionRect(sf::Vector2f(collisionBox.width, collisionBox.height));
	collisionRect.setPosition(collisionBox.left, collisionBox.top);
	collisionRect.setOutlineColor(sf::Color::Green);
	collisionRect.setOutlineThickness(1.0f);
	collisionRect.setFillColor(sf::Color::Transparent);
	//window.draw(collisionRect);
}

void Item::update(double deltaTime, Player& player)
{
	if (collisionBox.intersects(player.getCollisionBox()))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			utiliserObjet(player);
			sprite.setTexture(sf::Texture::Texture());
			collisionBox = sf::FloatRect();
			alreadyUse = true;
		}		
	}
}
