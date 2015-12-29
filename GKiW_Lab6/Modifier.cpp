#include "stdafx.h"
#include "Modifier.h"


Modifier::Modifier(float seconds)
{
	int number = seconds * 1000 / step;
	occurences = number; 
	pastOccurences = 0; 
}

Modifier::~Modifier()
{
}
