#include "StdAfx.h"
#include <memory>
#include "Item.h"
#include "ItemsOnScene.h"
#include "SizeModifier.h"

int findInVector(Item* value, vector<CSceneObject*>* vector)
{
	for (int i = 0; i < vector->size(); i++)
	{
		if ((*vector)[i] == value)
			return i;
	}

	return -1;
}

void output(int x, int y, float r, float g, float b, char *string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
	}
}

void set2DMode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT/10, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Konstruktor.
CScene::CScene(void)
{
	DrawCollisions = false;
	DrawNormals = false;
	MarkCollision = false;
}

// Destruktor - sprz¹tamy po sobie.
CScene::~CScene(void)
{
	if (Skydome != NULL) {
		delete Skydome;
	}
	//if (Terrain != NULL) {
	//	delete Terrain;
	//}
	delete collectingManager;
}

// Inicjalizacja sceny.
void CScene::Initialize(void) {
	
	#pragma region Ustawienia

		// Ustawienie wszelkiego rodzaju rzeczy, które s¹ charakterystyczne dla tej konkretnej sceny.

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);


		Player.pos.x = 0.0f;
		Player.pos.y = 1.5f;
		Player.pos.z = -0.0f;

		Player.dir.x = 0.0f;
		Player.dir.y = 0.0f;
		Player.dir.z = -1.0f;

		Player.speed = .5f;

	#pragma endregion

	#pragma region Zawartosc sceny
	

		// ...oraz teren.
		//Terrain = new CTerrain();
		//Terrain->Initialize();

		Furniture* sofa = new Furniture(3.0f, 0.0f, 1.0f, 0, 0, 0, 0.09, "sofa", this);
		Furniture* coffeTable = new Furniture(3.0f, 0.0f, 0.0f, 0, 0, 0, 0.001, "coffeetable", this);
		Furniture* tv = new Furniture(3.0, 0.0, -3.0, 0, 0, 0, 0.4, "tv", this);
		AtWallItem* bookShelve = new AtWallItem(5.0, 0.8, -3.2, 0, 0, 0, 0.03, "bookshelve", this);
		Furniture* shelves = new Furniture(5.0, 0.0, -3.0, 0, 0, 0, 0.009, "shelves", this);
		AtWallItem* window = new AtWallItem(7.0, 0.5, -0.4, 0, 0, 0, 0.03, "window", this);
		AtWallItem* window2 = new AtWallItem(7.0, 0.5, -1.2, 0, 0, 0, 0.03, "window", this);
		Furniture* fotel = new Furniture(3.8f, 0.2f, 0.0f, 0, 0, 0, 0.025, "chair", this);
		Furniture* fotel2 = new Furniture(1.2f, 0.2f, -0.35f, 0, 0, 0, 0.025, "chair2obj", this);
		Furniture* lamp = new Furniture(3.3, 0.5, 0.0, 0, 0, 0, 0.003, "ikeaLamp", this);
		AtWallItem* lion = new AtWallItem(3.0f, 1.2f, 1.5f, 0, 0, 0, 0.009, "head", this);
		Furniture* regal = new Furniture(6.0, -0.01, 1.0, 0, 0, 0, 0.0011, "reg", this);
		Furniture* vase1 = new Furniture(6.0, 0.0, -2.1, 0, 0, 0, 0.015, "vase1", this);
		Furniture* vase2 = new Furniture(5.6, 0.0, -1.7, 0, 0, 0, 0.01, "vase1", this);
		AtWallItem* ceillamp = new AtWallItem(4.0, 2.0, -1.3, 0.0, 0, 0, 0.025, "ceilamp", this);
		AtWallItem* bible = new AtWallItem(6.1, 0.95, 1.0, 30, 0, 0, 0.1, "bible", this);
		AtWallItem* books = new AtWallItem(4.7, 0.71, -3.0, 0, 0, 0, 0.008, "books", this);

		// Dodanie wszystkich obiektów sceny do wektora, po którym póŸniej bêdziemy iterowaæ chc¹c je rysowaæ.
		// Dlatego w³aœnie wygodnie jest, gdy wszystkie obiekty sceny dziedzicz¹ po jednej, wspólnej klasie bazowej (CSceneObject).

		Objects = new vector<CSceneObject *>();
		sofa->Initialize();
		coffeTable->Initialize();
		bookShelve->Initialize();
		tv->Initialize();
		shelves->Initialize();
		window->Initialize();
		window2->Initialize();
		fotel->Initialize();
		fotel2->Initialize();
		lamp->Initialize();
		lion->Initialize();
		regal->Initialize();
		vase1->Initialize();
		vase2->Initialize();
		ceillamp->Initialize();
		bible->Initialize();
		books->Initialize();

		Objects->push_back(sofa);
		Objects->push_back(coffeTable);
		Objects->push_back(bookShelve);
		Objects->push_back(tv);
		Objects->push_back(shelves);
		Objects->push_back(window);
		Objects->push_back(window2);
		Objects->push_back(fotel);
		Objects->push_back(fotel2);
		Objects->push_back(lamp);
		Objects->push_back(lion);
		Objects->push_back(regal);
		Objects->push_back(vase1);
		Objects->push_back(vase2);
		Objects->push_back(ceillamp);
		Objects->push_back(bible);
		Objects->push_back(books);

		// Definicje po³o¿enia naszych œcian. Ka¿da kolejna czwórka wektorów to jeden quad.
		const float height = 2.9; 
		const float xa = -0.4;
		const float za = 1.55;
		const float zb = -3.4;
		const float xc = 7.3;

		vec3 walls[][4] = { 

			{ vec3( xa,  0.0f, za), vec3(xa,  height, za), vec3( xc,  height, za), vec3( xc,  0.0f, za) },
			{ vec3(xa,  0.0f, zb), vec3(xa,  height, zb), vec3(xa,  height, za), vec3(xa,  0.0f, za) },
			{ vec3(xc,  0.0f, zb), vec3(xc,  height, zb), vec3(xa,  height, zb), vec3(xa,  0.0f, zb) },
			{ vec3(xc,  0.0f, za), vec3(xc,  height, za), vec3(xc,  height, zb), vec3(xc,  0.0f, zb) },
			{ vec3(xa,  height, zb), vec3(xc,  height, zb),vec3(xc,  height, za), vec3(xa,  height, za) },
			
		};

		// Tyle mamy œcian.
		int NumberOfWalls = 5;

		// Zamieniamy powy¿sz¹ tablicê na obiekty typu CWall, które dodamy do listy obiektów na scenie.
		for (int i = 0; i < NumberOfWalls; ++i) {
			CWall *w = new CWall(walls[i][0], walls[i][1], walls[i][2], walls[i][3], "box.bmp");
			w->Name = "Wall" + to_string(i); // Nadanie nazwy, aby np. mo¿na by³o póŸniej ³atwo dowiedzieæ siê z czym mamy kolizjê.
			w->Initialize();
			Objects->push_back(w); // Dodanie do wektora rysowanych/przetwarzanych obiektów.
		}
		CWall *floor = new CWall(vec3(xa, 0.0, za), vec3(xc, 0.0, za), vec3(xc, 0.0, zb), vec3(xa, 0.0, zb), "Grass.bmp");
		floor->Initialize();
		Objects->push_back(floor);

	#pragma endregion


