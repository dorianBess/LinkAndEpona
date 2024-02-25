#include "Horse.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>

Horse::Horse()
{
	// Initialisez ici si nécessaire
	loadSprite();
	collisionBox = sprite.getGlobalBounds();
	hitBox = sprite.getGlobalBounds();
	dir = Facing::down;
	speed = 0;
}

void Horse::loadSprite()
{
	sprite.setTexture(*TextureManager::Instance()->GetTexture("Horse"));
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	collisionBox = sprite.getGlobalBounds();
}

void Horse::draw(sf::RenderWindow& window)
{
	collisionBox.left = sprite.getPosition().x;
	collisionBox.top = sprite.getPosition().y;

	window.draw(sprite);

	sf::FloatRect collisionBox = getCollisionBox();
	sf::RectangleShape collisionRect(sf::Vector2f(collisionBox.width, collisionBox.height));
	collisionRect.setPosition(collisionBox.left, collisionBox.top);
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setOutlineThickness(1.0f);
	collisionRect.setFillColor(sf::Color::Transparent);
	//window.draw(collisionRect);
}

void Horse::update(double deltaTime, Map& map)
{
	isMoving = false;
	if (isMount)
	{
		std::cout << speed << std::endl;
		sf::Vector2f position = sprite.getPosition();
		sprite.setRotation(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (speed < maxSpeed)
			{
				speed += 0.001f * deltaTime;
				if (speed > maxSpeed) speed = maxSpeed;
			}

		}
		else if (speed > 0)
		{

			speed -= 0.0005f * deltaTime;
			if (speed < 0)
			{
				speed = 0;
			}
			else
			{
				float x = 0;
				float y = 0;
				switch (dir)
				{
				case down:
					y = 1;
					break;
				case right:
					x = 1;
					break;
				case up:
					y = -1;
					break;
				case left:
					x = -1;
					break;
				case downLeft:
					y = -1;
					x = -1;
					break;
				case downRight:
					y = -1;
					x = -1;
					break;
				case upLeft:
					y = 1;
					x = -1;
					break;
				case upRight:
					y = 1;
					x = 1;
					break;
				default:
					break;
				}
				if (dir == upLeft || dir == upRight || dir == downLeft || dir == downRight)
				{
					if (canMoveTo(map, position + sf::Vector2f(x, y) *
						speed / 2.0f * static_cast<float>(deltaTime)))
					{
						sprite.setPosition(position + sf::Vector2f(x, y) * speed / 2.0f * (float)deltaTime);
						isMoving = true;
					}
				}
				else
				{
					if (canMoveTo(map, position + sf::Vector2f(x, y) *
						speed * static_cast<float>(deltaTime)))
					{
						sprite.setPosition(position + sf::Vector2f(x, y) * speed * (float)deltaTime);
						isMoving = true;
					}
				}
			}

		}
		std::cout << speed << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
			&& canMoveTo(map, position + sf::Vector2f(1, -1) *
				speed / 2.0f * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(1, -1) * speed / 2.0f * (float)deltaTime);
			isMoving = true;
			dir = Facing::up;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
			&& canMoveTo(map, position + sf::Vector2f(-1, -1) *
				speed / 2.0f * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(-1, -1) * speed / 2.0f * (float)deltaTime);
			isMoving = true;
			dir = Facing::up;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			&& canMoveTo(map, position + sf::Vector2f(1, 1) *
				speed / 2.0f * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(1, 1) * speed / 2.0f * (float)deltaTime);
			isMoving = true;
			dir = Facing::down;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			&& canMoveTo(map, position + sf::Vector2f(-1, 1) *
				speed / 2.0f * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(-1, 1) * speed / 2.0f * (float)deltaTime);
			isMoving = true;
			dir = Facing::down;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			&& canMoveTo(map, position + sf::Vector2f(1, 0) * speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(1, 0) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& canMoveTo(map, position + sf::Vector2f(-1, 0) * speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(-1, 0) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::left;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
			&& canMoveTo(map, position + sf::Vector2f(0, -1) *
				speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(0, -1) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			&& canMoveTo(map, position + sf::Vector2f(0, 1)
				* speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(0, 1) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::down;
		}
	}
	animate(deltaTime);
}

void Horse::animate(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= frameDuration) {
		elapsedTime = 0;
		if (isMoving)
		{
			frameNumber++;
			if (frameNumber >= numFrames) { frameNumber = 0; }
		}
		else
		{
			frameNumber = 0;
		}
		sprite.setTextureRect(sf::IntRect(frameNumber * spriteWidth, dir * spriteHeight, spriteWidth, spriteHeight));
		return;
	}
}

void Horse::setMount(bool valeur)
{
	isMount = valeur;
}
