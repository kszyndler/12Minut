#pragma once
class Item; 

class Modifier
{
public:
	Modifier(float seconds);
	~Modifier();
	virtual int update()=0;
protected:
	const int step = 17; 
	int occurences; 
	int pastOccurences;
};