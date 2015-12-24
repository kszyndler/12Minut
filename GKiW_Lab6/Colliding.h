#pragma once
#include "Vec3.h"

class Colliding
{
public:
	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawdê po prostu czworok¹t), z którym bêd¹ wykrywane kolizje.
	Colliding(int);
	Colliding();
	~Colliding();
	void createCollision(vec3 [4]);
	int numberOfWalls;
};