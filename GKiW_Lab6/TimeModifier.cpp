#include "stdafx.h"
#include "TimeModifier.h"


TimeModifier::TimeModifier():Modifier(0)
{
}


TimeModifier::~TimeModifier()
{
}

int TimeModifier::update()
{
	pastOccurences++;
	if (pastOccurences < occurences)
		return 0;
	return 3;
}

void TimeModifier::reset(float seconds)
{
	int number = seconds * 1000 / step;
	occurences = number;
	pastOccurences = 0;
}
