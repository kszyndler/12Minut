#include "stdafx.h"
#include "CollidingItem.h"


CollidingItem::CollidingItem(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene):
	Item(px, py, pz, rx, ry, rz, scale, filename, scene), Colliding(4) {}

CollidingItem::~CollidingItem()
{}

void CollidingItem::Initialize()
{
	Item::Initialize();
	collide(extremePeaks, extremePeaks[5].y, this);
}




