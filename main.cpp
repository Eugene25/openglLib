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
#define PIE 3.141593

using namespace std;

/*create brick texture*/

/*move car*/
float angle = 0.0, posX = 0, posY = 0, posZ = 0;
float chX = 0, chY = 0, sinX = 0, sinY = 0;
float spiralX =0, spiralY=0, theta=0.0f;
float sinMove = 0;

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
int nStep = 1;

//for timer
int g_counter = 0;
static int j = 0;

int w, h;

static float move_unit = 0.1f;
static float idle_move = 0.009f;
static float sin_move = 0.09f;
static float epsilon = 0.1f * 2.0f * PIE;

void RenderScene(void);
bool isDisplayList = false;
bool isFinishLine = false;

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
}//

void keyboardown(int key, int x, int y)
{
	if (posX >= 4.1)  posX = 4.1;
	else if (posY >= 2.8) posY = 2.8;
	else if (posX <= -14.4) posX = -14.4;
	else if (posY <= -15.4) posY = -15.4;
	else {
		switch (key){
			chX += 0;
			spiralX += 0;
			spiralY += 0;
			sinMove += 0;

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

void sceneChoreo(void) {
	
	/*apple with spiral movement*/
	glPushMatrix();
	if (theta > 30) epsilon = -(0.005f* PIE);
	else if (theta < 0) epsilon = 0.005f* PIE;
	theta += epsilon;
	spiralX = sin(theta) * theta;
	spiralY = cos(theta) * theta;

	initOrtho(-140, 140, -140, 140);
	glTranslatef(spiralX, spiralY, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0.5f);
	glVertex2f(-0.5, 1);
	glVertex2f(-0.5, 2);
	glColor3f(0, 1, 0.7f);
	glVertex2f(0.5, 2);
	glVertex2f(0.5, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	double rad = 1;
	for (int i = 0; i<360; i++)
	{
		double angle = i*PIE / 180;
		double x = rad*cos(angle);
		double y = rad*sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	/*insect with sin movement*/
	glPushMatrix();
	if (sinMove > 10) sin_move = -0.05;
	else if (sinMove <= 0) sin_move = 0.05;
	sinMove += sin_move;
	sinX = sinMove;
	sinY = sin(sinMove*(6.0 / 10.0)) * 3;
	initOrtho(-10, 60, -50, 50);
	glTranslatef(sinX, sinY, 0.0);
	glRotatef(sinY*5, 0.0, 0.0, 1.0);
	glTranslatef(-sinX, -sinY, 0.0);
	glTranslatef(sinX, sinY, 0.0);
	drawLeave();
	glPopMatrix();

	/*Moving car along straight line*/
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	initOrtho(-5.0, 15.0, -16.0, 4.0);
	if (chX >= 14.0f) idle_move = -0.009f;
	else if (chX <= -5.0f) idle_move = 0.009f;
	chX += idle_move;
	glTranslatef(chX, chY, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex2f(-0.5, -0.5);
	glTexCoord2f(0, 1.0f);
	glVertex2f(0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.5, 0.5);
	glTexCoord2f(1.0f, 0);
	glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutPostRedisplay();
	glPopMatrix();



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

	cout << "time : " << value << "\n";

	if (!isFinishLine) {
		g_counter = value+1;

		glutPostRedisplay();
		glutTimerFunc(GAP, myTimer, g_counter);
	}

}

void displayPanel(void) {

	char text[MAX_TEXT_SIZE];
	sprintf_s(text, "%d", g_counter);

	initOrtho(-1, 1, -1, 1);
	glColor3f(1, 0, 0);
	drawText("time=", 0.35, 0.5);
	drawText(text, 0.5, 0.5);
	if (isDisplayList) drawText("display mode = true", -0.8, 0.5);
	else drawText("display mode = false", -0.8, 0.5);
	if (isFinishLine) drawText("Game over", -0.5, -0.5);
	else drawText("Game on Air", -0.5, -0.5);

	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glEnd();
}

void checkFinishLine(void) {
	if (posX >= -7.5 && posX <= -6.5 && posY <= -9.4 && posY >= -12.9) {
		isFinishLine = true;
	}
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	menuSelect();
	glViewport(0, (1.5*h) / 5, w, (3.5*h) / 5);
	sceneChoreo();
	displayBackground();

	glViewport(0, 0, w, (1.5*h) / 5);
	displayPanel();
	checkFinishLine();

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
