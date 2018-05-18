#include <GLTools.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <math.h>
#include <vector>

#include <glm/glm.hpp>

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

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------


void init(void) {

	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, 0, 50);
	//glOrtho(-10, 10, -10,10, 0,10);
	glMatrixMode(GL_MODELVIEW);




}


void drawCube(float width, float height) {

	// color array
	GLfloat colors[] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,   // v0,v1,v2,v3 (front)
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,   // v0,v3,v4,v5 (right)
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,   // v0,v5,v6,v1 (top)
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,   // v1,v6,v7,v2 (left)
		0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,   // v7,v4,v3,v2 (bottom)
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 }; // v4,v7,v6,v5 (back)

	GLubyte indices[] = {
		0, 1, 2, 2, 3, 0,   // 36 of indices
		0, 3, 4, 4, 5, 0,
		0, 5, 6, 6, 1, 0,
		1, 6, 7, 7, 2, 1,
		7, 4, 3, 3, 2, 7,
		4, 7, 6, 6, 5, 4 };

	GLfloat vertices[] = {
		width, height, width,
		-width, height, width,
		-width, -8.0f, width,
		width, -8.0f, width,
		width, -8.0f, -width,
		width, height, -width,
		-width, height, -width,
		-width, -8.0f, -width,
	};          // 8 of vertex coords
	// normal array
	GLfloat normals[] = {
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,   // v0,v1,v2,v3 (front)

		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,   // v0,v3,v4,v5 (right)

		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,   // v0,v5,v6,v1 (top)

		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,   // v1,v6,v7,v2 (left)

		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,   // v7,v4,v3,v2 (bottom)
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1 }; // v4,v7,v6,v5 (back)

	GLfloat colors2[] = {
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,     // v0,v1,v2,v3 (front)

		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,   // v0,v3,v4,v5 (right)

		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,     // v0,v5,v6,v1 (top)

		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,   // v1,v6,v7,v2 (left)

		0, 0, 0,
		0, 0, 1,
		1, 0, 1,
		1, 0, 0,   // v7,v4,v3,v2 (bottom)

		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1, }; // v4,v7,v6,v5 (back)

	GLubyte indices2[] = {
		0, 1, 2, 3,   // 8*3=24 of indices
		0, 3, 4, 4,
		0, 5, 6, 1,
		1, 6, 7, 2,
		7, 4, 3, 2,
		4, 7, 6, 5, };



	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors2);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices2);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void drawCylinder(float width, float height, float r, float g, float b) {

	glBegin(GL_TRIANGLE_FAN);

	glNormal3f(0.0f, 1.0f, 0.0f);
	//change y value here and in the vertex below to move the end up or
	// down to seal the top end of the cylinder
	glVertex3f(0.0f, height, 0.0f);
	glColor3f(1, 1, 1);
	for (int i = 0; i <= 300; i++)
	{

		glVertex3f(width * cos(-i), height, width * sin(-i));
	}

	glEnd();



	// bottom end of cylinder
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, -1.0f, 0.0f);
	//change y value here and in the vertex below to move the end up or
	// down to seal the bottom end of the cylinder. Delete for a cone
	glVertex3f(0.0f, 0, 0.0f);
	for (int i = 0; i <= 300; i++)
	{
		glVertex3f(width * cos(i), 0, width * sin(i));
	}

	glEnd();

	glColor3f(r, g, b);
	//side of cylinder, y-values are used for the length of the cylinder
	//x and z values are used for the radius.
	// for a cone change y values to integers for the length.
	for (int j = 0; j <= 45; j++){
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i<300; i++){

			glNormal3f(width * cos(i), 0.0f, width * sin(i));

			//  for a cone change the x and z values to 0 for a central cone or other integers for an offset cone
			// don't forget to delete the bottom end circle above.

			glVertex3f(width * cos(i), (j) / 5, width * sin(i));
			glVertex3f(width * cos(i), (j + 1) / 5, width * sin(i));
		}
	}
	glEnd();
}

