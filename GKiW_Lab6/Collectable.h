#pragma once
class Collectable
{
public:
	Collectable();
	~Collectable();
	virtual void collect(CScene*) {};
protected:
	int callsNumber;
};

