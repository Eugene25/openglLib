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

GLBatch				topBlock;
GLBatch				frontBlock;
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;

int w, h;

createCity::createCity(){}
createCity::~createCity(){}

static float move_unit = 0.1f;

void display(void);


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

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0,10, 0,10);
	//glMatrixMode(GL_MODELVIEW);



}

void menuSelect() {
	if (value == 1){ //restart
		angle = 0.0, posX = 0, posY = 0, posZ = 0;
		glutDisplayFunc(display);
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
}



void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	menuSelect();

	glViewport(0, (1.5*h) / 5, w, (3.5*h) / 5);

	glPushMatrix();
	drawCar(posX,posY,angle);
	glPopMatrix();

	glPushMatrix();
	drawMapAndCity();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
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
	setTexture();
	init();

	 createMenuCG();
	glutDisplayFunc(display);
	glutSpecialFunc(keyboardown);


	glutMainLoop();
	return 0;
}