void drawPlane() {
	glColor3f(1.0f, 0.6f, 0.2f);
	glBegin(GL_QUADS);

	glVertex3f(-50.0f, -10.0f, -50.0f);
	glVertex3f(-50.0f, -10.0f, 50.0f);
	glVertex3f(50.0f, -10.0f, 50.0f);
	glVertex3f(50.0f, -10.0f, -50.0f);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void drawTriangle() {

	GLfloat colors[] = {
		1, 1, 0,
		1, 1, 0,
		1, 1, 0,
	}; // v4,v7,v6,v5 (back)

	GLubyte indices[] = {
		0, 1, 2 };

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0,
		1.0f, 0, 0,
		-1.0f, 1.0f, 0
	};          // 8 of vertex coords
	// normal array
	GLfloat normals[] = {
		0, 0, 1.0f,
		0, 0, 1.0f,
		0, 0, 1.0f
	}; // v4,v7,v6,v5 (back)





	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void drawRectangle() {

	GLfloat colors[] = {
		1, 1, 0,
		1, 1, 0,
		1, 1, 0,
		1, 1, 0
	}; // v4,v7,v6,v5 (back)

	GLubyte indices[] = {
		0, 1, 2, 3 };

	GLfloat vertices[] = {
		1.0f, -1.0f, 0,
		1.0f, 1.0f, 0,
		-1.0f, 1.0f, 0,
		-1.0f, -1.0f, 0
	};          // 8 of vertex coords
	// normal array
	GLfloat normals[] = {
		0, 0, 1.0f,
		0, 0, 1.0f,
		0, 0, 1.0f,
		0, 0, 1.0f
	}; // v4,v7,v6,v5 (back)





	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_QUADS, 16, GL_UNSIGNED_BYTE, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void drawMap() {
	glPushMatrix();
	glTranslated(8.0f, 0, 0);
	drawCube(2.0f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0f, 0, 0);
	drawCube(5.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0f, 0, 0);
	drawCylinder(0.5f, 10.0f, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glScalef(3.0f, 3.0f, 3.0f);
	glTranslated(3.2f, 6.0f, 0);
	drawTriangle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0f, 0, -5.0f);
	drawCube(5.0f, 0.0f);
	glPopMatrix();




	/*second building*/
	glPushMatrix();
	glTranslated(30.0f, 0, 17.0f);
	drawCube(5.0f, 0.0f);
	drawCylinder(1.0f, 10.0f, 1.0f, 1.0f, 1.0f);
	glTranslated(-1.0f, 0, 7.0f);
	drawRectangle();
	glTranslated(3.0f, 0, 0);
	drawRectangle();
	glPopMatrix();







	/*third building*/
	glPushMatrix();
	glTranslated(-30.0f, 10, 30.0f);
	drawCylinder(3.0f, 10.0f, 1.0f, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-25.0f, 10, 30.0f);
	drawCube(4.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-30.0f, 0, 30.0f);
	drawCylinder(5.0f, 10.0f, 0.5f, 0.5f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glScalef(3.0f, 3.0f, 3.0f);
	glTranslated(-8.0f, 8.0f, 8.0f);
	drawTriangle();
	glPopMatrix();
}


std::vector< glm::vec3 > vertices;
std::vector< glm::vec3 > vertices_1;
std::vector< glm::vec3 > vertices_2;
std::vector< glm::vec3 > vertices_3;
std::vector< glm::vec3 > vertices_4;
std::vector< glm::vec3 > vertices_5;

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

		printf("vertex Index = %d \n", vertexIndex - 1);

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


void drawObj(std::vector < glm::vec3 > & draw_vertices) {


	//glBegin(GL_TRIANGLE_STRIP);
	glBegin(GL_LINES);
	for (int i = 0; i < draw_vertices.size(); i++) {
		glVertex3f(draw_vertices[i].x, draw_vertices[i].y, draw_vertices[i].z);
		printf("Vertex[%d] = (%f,%f,%f) \n", i, draw_vertices[i].x, draw_vertices[i].y, draw_vertices[i].z);
	}


	glEnd();

}

void loadAndDrawObj() {

	loadOBJ("lamp.obj", vertices_1, uvs, normals);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(-10.0f, 0, 0);
	drawObj(vertices_1);
	glPopMatrix();

	loadOBJ("shuttle.obj", vertices_2, uvs, normals);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(-10.0f, 30.0f, 10.0f);
	drawObj(vertices_2);
	glPopMatrix();

	loadOBJ("ai.obj", vertices_3, uvs, normals);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(40.0f, 0, 0);
	drawObj(vertices_3);
	glPopMatrix();


	loadOBJ("teapot.obj", vertices_4, uvs, normals);
	glPushMatrix();
	glScalef(0.05f, 0.05f, 0.05f);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(-40.0f, 0, 0);
	drawObj(vertices_4);
	glPopMatrix();

	loadOBJ("humanoid.obj", vertices_5, uvs, normals);
	glPushMatrix();
	glScalef(0.05f, 0.05f, 0.05f);
	glTranslatef(50.0f, 0, -20.0f);
	glColor3f(0.5, 0.5, 0.5);
	drawObj(vertices_5);
	glPopMatrix();

}

void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	//glRotatef(rotate_x, 1.0, 0.0, 0.0);
	//glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//gluLookAt(1.5, 1.5, 1, 0, 0, 0, 0, 1, 0);
	//gluLookAt(0.5,0.5, 1, 0, 0, 0, 0, 1, 0);
	gluLookAt(3.6, 20.7, 20, 0, 0, 0, 0.0, 1, 0);


	//drawMap();
	//loadAndDrawObj();


	// Draw ground
	drawPlane();


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

	//bool res = loadOBJ("lamp.obj", vertices_3, uvs, normals);
	//bool res = loadOBJ("lamp.obj", vertices_4, uvs, normals);
	//bool res = loadOBJ("lamp.obj", vertices_5, uvs, normals);

	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);


	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
