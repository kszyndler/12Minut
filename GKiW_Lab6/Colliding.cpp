#include "stdafx.h"
#include "Colliding.h"


Colliding::Colliding(float px, float py, float pz)
{
	collisionPoints[0].Set(px, py, pz);
	collisionPoints[1].Set(px, 4.0, pz);
	collisionPoints[2].Set(4.0, py, pz);
	collisionPoints[3].Set(4.0, 4.0, pz);
	//stworzyc po prostu 4 sciany od razu 
	collisionPolygon = new CCollisionPolygon (collisionPoints, 4); // Stworzenie polygonu, kt�ry b�dzie wykorzystywany do wykrywania kolizji.
	//to juz w konkretnej klasie collisionPolygon->parent = this; // Niech polygon pami�ta, do kogo przynale�y.
}

Colliding::~Colliding()
{
	delete collisionPolygon;
}