#pragma once
#include "Item.h"
class CollidingItem :
	public Item, public Colliding
{
public:
	CollidingItem(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene);
	~CollidingItem();
	void Initialize();
};

