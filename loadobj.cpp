#include <GLTools.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <math.h>
#include <vector>

#include <glm/glm.hpp>

#define _CRT_SECURE_NO_WARNINGS
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

/*file load variables*/
GLint big;
float bigtrot;
char ch = '1';
FILE *fp;
GLfloat indicies[];

float vertices[1000];
float faces[1000];

using namespace std;
using namespace glm;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


void loadObj(char *fname) {


	int read;
	GLfloat x, y, z;
	char ch;
	int i = 0;
	int j = 0;


	big = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp) {
		printf("can't open file %s \n", fname);
		exit(1);
	}
	glPointSize(2.0);
	glNewList(big, GL_COMPILE);

	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp))) {
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v') {
				//std::cout << "(x,y,z) = (" << x << ", " << y << ", " << z << ") \n";
				glVertex3f(x, y, z);
				vertices[i] = x;
				vertices[i+1] = y;
				vertices[i+2] = z;
				//std::cout << "(vertices : x,y,z) = (" << x << ", " << y << ", " << z << ") \n";

				i += 3;
				//printf("current index [i] = %d \n", i);
			}
			if (read == 4 && ch == 'f') {
				//std::cout << "(x,y,z) = (" << x << ", " << y << ", " << z << ") \n";
				glVertex3f(x, y, z);
				faces[j] = x;
				faces[j + 1] = y;
				faces[j + 2] = z;
				//std::cout << "faces" << j << ": (x,y,z) = (" << x << ", " << y << ", " << z << ") \n";

				j += 3;
				//printf("current index = %d \n", j);
			}
			
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);

	


}

void drawBig() {

	int read;
	GLfloat x, y, z;
	char ch;



	//glTranslatef(0, -40, -105);
	glColor3f(1.0, 0, 0);

	std::cout << ("Here : 1 \n");
	std::cout << "Vertices" << vertices[0] << "\n";
	std::cout << "Indices" << faces[0] << "\n";

	glPointSize(3.0);
	glBegin(GL_POINTS);

	for (int a = 0; a < 18; a+=3) {
		glVertex3d(vertices[a], vertices[a + 1], vertices[a + 2]);
	}
	glEnd();

	/*glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glNormalPointer(GL_FLOAT, 0, normals);
	//glColorPointer(3, GL_FLOAT, 0, colors2);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_BYTE, faces);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);*/











	//glRotatef(bigtrot, 0, 1, 0);
	//glCallList(big);

	//bigtrot = bigtrot + 0.6;
	//if (bigtrot > 360) bigtrot = bigtrot - 360;
}

void init(void) {

	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-100, 100, -100, 100,0,100);
	glOrtho(-10, 10, -10,10, 0,10);
	glMatrixMode(GL_MODELVIEW);




}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawBig();
	glutSwapBuffers();
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
	loadObj("before.obj");
	
	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
