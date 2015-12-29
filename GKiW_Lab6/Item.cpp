#include "stdafx.h"
#include "Item.h"
#include "ObjLoader.h"
#include <tuple>

using namespace std; 

void swapVectors(vec3 a, vec3 b)
{
	vec3 tmp = a; 
	a = b;
	b = tmp; 
}

Item::Item(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene)
{
	Position.Set(px, py, pz);
	Rotation.Set(rx, ry, rz);
	Scale = scale; 
	Name = filename;
	scaleFactor = 1; 
	this->scene = scene; 
}


Item::~Item()
{

}

void Item::Initialize()
{
	try
	{
		tuple< int, vector<vec3> > idExtremePeaks = LoadObj(Name); 
		id = get < 0 > (idExtremePeaks);
		extremePeaks = get < 1 >(idExtremePeaks);
	}
	catch (const std::exception&)
	{
		return; 
	}
	
	for (int i = 0; i < extremePeaks.size(); i++)
	{	
		extremePeaks[i].x *= Scale;	
		extremePeaks[i].x += Position.x;

		extremePeaks[i].y *= Scale;
		extremePeaks[i].y += Position.y;

		extremePeaks[i].z *= Scale;
		extremePeaks[i].z += Position.z;
	}
}

void Item::Update()
{
	bool killYourself = false; 

	vector <shared_ptr<Modifier> >::iterator it = modifierRegister.begin();
	while (it != modifierRegister.end())
	{
		int nextAction = (*it)->update();
		if (nextAction == 1)
		{
			//delete modifierRegister[i];
			it = modifierRegister.erase(it);
			killYourself = true; 
		}
		else
			++it;
	}

	if(killYourself)
		scene->deleteObject(this);

}

void Item::Render()
{
	Scale *= scaleFactor; 

	glPushMatrix();
		glTranslatef(Position.x, Position.y, Position.z);
		glScalef(Scale, Scale, Scale);
		glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
		glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glCallList(id);
	glPopMatrix();

	//Colliding::Render();
}

void Item::registerModifier(shared_ptr<Modifier> modifier)
{
	modifierRegister.push_back(modifier);
}
