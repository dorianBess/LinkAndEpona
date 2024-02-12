#include "Player.h"
#include <iostream>
#include "TextureManager.h"
#include "AudioManager.h"


Player::Player()
{
	// Initialisez ici si nécessaire
	loadSprite();
	collisionBox = sprite.getGlobalBounds();
	hitBox = sf::FloatRect(0, 0, 0, 0);
}

void Player::loadSprite()
{
	sprite = sf::Sprite();
	sprite.setTexture(*TextureManager::Instance()->GetTexture("Player"));
	sprite.setTextureRect(sf::IntRect(1, 5, 15, 22));
	sprite.setPosition(sf::Vector2f(40, 40));

	swordSprite.setTexture(*TextureManager::Instance()->GetTexture("Sword"));
	swordSprite.setOrigin(0, 6.5);

}

void Player::draw(sf::RenderWindow& window) {
	if (onMount) return;
	window.draw(swordSprite);
	window.draw(sprite);
	
	sf::FloatRect collisionBox = getCollisionBox();
	sf::RectangleShape collisionRect(sf::Vector2f(collisionBox.width, collisionBox.height));
	collisionRect.setPosition(collisionBox.left, collisionBox.top);
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setOutlineThickness(1.0f);
	collisionRect.setFillColor(sf::Color::Transparent);
	//window.draw(collisionRect);

	sf::FloatRect attQBox = hitBox;
	sf::RectangleShape attRect(sf::Vector2f(attQBox.width, attQBox.height));
	attRect.setPosition(attQBox.left, attQBox.top);
	attRect.setOutlineColor(sf::Color::Blue);
	attRect.setOutlineThickness(1.0f);
	attRect.setFillColor(sf::Color::Transparent);
	//window.draw(attRect);
}

void Player::update(double deltaTime,Map& map)
{
	if (!canDoAction)
	{
		actionElapsedTime += deltaTime;
		if(actionElapsedTime >= actionDuration) 
		{
			actionElapsedTime = 0;
			canDoAction = true;
		}
	}
	if (onMount)
	{
		sprite.setPosition(horse->getSprite().getPosition());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && canDoAction)
		{
			horse->setMount(false);
			setHorse(nullptr);
		}
		return;
	}		
	checkInput(deltaTime, map);
	if(isAttacking) hitBox = swordSprite.getGlobalBounds();
	// Mettre à jour la position de la boîte de collision par rapport au sprite du joueur
	collisionBox.left = sprite.getPosition().x;
	collisionBox.top = sprite.getPosition().y;
	
	animate(deltaTime);
}

void Player::animate(float deltaTime) {

	elapsedTime += deltaTime;
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
	if (elapsedTime >= frameDuration) {
		elapsedTime = 0;
		if (isAttacking)
		{
			swordSprite.setColor(sf::Color(swordSprite.getColor().r, swordSprite.getColor().g, swordSprite.getColor().b, 255));
			frameNumber++;
			if (frameNumber > attNumFrames) { frameNumber = 0; isAttacking = false;}
			swordSprite.rotate(-90 / attNumFrames);
			return;
		}
		else
		{
			swordSprite.setColor(sf::Color(swordSprite.getColor().r, swordSprite.getColor().g, swordSprite.getColor().b, 0));
		}
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
}


void Player::checkInput(double deltaTime, Map& gameMap)
{
	sf::Vector2f position = sprite.getPosition();
	isMoving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isAttacking && canDoAction)
	{
		AudioManager::Instance()->GetSound("Sword")->play();
		isAttacking = true;
		canDoAction = false;
		switch (dir)
		{
		case 0:
			hitBox = sf::FloatRect(collisionBox.getPosition().x,
				collisionBox.getPosition().y + collisionBox.height,
				collisionBox.width, 3);
			swordSprite.setPosition(collisionBox.getPosition().x + collisionBox.width/2, collisionBox.getPosition().y + collisionBox.width);
			swordSprite.setRotation(180);
			break;
		case 1:
			hitBox = sf::FloatRect(collisionBox.getPosition().x + collisionBox.width,
				collisionBox.getPosition().y,
				3, collisionBox.height);
			swordSprite.setPosition(collisionBox.getPosition().x + collisionBox.width / 2, collisionBox.getPosition().y + collisionBox.height / 2);
			swordSprite.setRotation(90);
			break;
		case 2:
			hitBox = sf::FloatRect(collisionBox.getPosition().x,
				collisionBox.getPosition().y - 3,
				collisionBox.width, 3);
			swordSprite.setPosition(collisionBox.getPosition().x + collisionBox.width / 2, collisionBox.getPosition().y + collisionBox.width - 8);
			swordSprite.setRotation(0);
			break;
		case 3:
			hitBox = sf::FloatRect(collisionBox.getPosition().x - 3,
				collisionBox.getPosition().y,
				3, collisionBox.height);
			swordSprite.setPosition(collisionBox.getPosition().x + collisionBox.width / 2, collisionBox.getPosition().y + collisionBox.height/2);
			swordSprite.setRotation(-90);
			break;
		}
		hitBox = swordSprite.getGlobalBounds();
	}
	else
	{
		hitBox = sf::FloatRect(collisionBox.getPosition().x, collisionBox.getPosition().y + collisionBox.height, 0, 0);
	}

	if (!isAttacking)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			&& canMoveTo(gameMap, position + sf::Vector2f(1, 0) * speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(1, 0) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& canMoveTo(gameMap, position + sf::Vector2f(-1, 0) * speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(-1, 0) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::left;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
			&& canMoveTo(gameMap, position + sf::Vector2f(0, -1) *
				speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(0, -1) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			&& canMoveTo(gameMap, position + sf::Vector2f(0, 1)
				* speed * static_cast<float>(deltaTime))
			&& !isMoving)
		{
			sprite.setPosition(position + sf::Vector2f(0, 1) * speed * (float)deltaTime);
			isMoving = true;
			dir = Facing::down;
		}
	}
}

bool Player::setHorse(Horse* aHorse)
{
	if (!canDoAction)
	{
		return false;
	}
	onMount = aHorse == nullptr ? false : true;
	horse = aHorse;
	canDoAction = false;
	return true;
}
