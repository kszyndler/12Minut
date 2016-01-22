#include "stdafx.h"
#include "Interface.h"


Interface::Interface()
{
}


Interface::~Interface()
{
}
void Interface::draw(float x, float y, void * font, char * string)
{
	glColor4f(1.0, 0.0, 0.0, 1.0);

	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(x, y, font, string);
	glPopMatrix();
	restorePerspectiveProjection();
}

void Interface::setOrthographicProjection()
{

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
}
void Interface:: restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}
void Interface:: renderSpacedBitmapString(float x, float y, int spacing, void *font, char *string)
{
	char *c;
	int x1 = x;

	for (c = string; *c != '\0'; c++) {

		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c) + spacing;
	}
}
void Interface::renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font, char *string)
{
	char *c;
	int i;

	for (c = string, i = 0; *c != '\0'; i++, c++) {

		glRasterPos2f(x, y + bitmapHeight*i);
		glutBitmapCharacter(font, *c);
	}
}
void Interface::renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void Interface::initBackground(float x, float y, float width, float height)
{
	float xo = x - width/2; 
	float yo = y - height / 2;
	float xk = x + width / 2;
	float yk = y + width / 2;

	backgroundListId = glGenLists(1);

	glNewList(backgroundListId, GL_COMPILE);
	glBegin(GL_QUADS);
		glVertex2f(xk, yk);
		glVertex2f(xk, yo);
		glVertex2f(xo, yo);
		glVertex2f(xo, yk);

	glEnd();
	glEndList();
}