#pragma region Zbieranie przedmiotow
		queue <Item*>* ItemsToCollect = new queue<Item*>; 
		ItemsToCollect->push(bible);
		ItemsToCollect->push(vase2);

		collectingManager = new CollectingManager(ItemsToCollect);

#pragma endregion
	
}

// Aktualizacja œwiata gry.
void CScene::Update(void) {

	#pragma region Ruch kamery

		if (captureMouse) {
			Player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
			Player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		}

		if (keystate['w']) {
			Player.velM = Player.speed;
		}
		if (keystate['s']) {
			Player.velM = -Player.speed;
		}
		if (keystate['a']) {
			Player.velS = -Player.speed;
		}
		if (keystate['d']) {
			Player.velS = Player.speed;
		}
		if (keystate['q']) {
			Player.velRY = -Player.speed;
		}
		if (keystate['e']) {
			Player.velRY = Player.speed;
		}
		if (keystate['f']) {
			Player.velRX = -Player.speed;
		}
		if (keystate['c']) {
			Player.velRX = Player.speed;
		}


		float T = acos(Player.dir.y);
		float G = atan2(Player.dir.z, Player.dir.x);
		T -= Player.velRX * .03f;
		G += Player.velRY * .03f;
		Player.dir.x = sin(T) * cos(G);
		Player.dir.y = cos(T);
		Player.dir.z = sin(T) * sin(G);

		vec3 per;
		per.x = -Player.dir.z;
		per.y = 0;
		per.z = Player.dir.x;

		vec3 nextPlayerPos = Player.pos;

		nextPlayerPos.x += Player.dir.x * Player.velM * .1f;
		if (free3DMovement) {
			nextPlayerPos.y += Player.dir.y * Player.velM * .1f;
		}
		else {
			// Niby-grawitacja
			nextPlayerPos.y -= .1f;
		}
		nextPlayerPos.z += Player.dir.z * Player.velM * .1f;

		nextPlayerPos.x += per.x * Player.velS * .1f;
		if (free3DMovement) {
			nextPlayerPos.y += Player.dir.y * Player.velM * .1f;
		}
		nextPlayerPos.z += per.z * Player.velS * .1f;
		
		// Uniemo¿liwiamy zejœcie gracza poni¿ej poziomu terenu
		nextPlayerPos.y = __max(0.7f, nextPlayerPos.y);

		// Zmieniamy pozycjê gracza o wyliczony wczeœniej wektor przemieszczenia, uwzglêdniaj¹c przy tym kolizje ze œwiatem
		// "Objects" powinno byæ wektorem tylko tych obiektów, z którymi chcemy sprawdziæ kolizjê. Dobrze by³oby
		// wprowadziæ wczeœniejsz¹ fazê detekcji kolizji w oparciu np. o AABB i zawêziæ liczbê elementów Objects.
		Player.pos = CCollisionDetection::GetPositionAfterWorldCollisions(Player.pos, nextPlayerPos, Player, Objects);
		//objects to wszyskie obiekty, z ktorymi mozna kolidowac 
		Player.velRX /= 1.2;
		Player.velRY /= 1.2;
		Player.velM /= 1.2;
		Player.velS /= 1.2;

	#pragma endregion

	#pragma region Aktualizacja obiektow sceny

		// Ró¿ne obiekty mog¹ potrzebowaæ aktualizacji - np. poruszaj¹cy siê wrogowie.
		for (int i = 0; i < Objects->size(); ++i) {
			Objects->at(i)->Update();
		}

	#pragma endregion

}

