#pragma once
#include "Item.h"
#include "CollidingItem.h"

class Sofa :
	public CollidingItem
{
public:
	Sofa(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene) {};
};

class Boy :
	public Item
{
public:
	Boy(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene) {};
};

class Puff :
	public CollidingItem
{
public:
	Puff(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene) {};
};