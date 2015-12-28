#pragma once
#include "Vec3.h"

struct Shape
{
	vec3 peaks[4]; //xmin, zmin, xmax ,zmax lub dla 1 sciany wierzcholki
	int numberOfWalls;
	float height; 
};

class Colliding
{
public:
	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawdê po prostu czworok¹t), z którym bêd¹ wykrywane kolizje.
	vector <CCollisionPolygon*> collisionPolygons;

	Colliding(int);
	~Colliding();

	void createCollisions(CSceneObject* parent);
	void checkCollisions(vec3 pos0, vec3 pos1, CCollisionEllipsoid * e, SCollision &result);
	void chooseCollisionShape(vector<vec3> newPeaks, float newHeight);
	void Render();
	

protected:
	Shape collisionShape; 
	void createWall(vec3 peakA, vec3 peakB, vec3 wall[4]);
	void createCollision(vec3 peaks[4], CSceneObject* parent);
	void collide(vector <vec3> peaks, float height, CSceneObject* parent);
};

