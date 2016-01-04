#include "stdafx.h"
#include "RotationModifier.h"


RotationModifier::RotationModifier(float seconds, Item* item, float anglex, float angley, float anglez):Modifier(seconds)
{
	this->item = item;
	rx = anglex / occurences;
	ry = angley / occurences;
	rz = anglez / occurences;
}


RotationModifier::~RotationModifier()
{
}

int RotationModifier::update()
{
	item->Rotation.x += rx;
	item->Rotation.y += ry;
	item->Rotation.z += rz;

	pastOccurences++;
	if (pastOccurences < occurences)
		return 0;
	return 2;
}