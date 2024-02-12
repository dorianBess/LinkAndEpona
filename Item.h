#ifndef ITEM_H
#define ITEM_H

#include "Player.h"


class Item {
public:
    Item();
    virtual ~Item();

    virtual void utiliserObjet(Entity& entite);

    // Getter pour le nom de l'objet
    std::string getNom() const;

    // Getter pour la valeur de l'objet
    int getValue() const;

    // Getter pour le sprite de l'objet
    const sf::Sprite& getSprite() const;

    sf::FloatRect& getCollisionBox();

    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    void update(double deltaTime,Player& player);

protected:
    std::string nom;
    int valeur = 10;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::FloatRect collisionBox;
    bool alreadyUse = false;
};

#endif