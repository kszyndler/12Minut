#pragma once
#include "Modifier.h"
class SizeModifier :
	public Modifier
{
public:
	SizeModifier(int, CScene*, Item*);
	~SizeModifier();
	int update();

private:
	CScene* scene; 
	Item* item; 
};

