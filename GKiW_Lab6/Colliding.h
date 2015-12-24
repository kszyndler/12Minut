#pragma once
#include "Vec3.h"

class Colliding
{
public:
	vec3 collisionPoints[4];	//lub wiecej scian 
	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawd� po prostu czworok�t), z kt�rym b�d� wykrywane kolizje.
	Colliding(float, float, float);
	~Colliding();
};

