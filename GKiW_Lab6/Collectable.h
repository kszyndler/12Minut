#pragma once
class Collectable
{
public:
	Collectable();
	~Collectable();
	virtual void collect(CScene*) {};
	char* Riddle;
	char* action; 
protected:
	int callsNumber;
};

