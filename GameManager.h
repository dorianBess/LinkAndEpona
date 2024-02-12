#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "UI.h"
#include "SFML/Audio.hpp"

class GameManager
{
public:
	static GameManager* sInstance;
	bool finishGame = false;
private:
	Player player;
	Map map;
	std::map<int,Entity*> entities;
	std::map<int,Item*> items;
	Horse horse;
	UI ui;
public:
	static GameManager* Instance();
	static void Release();

	void draw(sf::RenderWindow& window);
	void update(double deltaTime);

	void checkPlayerHitEntities();
	void checkPlayerCollisionEntities();
	void checkPlayerCollisionHorse();

	// Getters and setters
	Player& GetPlayer() { return player; }
	void SetPlayer(const Player& newPlayer) { player = newPlayer; }

	Map& GetMap() { return map; }
	void SetMap(const Map& newMap) { map = newMap; }

	std::map<int, Entity*>& GetEntities() { return entities; }
	void SetEntities(const std::map<int, Entity*>& newEntities) { entities = newEntities; }

	std::map<int, Item*>& GetItems() { return items; }
	void SetItems(const std::map<int, Item*>& newItems) { items = newItems; }

	Horse& GetHorse() { return horse; }
	void SetHorse(Horse newHorse) { horse = newHorse; }


private:
	GameManager();
	~GameManager();
};

#endif

