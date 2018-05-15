#include <GLTools.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>

#include <glm/glm.hpp>

#define PI 3.1415926535898
#define cos(th) cos(PI/180*(th))
#define sin(th) sin(PI/180*(th))
#define Degree 5


/*using openGL and freegult*/
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
using namespace std;
using namespace glm;
float cameraX=0, cameraY=0.1f, cameraZ=1.0f;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


void init(void) {

	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-50, 50, -50, 50,0,50);
	glOrtho(-10, 10, -10,10, 0,10);
	glMatrixMode(GL_MODELVIEW);




}


void drawCube() {

	GLfloat vertices[] = { 
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
	};          // 8 of vertex coords
	// normal array
	GLfloat normals[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,   // v0,v1,v2,v3 (front)
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,   // v0,v3,v4,v5 (right)
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,   // v0,v5,v6,v1 (top)
		-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,   // v1,v6,v7,v2 (left)
		0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,   // v7,v4,v3,v2 (bottom)
		0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1 }; // v4,v7,v6,v5 (back)

	// color array
	GLfloat colors[] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1,   // v0,v1,v2,v3 (front)
		1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,   // v0,v3,v4,v5 (right)
		1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,   // v0,v5,v6,v1 (top)
		1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,   // v1,v6,v7,v2 (left)
		0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,   // v7,v4,v3,v2 (bottom)
		0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1 }; // v4,v7,v6,v5 (back)

	GLubyte indices[] = { 
		0, 1, 2, 2, 3, 0,   // 36 of indices
		0, 3, 4, 4, 5, 0,
		0, 5, 6, 6, 1, 0,
		1, 6, 7, 7, 2, 1,
		7, 4, 3, 3, 2, 7,
		4, 7, 6, 6, 5, 4 };

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}



void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	//glRotatef(rotate_x, 1.0, 0.0, 0.0);
	//glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//gluLookAt(1.5, 1.5, 1, 0, 0, 0, 0, 1, 0);
	//gluLookAt(0,0.5, 1, 0, 0, 0, 0, 1, 0);

	

	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0.0, 1.0, 0.0);

	//glColor3f(1.0f, 0, 0);
	drawCube();

	// Draw ground
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glVertex3f(-50.0f, -20.0f, -50.0f);
	glVertex3f(-50.0f, -20.0f, 50.0f);
	glVertex3f(50.0f, -20.0f, 50.0f);
	glVertex3f(50.0f, -20.0f, -50.0f);
	glEnd();

	glFlush();
	glutSwapBuffers();

}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	float fraction = 0.1f;

	//  Right arrow - increase rotation by 5 degree
	switch (key) {
	case GLUT_KEY_LEFT:
		cameraX -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		cameraX += 0.1f;
		break;
	case GLUT_KEY_UP:
		cameraY += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		cameraY -= 0.1f;
		break;
	}

	//  Request display update
	glutPostRedisplay();

}



// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){

	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(900, 700);
	glutCreateWindow("HW#2");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	init();
	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	
	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
