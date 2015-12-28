#pragma once
#include "Colliding.h"

class Item
	:public CSceneObject
{
public:
	Item(float px, float py, float pz, float rx, float ry, float rz, float scale, string name);
	~Item();
	void Initialize();
	void Update();
	void Render();

protected:
	int height; 
	vector<vec3> extremePeaks; 
	int id; 
	GLuint _displayListId;
	CTexture * _itemTexture;

};

