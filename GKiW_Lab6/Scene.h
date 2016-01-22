#pragma once
#include "CollectingManager.h"
#include "Interface.h"
#include "TimeHandler.h"

int findInVector(Item* value, vector<CSceneObject*>* vector);


class CScene
{
public:
	CPlayer Player; // Stan gracza.
	CollectingManager* collectingManager;

	vector<CSceneObject *> * Objects;

	CScene(void); 
	~CScene(void); 
	void Initialize(void); 
	void Update(void); 
	void Render(void); 
	void deleteObject(Item* object);

	bool CallCollectingManager();
	
	void renderGoodEnding();
	void start();

private:
	Collectable* toFind;
	Interface userInterface;
	queue <shared_ptr<TimeHandler> > actionWindow;
	void pushTextToDisplay(vector<char*> text, float time);
	bool ended; 
	bool started; 
};

