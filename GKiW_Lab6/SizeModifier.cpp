#include "stdafx.h"
#include "SizeModifier.h"


SizeModifier::SizeModifier(int seconds, CScene* scene, Item* item):Modifier(seconds)
{
	this->scene = scene; 
	this->item = item; 
}


SizeModifier::~SizeModifier(){}

int SizeModifier::update()
{
	item->scaleFactor *= 0.995; 
	pastOccurences++;
	if (pastOccurences < occurences)
		return 0;
	return 1; 
}
