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
		Riddle = "Joanna stala sie ostatnio bardzo religijna";
		action = { 
			{ "Ksiega wyglada na bardzo czesto uzywana. ",
			"Kiedy otwierasz ja na zaznaczonej stronie,",
			"widzisz wielokrotnie podkreslony tekst. "},
			{"Niestety druk jest zbyt drobny, nie mozesz nic przeczytac. " } 
		};
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
			action = { 
				{ "Czytasz: 'Nie mozecie sluzyc Bogu i mamonie'.",
			"Nie rozumiesz, czemu akurat ten ",
			"fragment tak bardzo ja zainteresowal." } 
			};
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
		action = {
			{ "Podnosisz pojemnik i zauwazasz, ze na spodzie",
			"znajduje sie wieczoko, przykrecone kilkoma srubkami. "},
			{"Wyglada na to ze Asia ukryla cos w srodku." } 
		};
	};
	void collect(CScene* scene)
	{
		if (callsNumber == 0)
		{
			Riddle = "Odkrec sruby";
			action = {
				{ "W srodku znajdujesz artykul z gazety, data wydania przypada na lata 60.",
				"Tekst mowi o spotkaniach czlonkow sekty Boga Slonca. "},
				{"'Grupa fanatykow zbierala sie w domu nr 13 przy ulicy 17 Stycznia, ",
				"by odprawiac krwawe rytualy. Ofiary przygotowyli przez 24 godziny. " },
				{"Wierzyli, ze ich poswiecenie przyniesie zbawienie ludzkosci'"}, 
				//{"Nie mozesz uwierzyc, ze Joanna wplata sie w dzialalnosc sekty"},
				//{"Natychmiast informujesz policje o miejscu, w ktorym",
				//"prawdopodobnie znajduje sie twoja przyjaciolka."},
				//{"W domu przebywala nie tylko Joanna ale tez cztery inne osoby, "
				//"ktore mialy stac sie ofiarami w zaplanowanym na kolejna noc rytuale. "}, 
				//{"Uratowano je dzieki rozwiazaniu zagadki. "}
			};
		}
		else if (callsNumber == 1)
		{
			shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
			registerModifier(dissapear);
		}
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
		action = {
			{ "Na zdjeciu dostrzegasz dwie postaci'",
		"w jednej z nich rozpoznajesz Asie, obok niej stoi mezczyzna,  ",
		"ktorego widzisz po raz pierwszy."},
		{"Oboje maja na palcach srebrne obraczki. Na odwrocie zapisano date: '17.01.13', ",
		"jednak masz pewnosc, ze zdjecia nie zrobiono zima."},
		{"Wyglada to na zdjecie nowozencow, ale wiesz,",
		"ze Asia nigdy nie wyszla za maz" }
		};
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
		action = { {"Wyglada na to, ze pasuje do klodki kuferka"} };
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
		action = { { "Mozesz teraz wrocic po Biblie"} };
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
		Riddle = "Do dna przykrecone sa sruby";
		action = { { "Sprobuj odkrecic sruby"} };
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
		Riddle = "'Nie mozecie sluzyæ Bogu i Mamonie'";
		action = { {"Na banknocie zauwazasz dziwne symbole. ",
			"Na odwrocie zapisany jest ciag cyfr: 580400202" } };
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
		Riddle = "Na odwrocie banknotu zapisano ciag cyfr: 580400202";
		action = { {"To numer telefonu. Sprawdzasz historie polaczen Joanny. ",
			"Zauwazasz, ze czesto dzwoni na ten numer. "},
			{"Tydzien temu dostala wiadomosc: 'W Paryzu bylo cudownie, dziekuje!'"}
		};
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
		action = { { "Kuferek jest zamkniety"} };
	};
	void collect(CScene* scene)
	{
		if (callsNumber == 0)
		{
			Riddle = "Otworz kuferek";
			action = { { " " } };
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
		action = { { "Obraczki sa identyczne. Wewnetrzne czesci sa wygrawerowane.",
			"Przygladasz sie blizej. ",
			"'Mniejsze rozmiary skrywaja wieksze sekrety'" }};
	};
	void collect(CScene* scene)
	{
		shared_ptr<SizeModifier> dissapear(new SizeModifier(0.6, scene, this));
		registerModifier(dissapear);
		callsNumber++;
	}
};