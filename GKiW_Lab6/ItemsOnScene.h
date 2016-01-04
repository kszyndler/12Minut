#pragma once
#include "Item.h"
#include "CollidingItem.h"
#include "Collectable.h"
#include "SizeModifier.h"
#include "RotationModifier.h"

using namespace std; 

class Bible :
	public Item ,public Collectable
{
public:
	Bible(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable() 
	{
		Riddle = "Znajdz Biblie";
	};
	void collect(CScene* scene)
	{
		if (callsNumber == 1)
		{
			shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
			registerModifier(dissapear);
		}
		else if (callsNumber == 0)
		{
			Riddle = "Przeczytaj tekst";
		}
		callsNumber++;
	}

private:

};

class Vase :
	public CollidingItem, public Collectable
{
public:
	Vase(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene)
	{
		Riddle = "Mniejsze rozmiary skrywaja wieksze sekrety";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class Doors :
	public Item
{
public:
	Doors(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene) {};

};

class Frame :
	public Item, public Collectable
{
public:
	Frame(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Czytasz wiadomosc od numeru: 'W paryzu bylo cudownie'";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class Key :
	public Item, public Collectable
{
public:
	Key(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Kuferek jest zamkniety";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class MagGlass :
	public Item, public Collectable
{
public:
	MagGlass(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Druk jest drobny, nie mozesz przeczytac";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class ScrewDriver :
	public Item, public Collectable
{
public:
	ScrewDriver(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Odkrec sruby";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class Dolar :
	public Item, public Collectable
{
public:
	Dolar(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Czytasz: 'Nie mozecie sluzyæ Bogu i Mamonie'";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class Phone :
	public Item, public Collectable
{
public:
	Phone(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Na odwrocie banknotu znajdujesz numer teledonu: 540 240 328";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};

class Box :
	public CollidingItem, public Collectable
{
public:
	Box(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene)
	{
		Riddle = "Zauwazasz, ze postaci na zdjeciu nosza takie same, srebrne obraczki";
	};
	void collect(CScene* scene)
	{
		if (callsNumber == 0)
		{
			Riddle = "Otworz kuferek";
		}
		else if (callsNumber == 1)
		{
			shared_ptr<RotationModifier> open(new RotationModifier(1.0, this, 0, 0, 30));
			registerModifier(open);
		}
		callsNumber++;
	}

};

class Rings :
	public Item, public Collectable
{
public:
	Rings(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable()
	{
		Riddle = "Podnies obraczki";
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};