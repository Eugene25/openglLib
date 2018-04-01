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

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

using namespace std;

/*create brick texture*/
int textureNum = 7;
GLuint texture[7];

/*move car*/
float theta = 0.0, angle = 0.0, posX = 0, posY = 0, posZ = 0;

GLBatch				topBlock;
GLBatch				frontBlock;
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;

int w, h;

float move_unit = 0.1f;

createCity::createCity(){}
createCity::~createCity(){}


void keyboardown(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_RIGHT:
		angle = 180;
		posX += move_unit;;
		cout << x << endl;
		break;

	case GLUT_KEY_LEFT:
		angle = 0;
		posX -= move_unit;;
		cout << x << endl;
		break;

	case GLUT_KEY_UP:
		angle = -90;
		posY += move_unit;;
		cout << y << endl;
		break;

	case GLUT_KEY_DOWN:
		angle = 90;
		posY -= move_unit;;
		cout << y << endl;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void setTexture(void) {

	GLbyte *pBytes;
	GLint nWidth, nHeight, nComponents;
	GLenum format;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

	glGenTextures(textureNum, texture);


	pBytes = gltReadTGABits("brick.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("window.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("window2.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("map.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("logo.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("school.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("car.tga", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);
}

void init(void) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0,10, 0,10);
	glMatrixMode(GL_MODELVIEW);



}


void initOrtho(int x, int y, int width, int height) {
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(x, y, width, height);
	//glMatrixMode(GL_MODELVIEW);
}

void drawCar() {

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTranslatef(posX, posY, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-posX, -posY, 0.0);
	glTranslatef(posX, posY, 0.0);

	std::cout << "posX = " << posX << ", posY = " << posY << "\n";
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
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

}

void drawMapAndCity() {

	/* first apart building */

	gluOrtho2D(-15, 35, -20, 35);
	createWindow(texture[1]);
	createBuilidng(texture[0], 0, 0, 0, 0, 0);

	/* second apple office */

	initOrtho(-23.5, 35, -50, 5);
	createCircle(texture[4]);
	initOrtho(-15, 35, -50, 10);
	createBuilidng(texture[2], 0, 0, 0, 0, 0);

	/* third building with star */

	glColor3f(1, 1, 0);
	initOrtho(-100, 27, -120, 65);
	createStar();


	initOrtho(-50, 20, -30, 20);
	createWindow(texture[1]);
	createBuilidng(texture[0], 2, 0, 1.8, 2, 0);


	/* fourth school */
	initOrtho(2, 50, -20, 35);
	createWindow(texture[1]);
	initOrtho(-2, 50, -20, 35);
	createWindow(texture[1]);

	initOrtho(-2, 50, -28, 35);
	createFlag();

	initOrtho(0, 50, -20, 35);
	createBuilidng(texture[5], 3, 0, 3, 3, 0);


	/* fifth restroom */
	initOrtho(0, 60, -50, 10);
	createRoof();
	createWindow(texture[1]);
	createBuilidng(texture[0], 2, 0, 1, 2, 0);


	/*background map*/

	initOrtho(0, 10, 0, 10);

	glBindTexture(GL_TEXTURE_2D, texture[3]);

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



void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glViewport(0, (1.5*h) / 5, w, (3.5*h) / 5);
	glPushMatrix();

	drawCar();
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
	glutDisplayFunc(display);

	glutSpecialFunc(keyboardown);


	glutMainLoop();
	return 0;
}
