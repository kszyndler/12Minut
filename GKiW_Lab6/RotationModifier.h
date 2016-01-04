#pragma once
#include "Modifier.h"

class RotationModifier :
	public Modifier
{
public:
	RotationModifier(float seconds, vec3 playerPos);
	~RotationModifier();
	int update();

private:
	Item* item; 
	vec3 playerPos;
};

