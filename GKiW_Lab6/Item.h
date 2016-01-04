#pragma once
#include <memory>
#include "Colliding.h"
#include "Modifier.h"

class CScene; 

class Item
	:public CSceneObject
{
public:
	Item(float px, float py, float pz, float rx, float ry, float rz, float scale, string name, CScene* scene);
	~Item();
	void Initialize();
	void Update();
	void Render();
	float scaleFactor;
	void registerModifier(shared_ptr<Modifier> modifier);
	
protected:
	int height; 
	vector<vec3> extremePeaks; 
	int id; 
	GLuint _displayListId;
	CTexture * _itemTexture;
	vector < shared_ptr< Modifier > > modifierRegister; 
	CScene* scene; 
};

