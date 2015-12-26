#include "stdafx.h"
#include "ObjLoader.h"
#include "Vec3.h"
#include <tuple>

using namespace std;

std::tuple< int, vector<vec3> > LoadObj(string file) {

	FILE * fp;
	errno_t error;

	error = fopen_s(&fp, file.c_str(), "r");

	if (error != 0) {
		printf("ERROR: Cannot read model file \"%s\".\n", file);
		throw EXCEPTION_READ_FAULT;
	}

	std::vector<vec3> * v = new std::vector<vec3>();
	std::vector<vec3> * n = new std::vector<vec3>();
	std::vector<vec3> * t = new std::vector<vec3>();
	std::vector<SFace> * f = new std::vector<SFace>();

	std::vector<vec3> extremePeaks; 

	char buf[128];
	
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
			f->push_back(*face);
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

	GLuint dlId;
	dlId = glGenLists(1);//generuje 1 pusta liste 
	glNewList(dlId, GL_COMPILE);


	glBegin(GL_TRIANGLES);
	for (int i = 0; i < f->size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			vec3 * cv = &(*v)[((*f)[i].v[j] - 1)];
			vec3 * ct = &(*t)[((*f)[i].t[j] - 1)];
			vec3 * cn = &(*n)[((*f)[i].n[j] - 1)];
			glTexCoord2f(ct->x, ct->y);
			glNormal3f(cn->x, cn->y, cn->z);
			glVertex3f(cv->x, cv->y, cv->z);
		}
	}
	glEnd();
	glEndList();

	delete v;
	delete n;
	delete t;
	delete f;

	return std::make_tuple(dlId, extremePeaks);
}
