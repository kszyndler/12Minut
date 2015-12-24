#include "stdafx.h"
#include "Item.h"
#include "ObjLoader.h"


Item::Item(float px, float py, float pz, float rx, float ry, float rz, string filename):Colliding(1)
{
	Position.Set(px, py, pz);
	Rotation.Set(rx, ry, rz);
	Name = filename;

	vec3 collisionPoints[4];
	collisionPoints[0].Set(px, py, pz);
	collisionPoints[1].Set(px, 2.0, pz);
	collisionPoints[2].Set(2.0, py, pz);
	collisionPoints[3].Set(2.0, 2.0, pz);//tu trzeba zmienic, zeby sie ladnie samo liczylo! 

	createCollision(collisionPoints);
	collisionPolygon->parent = this;

}


Item::~Item()
{
}

void Item::Initialize()
{
	id = LoadObj(Name);
}

void Item::Update()
{
}

void Item::Render()
{
	glPushMatrix();
		glTranslatef(Position.x, Position.y, Position.z);
		glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
		glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glScalef(0.2, 0.2, 0.2);
		glCallList(id);
	glPopMatrix();
}
