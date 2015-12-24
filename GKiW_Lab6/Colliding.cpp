#include "stdafx.h"
#include "Colliding.h"


Colliding::Colliding(int num)
{
	numberOfWalls = num;
}
Colliding::Colliding()
{
	numberOfWalls = 1;
}

//slabo, bo zawsze w dziecku trzeba wywolac createCollision, a potem przypisac do poligonu

Colliding::~Colliding()
{
	delete collisionPolygon;
}

void Colliding::createCollision(vec3 collisionPoints[4])
{
	//assertion: collisionPoints.size() == numberOfWalls*4

	vec3 pointInTable[4];

	for (int i = 0; i < 4; i++)
	{

	}
	collisionPolygon = new CCollisionPolygon(collisionPoints, 4);
}
