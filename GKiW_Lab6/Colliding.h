#pragma once
#include "Vec3.h"

class Colliding
{
public:
	vec3 collisionPoints[4];	//lub wiecej scian 
	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawdê po prostu czworok¹t), z którym bêd¹ wykrywane kolizje.
	Colliding(float, float, float);
	~Colliding();
};

