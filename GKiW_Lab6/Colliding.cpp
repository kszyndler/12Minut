#include "stdafx.h"
#include "Colliding.h"


Colliding::Colliding(int num)
{
	collisionShape.numberOfWalls = num;
}


Colliding::~Colliding()
{
	for (int i = 0; i < collisionPolygons.size(); i++)
	{
		delete collisionPolygons[i];
	}
	collisionPolygons.clear();
}

void Colliding::createCollision(vec3 collisionPoints[4], CSceneObject* polygonParent)
{
	CCollisionPolygon* polygon = new CCollisionPolygon(collisionPoints, 4);
	polygon->parent = polygonParent;
	collisionPolygons.push_back(polygon);
}

void Colliding::createCollisions(CSceneObject * parent)
{
	vec3 wallPeaks[4];
	if (collisionShape.numberOfWalls == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			wallPeaks[i] = collisionShape.peaks[i];
		}
		createCollision(wallPeaks, parent);
	}

	else if (collisionShape.numberOfWalls == 4)
	{
		vec3 wall[4]; 
		for (int i = 0; i < 4; i++)
		{
			createWall(collisionShape.peaks[i], collisionShape.peaks[(i + 1)%4], wall);
			createCollision(wall, parent);
		}
	}
}

void Colliding::checkCollisions(vec3 pos0, vec3 pos1, CCollisionEllipsoid * e, SCollision & result)
{
	for (int i = 0; i < collisionShape.numberOfWalls; i++)
	{
		collisionPolygons[i]->CheckCollision(pos0, pos1, e, result);
	}
}

void Colliding::chooseCollisionShape(vector<vec3> newPeaks, float newHeight)
{
	collisionShape.peaks = newPeaks; 
	collisionShape.height = newHeight; 
}

void Colliding::createWall(vec3 peakA, vec3 peakB, vec3 wall[4])
{
	float xA = peakA.x;
	float xB = peakB.x; 
	float zA = peakA.z;
	float zB = peakB.z; 
	float ymin = 0.0; 
	float ymax = collisionShape.height;

	wall[0].Set(xA, ymin, zA);
	wall[1].Set(xA, ymax, zA);
	wall[2].Set(xB, ymax, zB);
	wall[3].Set(xB, ymin, zB);
}

void Colliding::Render()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	for (size_t i = 0; i < collisionPolygons.size(); i++)
	{
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex3f(collisionPolygons[i]->v[0].x,
					collisionPolygons[i]->v[0].y, collisionPolygons[i]->v[0].z);
				glVertex3f(collisionPolygons[i]->v[1].x,
					collisionPolygons[i]->v[1].y, collisionPolygons[i]->v[1].z);
				glVertex3f(collisionPolygons[i]->v[2].x,
					collisionPolygons[i]->v[2].y, collisionPolygons[i]->v[2].z);
				glVertex3f(collisionPolygons[i]->v[3].x,
					collisionPolygons[i]->v[3].y, collisionPolygons[i]->v[3].z);
			glEnd();
		glPopMatrix();
	}
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
}
