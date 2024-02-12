#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include "Horse.h"


class GameManager;
class Item;

class Player : public Entity {
public:
    Player();  // Constructeur par défaut
    void loadSprite() override;  // Charger la texture du joueur
    void draw(sf::RenderWindow& window) override;  // Afficher le joueur
    void update(double deltaTime,Map& map) override;
    void animate(float deltaTime) override;

    void checkInput(double deltaTime, Map& gameMap);
    bool setHorse(Horse* aHorse);

    bool canDoAction = true;

private:
    int frameNumber = 0;
    int spriteWidth = 16;
    int spriteHeight = 22;
    int numFrames = 4;
    int attNumFrames = 3;

    float elapsedTime;
    float frameDuration = 60;

    sf::Sprite swordSprite;  
    sf::Texture swordTexture;

    Horse* horse;
    bool onMount = false;

    
    float actionElapsedTime;
    float actionDuration = 600;
};

#endif // PLAYER_H
