#pragma once
class Collectable
{
public:
	Collectable();
	~Collectable();
	virtual void collect(CScene*) {};
	char* Riddle;
	vector<vector<char*>>action; 
protected:
	int callsNumber;
};

