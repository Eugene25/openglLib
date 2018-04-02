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

int w, h;

createCity::createCity(){}
createCity::~createCity(){}

static float move_unit = 0.1f;

void RenderScene(void);

int MyListId[2];
bool isDisplayList = false;

void MyCreateList() {

	MyListId[0] = glGenLists(1); //draw baclground
	glNewList(MyListId[0], GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0); //Left bottom

		glTexCoord2f(1.0f, 0);
		glVertex3f(10, 0, 0); //Right bottom

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10, 10, 0); //Right top

		glTexCoord2f(0, 1.0f);
		glVertex3f(0, 10, 0); //Left top
		glEnd();
	glEndList();

	MyListId[1] = glGenLists(2);
	glNewList(MyListId[1], GL_COMPILE);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-1, -1, 0.0);
	glVertex3f(1, -1, 0.0);
	glVertex3f(1, 1, 0.0);
	glVertex3f(-1, 1, 0.0);
	glEnd();
	glEndList();
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

	glClearColor(1, 1, 1, 0);
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



void RenderCity(void) {

		//glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDisable(GL_CULL_FACE);

		glPushMatrix();
		drawCar(NULL,0, 0, 0);

		/*first apart*/
		initOrtho(-15, 35, -20, 35);
		createWindow(NULL);
		createBuilidng(NULL,0, 0, 0, 0, 0);

		/* second apple office */

		initOrtho(-23.5, 35, -50, 5);
		createCircle(NULL);
		initOrtho(-15, 35, -50, 10);
		createBuilidng(NULL, 0, 0, 0, 0, 0);

		/* third building with star */

		initOrtho(-100, 27, -120, 65);
		createStar();


		initOrtho(-50, 20, -30, 20);
		createWindow(NULL);
		createBuilidng(NULL, 2, 0, 1.8, 2, 0);


		/* fourth school */
		initOrtho(2, 50, -20, 35);
		createWindow(NULL);
		initOrtho(-2, 50, -20, 35);
		createWindow(NULL);

		initOrtho(0, 50, -20, 35);
		createBuilidng(NULL, 3, 0, 3, 3, 0);

		initOrtho(-2, 50, -28, 35);
		createFlag();


		/* fifth restroom */
		initOrtho(0, 60, -50, 10);
		createRoof();
		createWindow(NULL);
		createBuilidng(NULL, 2, 0, 1, 2, 0);


		/*background map*/

		initOrtho(0, 10, 0, 10);

		if (!isDisplayList) {
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0); //Left bottom

			glTexCoord2f(1.0f, 0);
			glVertex3f(10, 0, 0); //Right bottom

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(10, 10, 0); //Right top

			glTexCoord2f(0, 1.0f);
			glVertex3f(0, 10, 0); //Left top
			glEnd();
		}
		else {
			glCallList(MyListId[0]);
		}

		glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	//glDisable(GL_STENCIL_TEST);


}

void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	menuSelect();
	glViewport(0, (1.5*h) / 5, w, (3.5*h) / 5);
	
	if (nStep == 0)
	{
		RenderCity();

	} else if(nStep==1) {

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
	glutSwapBuffers();

}

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
	glutSpecialFunc(keyboardown);


	glutMainLoop();
	return 0;
}
