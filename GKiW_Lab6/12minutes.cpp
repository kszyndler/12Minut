#include "stdafx.h"
#include <conio.h>

#pragma region Zmienne globalne

	int mouseX = 0;
	int mouseY = 0;

	bool captureMouse = true;
	bool free3DMovement = false;

	float mouseSensitivity = .15f;

	CScene * Scene;

	bool keystate[255];

#pragma endregion

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640*2, 360*2);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutCreateWindow("12 minut");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	
	float gl_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
	
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);

	// Inicjalizacja sceny.
	Scene = new CScene();
	Scene->Initialize();

	glutMainLoop();

	return 0;
}

#pragma region Obsluga wejscia

	void OnKeyPress(unsigned char key, int x, int y) {
		if (!keystate[key]) {
			keystate[key] = true;
			OnKeyDown(key, x, y);
		}
	}

	void endGame(int someInt)
	{
		glutLeaveMainLoop();
	}
	void renderGoodEnd(int someint)
	{
		Scene->renderGoodEnding();
		glutTimerFunc(14000, endGame, 0);
	}


	void OnKeyDown(unsigned char key, int x, int y) {
		if (key == 27) {
			endGame(27);
		}

		if (key == 32) {
			Scene->start();
			bool isDone = Scene->CallCollectingManager();
			if (isDone)
			{
				glutTimerFunc(15000, renderGoodEnd, 0);
			}

		}
	}

	void OnKeyUp(unsigned char key, int x, int y) {
		keystate[key] = false;
	}

	void OnMouseMove(int x, int y) {
		mouseX = x;
		mouseY = y;
	}

#pragma endregion

void OnTimer(int id) {
	glutTimerFunc(17, OnTimer, 0);
	
	Scene->Update();
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Scene->Render();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(50.0f, (float) width / height, .01f, 100.0f);
}
