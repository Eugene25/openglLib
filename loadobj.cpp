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

unsigned int VAO;
unsigned int VBO;
unsigned int VBO_verts;
unsigned int  VBO_indice;
unsigned int  VBO_normals;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

bool loadOBJ(
	const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
	);

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


bool loadOBJ(
const char * fname,
std::vector < glm::vec3 > & out_vertices,
std::vector < glm::vec2 > & out_uvs,
std::vector < glm::vec3 > & out_normals
) {

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

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
			//std::cout << "vertices : (x,y,z) = (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ") \n";
			temp_vertices.push_back(vertex);
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


		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			if (matches != 3){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}

		


		//i += 3;
		//std::cout << "current index is " << i << "/n";
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++){

		unsigned int vertexIndex = vertexIndices[i];

		printf("vertex Index = %d \n", vertexIndex-1);

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];

		out_vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < normalIndices.size(); i++){
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	return true;


}



void drawBig() {



	glBegin(GL_LINES);
	glColor3f(1.0, 0, 0);
	for (int i = 0; i < vertices.size(); i++) {
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		printf("Vertex[%d] = (%f,%f,%f) \n", i, vertices[i].x, vertices[i].y, vertices[i].z);
	}


	glEnd();

	
}

void init(void) {

	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-20, 20, -20, 20,0,20);
	glOrtho(-10, 10, -10, 10, 0, 10);
	//glOrtho(-2, 2, -2, 2, 0, 1);
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
	glutInitWindowSize(700, 700);
	glutCreateWindow("HW#2");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	init();
	// Callback functions
	//glutDisplayFunc(display);



	bool res = loadOBJ("lamp.obj", vertices, uvs, normals);

	/*for (int i = 0; i < vertices.size(); i++) {
		printf("Vertex[%d] = (%f,%f,%f) \n", i, vertices[i].x, vertices[i].y, vertices[i].z);
	}
	for (int i = 0; i < normals.size(); i++) {
		printf("normals[%d] = (%f,%f,%f) \n", i, normals[0].x, normals[0].y, normals[0].z);
	}*/
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glutDisplayFunc(display);


	//loadObj("before.obj");

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
