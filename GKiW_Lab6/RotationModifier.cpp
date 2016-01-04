#include "stdafx.h"
#include "RotationModifier.h"


RotationModifier::RotationModifier(float seconds, vec3 playerPos):Modifier(seconds)
{

}


RotationModifier::~RotationModifier()
{
}

int RotationModifier::update()
{
	item->rotationFactor *= 0.995;
	pastOccurences++;
	if (pastOccurences < occurences)
		return 0;
	return 2;
}