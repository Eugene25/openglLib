
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
#include "MeshStructure.h"

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

typedef glm::vec3 Vec3;

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
	glShadeModel(GL_SMOOTH);

	GLfloat	 lightPosition[] = { 1.0, 2.0, 3.0, 1.0 };
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20,20, -20, 20, 0, 40);
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
	gluLookAt(20, 8, 20, 0, 0, 0, 0.0, 1, 0);

	//glEnable(GL_LINE_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/*std::vector<Vec3> vertex =
		{ { 0, 0, 5 }, { 10.0, 0, 9.0 }, { 10.0, 0, 2.0 },
		{ 0.0, 0, -5.0 }, { -1.0, 0, 5.0 }, { 10.0, 0, 2.0 },
		{ 0, 2, 0 }, { 0, 0, 2 }, {2,0,0},
		{ -5, -5, 2 }, { 0, 2, 0 }, { -5, 0, 5 } };*/

	std::vector<Vec3> vertices = {
		//0
		{-5,5,5},
		//1
		{ -5, -5, 5 },
		//2
		{ 5, -5, 5 },
		//3
		{ 5, 5, 5 },
		//4
		{ 5, 5, -5 },
		//5
		{ 5, -5, -5 },
		//6
		{ -5, -5, -5 },
		//7
		{ -5, 5, -5 }
	};

	GLfloat colors[][3] = {
		{ 1.0, 0, 0 },
		{ 1.0, 1.0, 0 },
		{ 1.0, 0, 1.0 },
		{ 0, 0, 1.0 },
		{ 1.0, 1.0, 0 },
		{ 1.0, 0, 1.0 }
	};

	/*GLubyte index[18] = {
	0, 1, 2 ,
	 3, 0, 2,
	3, 2, 4 ,
	4, 2, 5 ,
	7,0,3,
	7,3,4
	};*/

	std::vector<int> index = {
		0, 1, 2,
		3, 0, 2,
		3, 2, 4,
		4, 2, 5,
		7, 0, 3,
		7, 3, 4
	};

	//vertices to vertex
	/*std::vector<Vec3> vertex;
	Vec3 temp;

	for (int i = 0; i <index.size(); i++) {
		temp.x=vertices[index[i]].x;
		temp.y=vertices[index[i]].y;
		temp.z =vertices[index[i]].z;

		vertex.push_back(temp);

	}

	for (int i = 0; i < vertex.size(); i++) {
		std::cout << "  vertex[" <<i<<" ] = (" << vertex[i].x << ", " << vertex[i].y << ", " << vertex[i].z << ")\n";
	}

	//calculate each normal end start end proint to draw normal vector line
	std::vector<Vec3> faceNormal = calculateFaceNormal(vertex);
	std::vector<Vec3> startCenters = calcualteCenter(vertex);
	std::vector<Vec3> endCenters = calcualteEndCenter(startCenters, faceNormal);
	*/

	MeshStructure MESH;
	MESH.SetMesh(vertices, index);
	

	for (int i = 0; i < MESH.vertex.size(); i += 3) {

		//draw line
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex3f(MESH.startCenters[i / 3].x, MESH.startCenters[i / 3].y, MESH.startCenters[i / 3].z);
		glVertex3f(MESH.endCenters[i / 3].x, MESH.endCenters[i / 3].y, MESH.endCenters[i / 3].z);
		glEnd();

		glColor3f(colors[i / 3][0], colors[i / 3][1], colors[i / 3][2]);
		glBegin(GL_TRIANGLES);

		//first triangle
		glNormal3f(MESH.faceNormal[i / 3].x, MESH.faceNormal[i / 3].y, MESH.faceNormal[i / 3].z);
		glVertex3f(MESH.vertex[i].x, MESH.vertex[i].y, MESH.vertex[i].z);
		glVertex3f(MESH.vertex[i + 1].x, MESH.vertex[i + 1].y, MESH.vertex[i + 1].z);
		glVertex3f(MESH.vertex[i + 2].x, MESH.vertex[i + 2].y, MESH.vertex[i + 2].z);
		glEnd();

	}


	/*vertex =
	{ { -5, 5, 5 }, { -5, -5, 5 }, { 5, -5, 5 },
	{ 5, 5, 5 }, { -5, 5, 5 }, { 5, -5, 5 },
	{ 5, 5, 5 }, { 5, -5, 5 }, { 5, 5, -5 },
	{ 5, 5, -5 }, { 5, -5, 5 }, { 5, -5, -5 },
	{ -5, 5, -5 }, { -5, 5, 5 }, { 5, 5, 5 },
	{ 5, 5, -5 }, { -5, 5, -5 }, { 5, 5, 5 }, };


	std::vector<Vec3> faceNormal = calculateFaceNormal(vertex);
	std::vector<Vec3> startCenters = calcualteCenter(vertex);
	std::vector<Vec3> endCenters = calcualteEndCenter(startCenters, faceNormal);

	for (int i = 0; i < endCenters.size(); i++) {
		std::cout << "  endCenters = (" << endCenters[i].x << ", " << endCenters[i].y << ", " << endCenters[i].z << ")\n";
	}*/
	


	/*glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();          

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, index);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);

	for (int i = 0; i < vertex.size(); i+=3) {

		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(startCenters[i / 3].x, startCenters[i / 3].y, startCenters[i / 3].z);
		glVertex3f(endCenters[i / 3].x, endCenters[i / 3].y, endCenters[i / 3].z);
		glEnd();

		glColor3f(1.0f, 0, 0);
		glBegin(GL_TRIANGLES);

		//first triangle
		glNormal3f(faceNormal[i / 3].x, faceNormal[i / 3].y, faceNormal[i / 3].z);
		glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
		glVertex3f(vertex[i + 1].x, vertex[i + 1].y, vertex[i + 1].z);
		glVertex3f(vertex[i + 2].x, vertex[i + 2].y, vertex[i + 2].z);
		glEnd();

	}*/

	glutSwapBuffers();




	/*if (!isSmooth)	glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);

	if (!isLine)	{
		drawMap();
		drawPlane();
	}
	else {
		drawLineMap();
	}
	loadAndDrawObj();
	glutSwapBuffers();*/

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
