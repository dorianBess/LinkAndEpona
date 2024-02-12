#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile();
    ~Tile();

    void setWalkable(bool walkable); // Définir si la case est marchable ou non
    void draw(sf::RenderWindow& window);

    sf::Sprite& getSprite();    // Obtenir la référence du sprite

    bool isTileWalkable();      // Vérifier si la case est marchable

    sf::FloatRect getCollisionBox();

    

private:
    
    sf::Sprite sprite;

    bool walkable;
};

#endif // TILE_H
