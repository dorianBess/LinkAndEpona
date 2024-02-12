#ifndef _MONSTER_H
#define _MONSTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

class Monster : public Entity
{
public:
    Monster();  // Constructeur par défaut

    void loadSprite() override;
    void draw(sf::RenderWindow& window) override;
    void update(double deltaTime,Map& map) override;
    void animate(float deltaTime) override;
    void addMovePosition(sf::Vector2f newPos);
    void setMobile(bool value);
private:
    int frameNumber = 0;
    int spriteWidth = 16;
    int spriteHeight = 22;
    int numFrames = 4;

    float elapsedTime;
    float frameDuration = 60;

    float moveTimer = 0.0f;
    float moveInterval = 1000.0f;
    int indexMove = 0;
    std::vector<sf::Vector2f>movePosition;
    bool needToMove = true;
    bool mobile = false;
};

#endif
