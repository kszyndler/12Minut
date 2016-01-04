#include "stdafx.h"
#include "CollectingManager.h"
#include <math.h>

CollectingManager::CollectingManager(queue <Item*>* Items)
{
	ItemsToCollect = Items; 
}

CollectingManager::~CollectingManager()
{
	delete ItemsToCollect;
}

Item* CollectingManager::tryToCollect(CPlayer & playerState)
{
	printf("W Collectorze\n");

	if (ItemsToCollect->empty())
		return nullptr; 

	Item* head = ItemsToCollect->front();

	if (isCollectable(head, playerState))
	{
		ItemsToCollect->pop();

		return head; 
	}

	return nullptr; 
}

bool CollectingManager::isCollectable(Item* item, CPlayer& playerState)
{
	float a = item->Position.x; 
	float b = item->Position.y;
	float c = item->Position.z;

	float x1 = playerState.pos.x;
	float y1 = playerState.pos.y;
	float z1 = playerState.pos.z;

	float l = playerState.dir.x - x1; 
	float m = playerState.dir.y - y1; 
	float n = playerState.dir.z - z1; 

	float d2 = (pow(((a - x1)*m - (b - y1)*l), 2) + pow(((b - y1)*n - (c - z1)*m), 2) +
		pow(((c - z1)*l - (a - x1)*n), 2)) / (l*l + m*m + n*n);
	float d = sqrt(d2);

	vec3 distanceVector = playerState.pos - item->Position;
	float distance = sqrt(distanceVector.x*distanceVector.x + distanceVector.y*distanceVector.y + distanceVector.z * distanceVector.z);

	vec3 pointLookingAt = playerState.pos + (playerState.dir/50);
	vec3 distanceLookingAtItemVector = pointLookingAt - item->Position;
	float distanceLookingAtItem = sqrt(distanceLookingAtItemVector.x*distanceLookingAtItemVector.x + distanceLookingAtItemVector.y*distanceLookingAtItemVector.y + distanceLookingAtItemVector.z * distanceLookingAtItemVector.z);

	if (distance < 1.2 && d<1.3 && distanceLookingAtItem <= distance)
		return true;
	return false; 
}

bool CollectingManager::isDoneJob()
{
	if (ItemsToCollect->empty())
	{
		return true;
	}
	return false;
}

Item * CollectingManager::getHead()
{
	if (ItemsToCollect->empty())
		return nullptr;
	return ItemsToCollect->front();
}
