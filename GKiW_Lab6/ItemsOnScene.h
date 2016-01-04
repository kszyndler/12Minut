#pragma once
#include "Item.h"
#include "CollidingItem.h"
#include "Collectable.h"

class Bible :
	public Item ,public Collectable
{
public:
	Bible(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		Item(px, py, pz, rx, ry, rz, scale, filename, scene), Collectable() 
	{
		Riddle = "Znajdz Biblie";
	};
};

class Vase :
	public CollidingItem
{
public:
	Vase(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene)
	{
		Riddle = "Mniejsze rozmiary skrywaja wieksze sekrety";
	};
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
};

class Boxu :
	public CollidingItem
{
public:
	Boxu(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene)
	{
		Riddle = "Na zdjeciu dostrzegasz maly, kolorowy kuferek";
	};
};
class Boxd :
	public CollidingItem
{
public:
	Boxd(float px, float py, float pz, float rx, float ry, float rz, float scale, string filename, CScene* scene) :
		CollidingItem(px, py, pz, rx, ry, rz, scale, filename, scene)
	{
		Riddle = "Otworz kuferek";
	};
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
};