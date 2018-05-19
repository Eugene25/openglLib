#include <GLTools.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <math.h>
#include <vector>

#include <glm/glm.hpp>

//#include "drawPrimitive.h"
#include "drawObject.h"
#include "popUp.h"

#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
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
float cameraX = 0, cameraY = 0.1f, cameraZ = 1.0f;

double dim = 2.0;

float radius = 0.3f;
float height = 1.0f;

bool isLine = false;
bool isSmooth = false;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


struct Mesh {
	std::vector< glm::vec3> vertices;
	std::vector< glm::vec2> textCoordinates;
	std::vector< glm::vec3> normals;

	std::vector<unsigned int> v_index;
	std::vector<unsigned int> t_index;
	std::vector<unsigned int> n_index;

	std::vector< glm::vec3> perFaceNormals;
	std::vector< glm::vec3> perVertexNormals;
	std::vector< glm::vec3> perVertexTextCoordinates;


} mesh ;

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

void menuSelect() {
	if (value == 1){ //restart

	}
	else if (value == 2){ //slow

	}
	else if (value == 3){ //medium

	}
	else if (value == 4){ //fast

	}
	else if (value == 5){
		isSmooth = true;
		
	}
	else if (value == 6){
		isSmooth = false;
		
	}
	else if (value == 7){
		isLine = true;
		
	}
	else if (value == 8){
		isLine = false;
		
	}

}



void init(void) {

	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, 0, 50);
	//glOrtho(-10, 10, -10,10, 0,10);
	glMatrixMode(GL_MODELVIEW);




}

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


void display(){

	menuSelect();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	//glRotatef(rotate_x, 1.0, 0.0, 0.0);
	//glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//gluLookAt(1.5, 1.5, 1, 0, 0, 0, 0, 1, 0);
	//gluLookAt(0.5,0.5, 1, 0, 0, 0, 0, 1, 0);
	gluLookAt(3.6, 20.7, 20, 0, 0, 0, 0.0, 1, 0);

	if (!isSmooth)	glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);

	if (!isLine)	{
		drawMap();
		drawPlane();
	}
	else {
		drawLineMap();
	}
	//loadAndDrawObj();


	// Draw ground


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
	createMenuCG();


	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);


	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
