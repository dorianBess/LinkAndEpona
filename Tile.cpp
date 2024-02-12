#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

Tile::Tile() : walkable(true)
{
}

Tile::~Tile()
{
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}

sf::Sprite& Tile::getSprite() {
    return sprite;
}

bool Tile::isTileWalkable() {
    return walkable;
}

void Tile::draw(sf::RenderWindow& window) {

    window.draw(sprite);
    sf::FloatRect collisionBox = sprite.getGlobalBounds();
    sf::RectangleShape collisionRect(sf::Vector2f(collisionBox.width, collisionBox.height));
    collisionRect.setPosition(collisionBox.left, collisionBox.top);
    collisionRect.setOutlineColor(sf::Color::Red);
    collisionRect.setOutlineThickness(1.0f);
    collisionRect.setFillColor(sf::Color::Transparent);
    //window.draw(collisionRect);        
}

sf::FloatRect Tile::getCollisionBox() { return sprite.getGlobalBounds(); }
