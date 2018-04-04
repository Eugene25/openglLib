#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "createCity.h"
#include "popUp.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#define GAP 1000
#define MAX_TEXT_SIZE 255

using namespace std;

/*create brick texture*/

/*move car*/
float angle = 0.0, posX = 0, posY = 0, posZ = 0;

GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;
GLFrame				cameraFrame;
GLFrustum			viewFrustum;
GLBatch				cubeBatch;
GLBatch				floorBatch;
GLBatch				topBlock;
GLBatch				frontBlock;
GLBatch				leftBlock;
GLGeometryTransform	transformPipeline;
M3DMatrix44f		shadowMatrix;
// Keep track of effects step
int nStep = 0;

//for timer
static int g_counter = 0;
static int j = 0;

int w, h;

createCity::createCity(){}
createCity::~createCity(){}

static float move_unit = 0.1f;

void RenderScene(void);
bool isDisplayList = false;

void KeyPressFunc(unsigned char key, int x, int y)
{
	if (key == 32)
	{
		nStep++;
		if (nStep > 2)
			nStep = 0;
	}
	// Refresh the Window
	glutPostRedisplay();
}

void keyboardown(int key, int x, int y)
{
	cout << "speed = " << move_unit << "\n";

	switch (key){
	case GLUT_KEY_RIGHT:
		angle = 180;
		posX += move_unit;
		break;

	case GLUT_KEY_LEFT:
		angle = 0;
		posX -= move_unit;
		break;

	case GLUT_KEY_UP:
		angle = -90;
		posY += move_unit;
		break;

	case GLUT_KEY_DOWN:
		angle = 90;
		posY -= move_unit;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void init(void) {

	glClearColor(0, 0, 0, 0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0,10, 0,10);
	//glMatrixMode(GL_MODELVIEW);



}

void menuSelect() {
	if (value == 1){ //restart
		angle = 0.0, posX = 0, posY = 0, posZ = 0;
		glutDisplayFunc(RenderScene);
		value = 0;

	}
	else if (value == 2){ //slow
		move_unit = 0.03f;
	}
	else if (value == 3){ //medium
		move_unit = 0.1f;
	}
	else if (value == 4){ //fast
		move_unit = 0.5f;
	}
	else if (value == 5){
		glShadeModel(GL_SMOOTH);
	}
	else if (value == 6){
		glShadeModel(GL_FLAT);
	}
	else if (value == 7){
		isDisplayList = TRUE;
	}
	else if (value == 8){
		isDisplayList = FALSE;
	}
}

void displayBackground(void) {

	if (!isDisplayList) {
		if (nStep == 0) drawLineMap();
		else if (nStep == 1) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			glPushMatrix();
			drawCar(texture[6], posX, posY, angle);
			glPopMatrix();

			glPushMatrix();
			drawMapAndCity();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
	}
	else {
		if (nStep == 0) drawLineWithDisplayList();
		else if (nStep == 1) {
			glEnable(GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			glPushMatrix();
			initOrtho(-15.0, 5.0, -16.0, 4.0);
			glTranslatef(posX, posY, 0.0);
			glRotatef(angle, 0.0, 0.0, 1.0);
			glTranslatef(-posX, -posY, 0.0);
			glTranslatef(posX, posY, 0.0);
			glBindTexture(GL_TEXTURE_2D, texture[6]);
			glCallList(MyListId[6]);
			glPopMatrix();

			drawMapWithDisplayList();

			glDisable(GL_TEXTURE_2D);
		}
	}

}

void myTimer(int value) {

	g_counter = value + 1;
	glutPostRedisplay();
	glutTimerFunc(GAP, myTimer, g_counter);
}

void displayPanel(void) {

	char text[MAX_TEXT_SIZE];
	sprintf_s(text, "%d", g_counter);

	initOrtho(-1, 1, -1, 1);
	glColor3f(1, 0, 0);
	drawText("time=", 0.35, 0.5);
	drawText(text, 0.5, 0.5);
	drawText("s", 0.55, 0.5);

	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glEnd();
}
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	menuSelect();
	glViewport(0, (1.5*h) / 5, w, (3.5*h) / 5);
	displayBackground();

	glViewport(0, 0, w, (1.5*h) / 5);
	displayPanel();


	glutSwapBuffers();

}

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Making a building");

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	MyCreateList();
	setTexture();
	init();

	createMenuCG();
	glutKeyboardFunc(KeyPressFunc);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(GAP, myTimer, 0);
	glutSpecialFunc(keyboardown);


	glutMainLoop();
	return 0;
}
