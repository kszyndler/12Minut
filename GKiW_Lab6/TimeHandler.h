#pragma once
#include "Modifier.h"

class TimeHandler :
	public Modifier
{
public:
	TimeHandler(float seconds,  vector<char*> strings);
	~TimeHandler();
	int update();
private:
	vector<char*> toDisplay;
	Interface userInterface;
};

