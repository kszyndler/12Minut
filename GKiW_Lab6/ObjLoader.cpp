#include "stdafx.h"
#include "ObjLoader.h"
#include "Texture.h"
#include <vector>
#include <map>

using namespace std;

struct light {
	float r;
	float g; 
	float b;
};

struct Material {
	string name;
	string texturePath;
	light ambient; 
	light difuse; 
	light specular; 
};

std::tuple< int, vector<vec3> >  LoadObj(string file) {
	FILE * fp2;
	errno_t error2;

	error2 = fopen_s(&fp2, ("Resources\\" + file + ".mtl").c_str(), "r");

	if (error2 != 0) {
		printf("ERROR: Cannot read mtl file \"%s\".\n", file + ".mtl");
		throw EXCEPTION_BREAKPOINT;
	}

	vector< pair< Material, vector < SFace > > > materials;

	char buf2[128];

	while (fgets(buf2, 128, fp2) != NULL) {
		if (buf2[0] == 'n' && buf2[1] == 'e') {
			char mtlName[50];
			sscanf(buf2, "newmtl %s", &mtlName);
			string str(mtlName);

			Material mtl = { str, "" };
			vector<SFace> v; //pusty wektor tymczasowo
			pair< Material, vector< SFace > > p(mtl, v);
			materials.push_back(p);
		}
		if (buf2[0] == 'm' && buf2[1] == 'a' && buf2[2] == 'p' && buf2[3] == '_' && buf2[4] == 'K' && buf2[5] == 'd') {
			char texName[100];
			sscanf(buf2, "map_Kd %s", &texName);
			string str(texName);
			string texPath("Resources\\tex\\" + str);//dopisujemy sciezke wzgledem projektu

			materials.back().first.texturePath = texPath;
		}
		if (buf2[0] == 'K' && buf2[1] == 'a')
		{
			sscanf(buf2, "Ka %f %f %f", &materials.back().first.ambient.r, 
				&materials.back().first.ambient.g, &materials.back().first.ambient.b);
		}
		if (buf2[0] == 'K' && buf2[1] == 'd')
		{
			sscanf(buf2, "Kd %f %f %f", &materials.back().first.difuse.r,
				&materials.back().first.difuse.g, &materials.back().first.difuse.b);
		}
		if (buf2[0] == 'K' && buf2[1] == 's')
		{
			sscanf(buf2, "Ks %f %f %f", &materials.back().first.specular.r,
				&materials.back().first.specular.g, &materials.back().first.specular.b);
		}
	}

	fclose(fp2);

	FILE * fp;
	errno_t error;

	error = fopen_s(&fp, ("Resources\\" + file + ".obj").c_str(), "r");

	if (error != 0) {
		printf("ERROR: Cannot read model file \"%s\".\n", file + ".obj");
		throw EXCEPTION_BREAKPOINT;
	}

	vector<vec3> * v = new vector<vec3>();
	vector<vec3> * n = new vector<vec3>();
	vector<vec3> * t = new vector<vec3>();
	vector<SFace> * f = new vector<SFace>();

	std::vector<vec3> extremePeaks;


	char buf[128];

	pair< Material, vector< SFace > >* currentPair;

	while (fgets(buf, 128, fp) != NULL) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 * vertex = new vec3();
			sscanf(buf, "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			v->push_back(*vertex);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 * vertex = new vec3();
			sscanf(buf, "vt %f %f", &vertex->x, &vertex->y);
			t->push_back(*vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 * vertex = new vec3();
			sscanf(buf, "vn %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			n->push_back(*vertex);
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace * face = new SFace();
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face->v[0], &face->t[0], &face->n[0],
				&face->v[1], &face->t[1], &face->n[1],
				&face->v[2], &face->t[2], &face->n[2]
				);
			currentPair->second.push_back(*face);
		}
		if (buf[0] == 'u' && buf[1] == 's') {
			char mtlName[50];
			sscanf(buf, "usemtl %s", &mtlName);
			string str(mtlName);

			for (int i = 0; i < materials.size(); i++)
				if (materials[i].first.name == str)
					currentPair = &materials[i];
		}
	}

	fclose(fp);

	//szukanie punktow max i min do kolizji 
	vec3 xmin = (*v)[0];
	vec3 xmax = xmin;
	vec3 ymin = (*v)[0];
	vec3 ymax = ymin;
	vec3 zmin = (*v)[0];
	vec3 zmax = zmin;

	for (int i = 1; i < v->size(); i++)
	{
		vec3 nextPoint = (*v)[i];
		if (nextPoint.x < xmin.x)
			xmin = nextPoint;
		else if (nextPoint.x > xmax.x)
			xmax = nextPoint;
		if (nextPoint.y < zmin.y)
			ymin = nextPoint;
		else if (nextPoint.y > zmax.y)
			ymax = nextPoint;
		if (nextPoint.z < zmin.z)
			zmin = nextPoint;
		else if (nextPoint.z > zmax.z)
			zmax = nextPoint;
	}

	extremePeaks.push_back(xmin);
	extremePeaks.push_back(zmin);
	extremePeaks.push_back(xmax);
	extremePeaks.push_back(zmax);
	extremePeaks.push_back(ymin);
	extremePeaks.push_back(ymax);


	GLuint* textures = new GLuint[materials.size()];
	//generowanie id tekstur, przekazuje wypelniona randomowo tablice id tekstur, 
	//a opengl oddaje wypelniona poprawnie
	glGenTextures(materials.size(), textures);
	for (int i = 0; i < materials.size(); i++)
	{
		string str = materials[i].first.texturePath;
		char* writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';
		CTexture tex(writable, textures[i]);
		tex.Load(false);
		delete[] writable;
	}

	GLuint dlId;
	dlId = glGenLists(1);
	glNewList(dlId, GL_COMPILE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_TEXTURE_2D);

	for (int k = 0; k < materials.size(); k++) {
		GLuint tx = textures[k];

		glBindTexture(GL_TEXTURE_2D, tx);//korzystamy z tekstury o podanym id

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < materials[k].second.size(); i++) {

			//float m0_amb[] = { materials[k].first.ambient.r, materials[k].first.ambient.g,materials[k].first.ambient.b };
			//float m0_dif[] = { materials[k].first.difuse.r, materials[k].first.difuse.g,materials[k].first.difuse.b };
			//float m0_spe[] = { materials[k].first.specular.r, materials[k].first.specular.g,materials[k].first.specular.b };
			//glMaterialfv(GL_FRONT, GL_AMBIENT, m0_amb);
			//glMaterialfv(GL_FRONT, GL_DIFFUSE, m0_dif);
			//glMaterialfv(GL_FRONT, GL_SPECULAR, m0_spe);
			//glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);

			for (int j = 0; j < 3; j++) {
				vec3 * cv = &(*v)[(materials[k].second[i].v[j] - 1)];
				vec3 * ct = &(*t)[(materials[k].second[i].t[j] - 1)];
				vec3 * cn = &(*n)[(materials[k].second[i].n[j] - 1)];
				glTexCoord2f(ct->x, ct->y);
				glNormal3f(cn->x, cn->y, cn->z);
				glVertex3f(cv->x, cv->y, cv->z);
			}
		}
		glEnd();

	}


	glDisable(GL_TEXTURE_2D);

	glEndList();

	delete textures;
	delete v;
	delete n;
	delete t;
	delete f;

	return std::make_tuple(dlId, extremePeaks);
}
