#pragma once
#include <queue>
#include "Player.h"
#include "Item.h"
#include "Collectable.h"

class CollectingManager
{
public:
	CollectingManager(queue <Collectable*>* Items);
	~CollectingManager();
	Collectable* tryToCollect(CPlayer& playerState);
	bool isDoneJob();
	Collectable* getHead();

private:
	queue <Collectable*>* ItemsToCollect;
	bool isCollectable(Item* item, CPlayer& playerState);
};

