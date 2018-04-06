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
#include "createCity.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


static int MyListId[10];

class displayList
{
public:
	displayList();
	~displayList();

	void MyCreateList();

};

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

	MyListId[1] = glGenLists(2); //draw star
	glNewList(MyListId[1], GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex2f(-3, 0.0);
	glColor3f(0, 1, 0);
	glVertex2f(-5, 2);
	glVertex2f(-1, 3);
	glVertex2f(0.0, 5);
	glVertex2f(1, 3);
	glColor3f(0, 0, 1);
	glVertex2f(5, 2);
	glVertex2f(3, 0);
	glVertex2f(5, -5);
	glColor3f(0, 1, 1);
	glVertex2f(0, -2);
	glVertex2f(-5, -5);
	glEnd();
	glEndList();

	MyListId[2] = glGenLists(3); //draw flag head
	glNewList(MyListId[2], GL_COMPILE);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(2, 5);
	glVertex2f(2, 9);
	glColor3f(1, 0.5, 0.2);
	glVertex2f(4, 7);
	glEnd();
	glEndList();

	MyListId[3] = glGenLists(4); //draw flag line
	glNewList(MyListId[3], GL_COMPILE);
	glBegin(GL_LINES);
	glVertex2f(2, 5);
	glColor3f(0, 0.5, 0.2);
	glVertex2f(2, 2);
	glEnd();
	glEndList();

	MyListId[4] = glGenLists(5); //draw roof
	glNewList(MyListId[4], GL_COMPILE);
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(5, 9);
	glColor3f(0.8, 1, 0.8);
	glVertex2f(2, 7);
	glVertex2f(2, 5);
	glColor3f(0, 0.2, 0.9);
	glVertex2f(8, 5);
	glColor3f(0.8, 1, 0.8);
	glVertex2f(8, 7);
	glEnd();

	glEndList();

	MyListId[5] = glGenLists(6); //draw window
	glNewList(MyListId[5], GL_COMPILE);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(0, 0);
	glVertex2f(3.8, 3.5);

	glTexCoord2f(0, 1.0f);
	glVertex2f(3.6, 4.5);

	glTexCoord2f(0.5f, 0.0f);
	glVertex2f(5.0, 3.5);

	glTexCoord2f(0.5f, 1.0f);
	glVertex2f(5.0, 4.5);

	glTexCoord2f(1.0f, 0);
	glVertex2f(6.0, 3.5);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(6.2, 4.5);

	glEnd();
	glEndList();

	MyListId[6] = glGenLists(7); //draw car
	glNewList(MyListId[6], GL_COMPILE);
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
	glEndList();

	MyListId[7] = glGenLists(8); //draw circle
	glNewList(MyListId[7], GL_COMPILE);
		glBegin(GL_POLYGON);
		double rad = 1;
		for (int i = 0; i<360; i++)
		{
			double angle = i*3.141592 / 180;
			double x = rad*cos(angle);
			double y = rad*sin(angle);
			glTexCoord2f(x, y);
			glVertex2f(x, y);
		}
	glEnd();
	glEndList();


	MyListId[8] = glGenLists(9); //draw circle
	glNewList(MyListId[8], GL_COMPILE);
	glColor3f(1, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(4, 1.8);
	glVertex2f(4, 3);
	glEnd();
	glEndList();
}
