#include "Heart.h"

Heart::Heart()
{
	sprite = sf::Sprite();
	sprite.setTexture(*TextureManager::Instance()->GetTexture("Heart"));
	collisionBox = sprite.getGlobalBounds();
}

void Heart::utiliserObjet(Entity& entite)
{
	entite.changeCurrentHP(valeur);
}
