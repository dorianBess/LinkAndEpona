#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Map.h"

enum Facing {

    down = 0,//row zero on sprite sheet
    right = 1,//row three on sprite sheet
    up = 2,//row two on sprite sheet
    left = 3,//row one on sprite sheet
    //these are used for 8 directional animation!
    downLeft = 4,
    downRight = 5,
    upLeft = 6,
    upRight = 7,
};

class Entity {
public:
    Entity();

    int getHealth() const;
    int getCurrentHealth() const;
    int getDamage() const;
    const sf::Sprite& getSprite() const;
    sf::FloatRect getCollisionBox() const;
    sf::FloatRect getHitBox() const;
    sf::FloatRect getHurtBox() const;

    void setPosition(float x, float y);
    void setSprite(sf::Sprite aSprite);    
    bool isAlive();    
    void move(float deltaX, float deltaY);    
    bool canMoveTo(Map& gameMap, sf::Vector2f newPosition) const;
    void changeCurrentHP(int amount);
    bool canTakeDamage();

    virtual void animate(float deltaTime) = 0;    
    virtual void update(double deltaTime,Map& map) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void loadSprite() = 0;

protected:
    int health = 100;
    int currentHealth = 100;
    int damage = 5;
    float speed = 0.1f;
    sf::Sprite sprite;
    sf::FloatRect collisionBox;
    sf::FloatRect hitBox;
    sf::FloatRect hurtBox;
    Facing dir;

    bool isMoving = false;
    bool isAttacking = false;
    bool invulnerability = false;
    double timer = 0;
    float invulTime = 600; 
};

#endif // ENTITY_H
