#pragma once
#include "Modifier.h"

class RotationModifier :
	public Modifier
{
public:
	RotationModifier(float seconds, Item* item, float anglex, float angley, float anglez);
	~RotationModifier();
	int update();

private:
	Item* item; 
	float rx; 
	float ry; 
	float rz; 
};

