#pragma once
#include "Vec3.h"

class Colliding
{
public:
	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawd� po prostu czworok�t), z kt�rym b�d� wykrywane kolizje.
	Colliding(int);
	Colliding();
	~Colliding();
	void createCollision(vec3 [4]);
	int numberOfWalls;
};