#include "stdafx.h"
#include "CollidingItem.h"


CollidingItem::CollidingItem(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename):
	Item(px, py, pz, rx, ry, rz, scale, filename), Colliding(4) {}

void CollidingItem::Initialize()
{
	Item::Initialize();
	collide(extremePeaks, extremePeaks[5].y, this);
}




