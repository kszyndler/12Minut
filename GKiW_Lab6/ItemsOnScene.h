#pragma once
#include "Item.h"
#include "CollidingItem.h"

class Furniture :
	public CollidingItem
{
public:
	Furniture(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene) {};
};

class AtWallItem :
	public Item
{
public:
	AtWallItem(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene) {};
};

class Puff :
	public CollidingItem
{
public:
	Puff(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene) {};
};