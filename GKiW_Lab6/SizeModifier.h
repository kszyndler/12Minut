#pragma once
#include "Modifier.h"
class SizeModifier :
	public Modifier
{
public:
	SizeModifier(float, CScene*, Item*);
	~SizeModifier();
	int update();


private:
	CScene* scene; 
	Item* item; 
};

