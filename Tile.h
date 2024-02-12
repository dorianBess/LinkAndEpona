#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile();
    ~Tile();

    void setWalkable(bool walkable); // D�finir si la case est marchable ou non
    void draw(sf::RenderWindow& window);

    sf::Sprite& getSprite();    // Obtenir la r�f�rence du sprite

    bool isTileWalkable();      // V�rifier si la case est marchable

    sf::FloatRect getCollisionBox();

    

private:
    
    sf::Sprite sprite;

    bool walkable;
};

#endif // TILE_H
