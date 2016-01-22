#include "stdafx.h"
#include "SizeModifier.h"


SizeModifier::SizeModifier(float seconds, CScene* scene, Item* item):Modifier(seconds)
{
	this->scene = scene; 
	this->item = item; 

	distance = (scene->Player.pos - item->Position)/occurences;
}


SizeModifier::~SizeModifier(){}

int SizeModifier::update()
{
	item->scaleFactor *= 0.997;
	item->Position = item->Position + distance; 

	pastOccurences++;
	if (pastOccurences < occurences)
		return 0;
	return 1; 
}
