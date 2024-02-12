#pragma once
#include "Entity.h"

class Horse : public Entity
{
public:
    Horse();  // Constructeur par défaut
    void loadSprite() override;  // Charger la texture du joueur
    void draw(sf::RenderWindow& window) override;  // Afficher le joueur
    void update(double deltaTime,Map& map) override;
    void animate(float deltaTime) override;

    void setMount(bool valeur);

private:
    int frameNumber = 0;
    int spriteWidth = 16;
    int spriteHeight = 16;
    int numFrames = 2;
    float elapsedTime;
    float frameDuration = 60;

    bool isMount = false;

};

