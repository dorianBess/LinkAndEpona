#pragma once

#include "Item.h"
#include "TextureManager.h"

class Heart : public Item
{
public:
	Heart();
	void utiliserObjet(Entity& entite) override;
};

