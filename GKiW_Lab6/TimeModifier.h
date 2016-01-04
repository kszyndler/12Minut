#pragma once
#include "Modifier.h"
class TimeModifier :
	public Modifier
{
public:
	TimeModifier();
	~TimeModifier();
	int update();
	void reset(float seconds);
};