// Narysowanie sceny.
void CScene::Render(void) {

	#pragma region Kamera

		gluLookAt(
			Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
			Player.pos.x + Player.cam.x + Player.dir.x, Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z,
			0.0f, 1.0f, 0.0f
		);

	#pragma endregion

	#pragma region Swiatlo
	
		float l0_amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		float l0_dif[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float l0_spe[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		float l0_pos[] = { 11.0f, 0.4, -0.6, 1.0 };//{ -1.0f, .2f, 0.5f, 0.0f };
		float l0_dir[] = { -1.0, -0.1, 0.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0_dir);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 70.0f);

		float l1_amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		float l1_dif[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l1_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float l1_pos[] = { 4.5, 2.0, -1.3, 1.0 };//na lampie
		glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);//zrodlo, skladowa, tablica
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_dif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spe);
		glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);

		//tlumienie swiatla z odlegloscia
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.2f);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2f);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2f);

		float l2_pos[] = { 2.6, l1_pos[1], -1.3, 1.0 };//na lampie
		glLightfv(GL_LIGHT2, GL_AMBIENT, l1_amb);//zrodlo, skladowa, tablica
		glLightfv(GL_LIGHT2, GL_DIFFUSE, l1_dif);
		glLightfv(GL_LIGHT2, GL_SPECULAR, l1_spe);
		glLightfv(GL_LIGHT2, GL_POSITION, l2_pos);

		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.2f);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2f);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2f);


	#pragma endregion

	#pragma region Skydome



	#pragma endregion

	//#pragma region Teren

	//	Terrain->Render();

	//#pragma endregion

	#pragma region Obiekty

		// Narysowanie wszystkich obiektów sceny (w tym przypadku - tylko œcian, ale do Objects mo¿na dodaæ te¿ wszystkie inne obiekty).
		for (int i = 0; i < Objects->size(); ++i) {
			Objects->at(i)->Render();
		}

		//swiatlo szescian
		glPushMatrix();
			glTranslatef(l1_pos[0], l1_pos[1], l1_pos[2]);
			glDisable(GL_LIGHTING);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(0.1);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(6.0, 0.8, 1.0);
		glDisable(GL_LIGHTING);
		glColor3f(0.0, 1.0, 0.0);
		//glutSolidCube(0.1);
		glEnable(GL_LIGHTING);
		glPopMatrix();

	#pragma endregion


	#pragma region Pomocnicze rysowanie kolizji
		// Narysowanie elipsoidy gracza oraz znalezionego punktu kolizji jeœli u¿ytkownik sobie tego ¿yczy (klawisz "K").
		if (DrawCollisions) {
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glLineWidth(1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glPushMatrix();
				glTranslatef(Player.pos.x, Player.pos.y, Player.pos.z);
				glScalef(Player.collisionEllipsoid->r.x, Player.collisionEllipsoid->r.y, Player.collisionEllipsoid->r.z);
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				glutWireSphere(1.0f, 64, 64);
			glPopMatrix();
			if (MarkCollision) {
				glColor3f(1.0f, 0.0f, 1.0f);
				glPointSize(16.0f);
				glDisable(GL_DEPTH_TEST);
				glBegin(GL_POINTS);
					glVertex3f(LastCollisionPoint.x, LastCollisionPoint.y, LastCollisionPoint.z);
				glEnd();
				glEnable(GL_DEPTH_TEST);
			}
			glEnable(GL_LIGHTING);
		}
	#pragma endregion


}


bool CScene::CallCollectingManager()
{
	Item* returnedItem = collectingManager->tryToCollect(Player);
	if (returnedItem != nullptr)
	{
		//deleteObject(returnedItem);
		shared_ptr<SizeModifier> dissapear(new SizeModifier(1.0, this, returnedItem));
		returnedItem->registerModifier(dissapear);
	}

	if (collectingManager->isDoneJob())
	{
		return true; //zakoncz gre
	}
	return false; 
}

void CScene::deleteObject(Item * obj)
{
	int objectId = findInVector(obj, Objects);
	Objects->erase(Objects->begin() + objectId);
	delete obj; 

}