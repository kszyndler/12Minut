#pragma once
#include "Item.h"
#include "CollidingItem.h"

class Sofa :
	public CollidingItem
{
public:
	Sofa(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename) {};
};

