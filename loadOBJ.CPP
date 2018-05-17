https://www.gamedev.net/forums/topic/692339-importing-obj-model-to-opengl/
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

//float vertices[1000];
//float faces[1000];

using namespace std;
using namespace glm;

std::vector < glm::vec3 > out_vertices;
std::vector < glm::vec2 >  out_uvs;
std::vector < glm::vec3 > out_normals;

GLfloat vertice[1000];
GLfloat normal[1000];
GLfloat indice[1000];
int i = 0;
int j = 0;
int k = 0;


std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals; // Won't be used at the moment.


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


void loadObj(char *fname) {

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	//std::vector< glm::vec3 > temp_vertices;
	//std::vector< glm::vec2 > temp_uvs;
	//std::vector< glm::vec3 > temp_normals;

	GLfloat x, y, z;

	FILE * file = fopen(fname, "r");
	if (file == NULL){
		printf("Impossible to open the file !\n");
	}

	while (1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0){

			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			//fscanf(file, "%f %f %f\n", &x, &y, &z);
			//std::cout << "vertices : (x,y,z) = (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ") \n";
			temp_vertices.push_back(vertex);

			vertice[i] = vertex.x;
			vertice[i + 1] = vertex.y;
			vertice[i + 2] = vertex.z;

			printf("vertice[%d] = (%f,%f,%f) \n", i, vertice[i], vertice[i + 1], vertice[i + 2]);

		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			//std::cout << "normal : (x,y,z) = (" << normal.x << ", " << normal.y << ", " << normal.z << ") \n";
			temp_normals.push_back(normal);

			normal[i] = normal.x;
			normal[i + 1] = normal.y;
			normal[i + 2] = normal.z;

			printf("Normal[%d] = (%f,%f,%f) \n", i, normal[i], normal[i + 1], normal[i + 2]);



		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], 
				&normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			}

			indice[i] = vertexIndex[0];
			indice[i + 1] = vertexIndex[1];
			indice[i + 2] = vertexIndex[2];

			printf("Indice[%d] = (%f,%f,%f) \n", i, indice[i], indice[i + 1], indice[i + 2]);

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

			for (unsigned int i = 0; i < vertexIndices.size(); i++){
				unsigned int vertexIndex = vertexIndices[i];
				glm::vec3 vertex = temp_vertices[vertexIndex - 1];
				std::cout << "vertexIndex = (" << vertexIndices[i] << ") \n";
				out_vertices.push_back(vertex);
			}

			/*for (unsigned int i = 0; i < uvIndices.size(); i++){
				unsigned int uvIndices = uvIndices[i];
				glm::vec2 indice = temp_vertices[uvIndices - 1];
				out_uvs.push_back(indice);
			}*/
			i += 3;
			std::cout << "current index is " << i << "/n";
		}

	
}



void drawBig() {

	int read;
	GLfloat x, y, z;
	char ch;



	//glTranslatef(0, -40, -105);
	glColor3f(1.0, 0, 0);
	glPointSize(3.0);
	glBegin(GL_POINTS);

	/*for (int a = 0; a < 18; a+=3) {
		glVertex3d(vertices[a], vertices[a + 1], vertices[a + 2]);
	}
	glEnd();*/

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
	
	//drawBig();
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

	
	//loadObj("before.obj");
	
	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
