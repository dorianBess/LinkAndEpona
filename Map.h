#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <list>

class Map {
public:
    static const int mapWidth = 30;
    static const int mapHeight = 30;
    static const int tileSize = 16;
    Tile mapTiles[mapHeight][mapWidth];  // Structure de la carte
public:
    Map();  // Constructeur par défaut

    void generateMap();  // Générer la carte
    void draw(sf::RenderWindow& window);  // Afficher la carte    
};

#endif // MAP_H
