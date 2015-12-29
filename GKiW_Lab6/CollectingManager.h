#pragma once
#include <queue>
#include "Player.h"
#include "Item.h"

class CollectingManager
{
public:
	CollectingManager(queue <Item*>* Items);
	~CollectingManager();
	Item* tryToCollect(CPlayer& playerState);
	bool isDoneJob();
	Item* getHead();

private:
	queue <Item*>* ItemsToCollect;
	bool isCollectable(Item* item, CPlayer& playerState);
};

