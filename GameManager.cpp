#include "GameManager.h"
#include "Monster.h"
#include "Heart.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance()
{
    if (!sInstance)
    {
        sInstance = new GameManager();
    }
    return sInstance;
}

void GameManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

void GameManager::draw(sf::RenderWindow& window)
{
    map.draw(window);
    for(auto entity : entities)
    {
        entity.second->draw(window);
    }
    for (auto item : items)
    {
        item.second->draw(window);
    }
    horse.draw(window);
    player.draw(window);
    ui.draw(window);
}

void GameManager::update(double deltaTime)
{
    if (!player.isAlive())
    {
        finishGame = true;
    }
    for (auto entity : entities)
    {
        entity.second->update(deltaTime, map);       
    }
    for (auto item : items)
    {
        item.second->update(deltaTime,player);
    }
    horse.update(deltaTime,map);
    player.update(deltaTime,map);
    ui.update(deltaTime, player);
    checkPlayerCollisionEntities();
    checkPlayerCollisionHorse();
    checkPlayerHitEntities();
}

void GameManager::checkPlayerHitEntities()
{
    for (auto ennemy : entities)
    {
        if (player.getHitBox().intersects(ennemy.second->getCollisionBox()))
        {
            ennemy.second->changeCurrentHP(-5);
        }
    }
}

void GameManager::checkPlayerCollisionEntities()
{
    for (auto ennemy : entities)
    {
        if (ennemy.second->getCollisionBox().intersects(GameManager::Instance()->GetPlayer().getCollisionBox()))
        {
            player.changeCurrentHP(-5);
        }
    }
    
}

void GameManager::checkPlayerCollisionHorse()
{
    if (player.canDoAction && horse.getCollisionBox().intersects(player.getCollisionBox()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (player.setHorse(&horse))
        {
            player.canDoAction = false;
            horse.setMount(true);
        };
    }
}

GameManager::GameManager()
{
    map = Map();

    player = Player();
    player.setPosition(80, 16);

    Item* item = new Heart();
    item->setPosition(280, 192);
    items.emplace(0, item);

    Monster* ennemy = new Monster();
    ennemy->setPosition(224, 64);
    ennemy->addMovePosition(ennemy->getSprite().getPosition());
    ennemy->addMovePosition(sf::Vector2f(224, 16));
    ennemy->addMovePosition(sf::Vector2f(224, 64));
    ennemy->setMobile(true);

    Monster* anotherEnnemy = new Monster();
    anotherEnnemy->setPosition(112, 240);
    anotherEnnemy->addMovePosition(anotherEnnemy->getSprite().getPosition());
    anotherEnnemy->addMovePosition(sf::Vector2f(192, 240));
    anotherEnnemy->addMovePosition(sf::Vector2f(192, 368));
    anotherEnnemy->addMovePosition(sf::Vector2f(112, 368));
    anotherEnnemy->setMobile(true);

    entities[0] = ennemy;
    entities[1] = anotherEnnemy;

    horse = Horse();
    horse.setPosition(160, 200);
}

GameManager::~GameManager()
{
    for (auto entity : entities)
    {
        delete entity.second;
        entity.second = NULL;
    }
    entities.clear();
    for (auto item : items)
    {
        delete item.second;
        item.second = NULL;
    }
    items.clear();
}

