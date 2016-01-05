#include "stdafx.h"
#include "TimeHandler.h"


TimeHandler::TimeHandler(float seconds, vector<char*> str):Modifier(seconds)
{
	toDisplay = str; 
}


TimeHandler::~TimeHandler()
{
}

int TimeHandler::update()
{

	for (int i = 0; i < toDisplay.size(); i++)
	{
		userInterface.draw(20, 40+i*5, GLUT_BITMAP_HELVETICA_18, toDisplay[i]);
	}
	
	pastOccurences++;
	if (pastOccurences < occurences)
		return 0;
	return 1;
}

