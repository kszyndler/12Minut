#include "stdafx.h"
#include "Item.h"
#include "ObjLoader.h"


Item::Item(float px, float py, float pz, float rx, float ry, float rz, string filename):Colliding(px, py, pz)
{
	Position.Set(px, py, pz);
	Rotation.Set(rx, ry, rz);
	Name = filename; 

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
