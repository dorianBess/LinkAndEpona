#include "Entity.h"
#include <iostream>
#include "AudioManager.h"

Entity::Entity() : dir(Facing::down)
{
}

sf::FloatRect Entity::getCollisionBox() const
{
    return collisionBox;
}

sf::FloatRect Entity::getHitBox() const
{
    return hitBox;
}

sf::FloatRect Entity::getHurtBox() const
{
    return hurtBox;
}

int Entity::getHealth() const {
    return health;
}

int Entity::getCurrentHealth() const {
    return currentHealth;
}

int Entity::getDamage() const {
    return damage;
}

const sf::Sprite& Entity::getSprite() const {
    return sprite;
}

void Entity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Entity::setSprite(sf::Sprite aSprite)
{
    sprite = aSprite;
}

void Entity::changeCurrentHP(int amount) {
    if (!canTakeDamage() && amount < 0) return;
    currentHealth += amount;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
    if (currentHealth > health)
    {
        currentHealth = health;
    }
    if (amount < 0)
    {
        invulnerability = true;
        AudioManager::Instance()->GetSound("Damage")->play();
    }
    else
    {
        AudioManager::Instance()->GetSound("Heal")->play();
    }
    std::cout << "Take " << amount << " damage" << std::endl;
}


bool Entity::isAlive()
{
    return currentHealth != 0;
}

bool Entity::canTakeDamage()
{
    return !invulnerability;
}

void Entity::move(float deltaX, float deltaY) {
    sprite.move(deltaX, deltaY);
}

bool Entity::canMoveTo(Map& gameMap, sf::Vector2f newPosition) const {
    // Obtenez la boîte de collision du joueur à la nouvelle position
    sf::FloatRect newPlayerBox = getCollisionBox();
    newPlayerBox.left = newPosition.x;
    newPlayerBox.top = newPosition.y;

    // Vérifiez les collisions avec chaque tuile de la carte
    for (int i = 0; i < gameMap.mapHeight; ++i) {
        for (int j = 0; j < gameMap.mapWidth; ++j) {
            if (!gameMap.mapTiles[i][j].isTileWalkable()) {
                // Si la tuile n'est pas walkable, vérifiez la collision
                sf::FloatRect tileBox(j * gameMap.tileSize * 1.0f, i * gameMap.tileSize * 1.0f, gameMap.tileSize * 1.0f, gameMap.tileSize * 1.0f);
                if (newPlayerBox.intersects(tileBox)) {
                    return false; // Collision détectée
                }
            }
        }
    }

    // Si aucune collision n'est détectée, le joueur peut se déplacer
    return true;
}
