#include "Monster.h"
#include "TextureManager.h"
#include <iostream>

Monster::Monster()
{
	// Initialisez ici si nécessaire
	loadSprite();
	collisionBox = sprite.getGlobalBounds();
	hitBox = sprite.getGlobalBounds();
	hurtBox = sf::FloatRect(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, sprite.getGlobalBounds().width - 4, sprite.getGlobalBounds().height - 4);
	sprite.setColor(sf::Color(255, 255, 0, 255));
	speed = 0.05f;
	health = 20;
	currentHealth = 20;
}

void Monster::loadSprite()
{
	sprite.setTexture(*TextureManager::Instance()->GetTexture("Player"));
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 22));
}

void Monster::draw(sf::RenderWindow& window)
{
	if (!isAlive()) return;
	window.draw(sprite);

	sf::FloatRect collisionBox = getCollisionBox();
	sf::RectangleShape collisionRect(sf::Vector2f(collisionBox.width, collisionBox.height));
	collisionRect.setPosition(collisionBox.left, collisionBox.top);
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setOutlineThickness(1.0f);
	collisionRect.setFillColor(sf::Color::Transparent);
	//window.draw(collisionRect);

	sf::FloatRect collisionBox2 = hurtBox;
	sf::RectangleShape collisionRect2(sf::Vector2f(collisionBox2.width, collisionBox2.height));
	collisionRect2.setPosition(collisionBox2.left, collisionBox2.top);
	collisionRect2.setOutlineColor(sf::Color::White);
	collisionRect2.setOutlineThickness(1.0f);
	collisionRect2.setFillColor(sf::Color::Transparent);
	//window.draw(collisionRect2);
}

void Monster::update(double deltaTime,Map& map)
{
	if (!isAlive())
	{
		collisionBox = sf::FloatRect();
		hitBox = sf::FloatRect();
		hurtBox = sf::FloatRect();
		return;
	}
	if (invulnerability)
	{
		timer += deltaTime;
		if (sprite.getColor().a == 255) {
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 0)); // Transparent
		}
		else {
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 255)); // Visible
		}

		if (timer > invulTime)
		{
			timer = 0;
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 255)); // Visible
			invulnerability = false;
		}
	}

	if (needToMove && mobile)
	{
		if (movePosition.size() >= indexMove)
		{
			// Calculer la différence entre la position actuelle et la position cible
			sf::Vector2f diff = movePosition[indexMove] - sprite.getPosition();
			if (std::abs(diff.x) > std::abs(diff.y))
			{
				// Déplacement horizontal
				if (diff.x > 0)
				{
					dir = Facing::right;
				}
				else
				{
					dir = Facing::left;
				}
			}
			else
			{
				// Déplacement vertical
				if (diff.y > 0)
				{
					dir = Facing::down;
				}
				else
				{
					dir = Facing::up;
				}
			}

			// Vérifier si le monstre est suffisamment proche de la position cible
			if (std::abs(diff.x) < 1.0f && std::abs(diff.y) < 1.0f)
			{
				needToMove = false;
				if (indexMove >= movePosition.size() - 1)
				{
					indexMove = 0;
				}
				else
				{
					indexMove++;
				}
			}
			else
			{
				sf::Vector2f direction = diff / std::sqrt(diff.x * diff.x + diff.y * diff.y);
				sprite.move(direction * speed * (float)deltaTime);
			}

		}
	}
	else
	{
		moveTimer += deltaTime;
		if (moveTimer >= moveInterval)
		{
			moveTimer = 0;
			needToMove = true;
		}
	}
	collisionBox.left = sprite.getPosition().x;
	collisionBox.top = sprite.getPosition().y;

	hurtBox.left = sprite.getPosition().x +2;
	hurtBox.top = sprite.getPosition().y + 2;
	animate(deltaTime);
}

void Monster::animate(float deltaTime)
{
	if (isMoving)
	{
		frameNumber++;
		if (frameNumber >= numFrames) { frameNumber = 0; }
	}
	else {
		frameNumber = 0;
	}
	sprite.setTextureRect(sf::IntRect(frameNumber * spriteWidth, dir * spriteHeight + 10 * dir, spriteWidth, spriteHeight));//finds appropriate "frame" in tileset, assigns to sprite
	return;
}

void Monster::addMovePosition(sf::Vector2f newPos)
{
	movePosition.push_back(newPos);
}

void Monster::setMobile(bool value)
{
	mobile = value;
}
