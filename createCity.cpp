#pragma once

#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include "createCity.h"
#include "displayList.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

int textureNum = 7;
GLuint texture[7];

class createCity
{
public:
	createCity();
	~createCity();

	void initOrtho(int x, int y, int width, int height);
	void setTexture(void);
	void createWindow(GLuint selectedTexture);
	void createBuilidng(GLuint selectedTexture,int level1x, int level1y, int level2x, int level3x, int level3y);
	void createCircle(GLuint selectedTexture);
	void createStar(void);
	void createFlag(void);
	void createRoof(void);
	void drawCar(GLuint selectedTexture, float posX, float posY, float angle);
	void drawMapAndCity();
	void drawMapWithDisplayList(void);
	void drawLineWithDisplayList(void);
	void drawLineMap(void);

};

void initOrtho(int x, int y, int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(x, y, width, height);
	glMatrixMode(GL_MODELVIEW);
}


void setTexture(void) {

	GLbyte *pBytes;
	GLint nWidth, nHeight, nComponents;
	GLenum format;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	/*glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);*/
	glShadeModel(GL_FLAT);
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


void createBuilidng(GLuint selectedTexture, int level1x, int level1y, int level2x, int level3x, int level3y) {

	glBindTexture(GL_TEXTURE_2D, selectedTexture);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0, 0);
	glVertex3f(3.0 - level2x, 5.0, 0); //Left bottom

	glTexCoord2f(0, 1.0f);
	glVertex3f(4.0 - level3x, 7.0 + level3y, 0); //Left top

	glTexCoord2f(1.0f, 0);
	glVertex3f(7.0 + level2x, 5.0, 0); //right botoom

	glTexCoord2f(1.0f, 0);
	glVertex3f(7.0 + level2x, 5.0, 0); //right bottom

	glTexCoord2f(0, 1.0f);
	glVertex3f(4.0 - level3x, 7.0 + level3y, 0);  //Left top

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.0 + level3x, 7.0 + level3y, 0); //right top

	glEnd();
	

	///////////////////////////////////// front of buliding

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(4.0 - level1x, 1.0 + level1y, 0); //Left bottom

	glTexCoord2f(1.0f, 0);
	glVertex3f(6.0 + level1x, 1.0 + level1y, 0); //Right bottom

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(7.0 + level2x, 5.0, 0); //Right top

	glTexCoord2f(0, 1.0f);
	glVertex3f(3.0 - level2x, 5.0, 0); //Left top
	glEnd();


}

void createWindow(GLuint selectedTexture) {
	glBindTexture(GL_TEXTURE_2D, selectedTexture);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(0, 0);
	glVertex2f(3.8, 3.5 );

	glTexCoord2f(0, 1.0f);
	glVertex2f(3.6, 4.5 );

	glTexCoord2f(0.5f, 0.0f);
	glVertex2f(5.0, 3.5 );

	glTexCoord2f(0.5f, 1.0f);
	glVertex2f(5.0, 4.5 );

	glTexCoord2f(1.0f, 0);
	glVertex2f(6.0, 3.5 );

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(6.2, 4.5 );

	glEnd();
	
}


void createCircle(GLuint selectedTexture) {

	glBindTexture(GL_TEXTURE_2D, selectedTexture);
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
	
}

void createStar(void) {

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1, 1, 0);
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

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

}

void createFlag(void) {

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(2, 5);
	glColor3f(0.5, 0.5, 0);
	glVertex2f(2, 9);
	glVertex2f(4, 7);
	glEnd();
	
	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(2, 5);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(2, 2);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

}

void createRoof(void) {

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(5, 9);
	glColor3f(0.8, 1, 0.8);
	glVertex2f(2, 7);
	glVertex2f(2, 5);
	glColor3f(0,0.2,0.9);
	glVertex2f(8, 5);
	glColor3f(0.8, 1, 0.8);
	glVertex2f(8, 7);
	glEnd();
	

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);


}

void drawCar(GLuint selectedTexture, float posX, float posY, float angle) {

	glBindTexture(GL_TEXTURE_2D, selectedTexture);
	glTranslatef(posX, posY, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-posX, -posY, 0.0);
	glTranslatef(posX, posY, 0.0);

	initOrtho(-15.0, 5.0, -16.0, 4.0);
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

	initOrtho(-15, 35, -20, 35);
	createWindow(texture[1]);
	createBuilidng(texture[0],0, 0, 0, 0, 0);

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
	createBuilidng(texture[0], 3, 0, 3, 3, 0);


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

void drawLineMap(void) {

	//glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);

	glPushMatrix();
	drawCar(NULL, 0, 0, 0);

	/*first apart*/
	initOrtho(-15, 35, -20, 35);
	createWindow(NULL);
	createBuilidng(NULL, 0, 0, 0, 0, 0);

	/* second apple office */

	initOrtho(-23.5, 35, -50, 5);
	createCircle(NULL);
	initOrtho(-15, 35, -50, 10);
	createBuilidng(NULL, 0, 0, 0, 0, 0);

	/* third building with star */

	initOrtho(-100, 27, -120, 65);
	createStar();


	initOrtho(-50, 20, -30, 20);
	createWindow(NULL);
	createBuilidng(NULL, 2, 0, 1.8, 2, 0);


	/* fourth school */
	initOrtho(2, 50, -20, 35);
	createWindow(NULL);
	initOrtho(-2, 50, -20, 35);
	createWindow(NULL);

	initOrtho(0, 50, -20, 35);
	createBuilidng(NULL, 3, 0, 3, 3, 0);

	initOrtho(-2, 50, -28, 35);
	createFlag();


	/* fifth restroom */
	initOrtho(0, 60, -50, 10);
	createRoof();
	createWindow(NULL);
	createBuilidng(NULL, 2, 0, 1, 2, 0);


	/*background map*/

	initOrtho(0, 10, 0, 10);
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


	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	//glDisable(GL_STENCIL_TEST);
}

void drawMapWithDisplayList(void) {

	glPushMatrix();
	/*first building*/
	initOrtho(-15, 35, -20, 35);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glCallList(MyListId[5]);
	createBuilidng(texture[0], 0, 0, 0, 0, 0);

	/*second building*/
	initOrtho(-23.5, 35, -50, 5);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glCallList(MyListId[7]);
	initOrtho(-15, 35, -50, 10);
	createBuilidng(texture[2], 0, 0, 0, 0, 0);

	/* third building with star */

	initOrtho(-100, 27, -120, 65);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glCallList(MyListId[1]);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	initOrtho(-50, 20, -30, 20);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glCallList(MyListId[5]);
	createBuilidng(texture[0], 2, 0, 1.8, 2, 0);


	/* fourth school */
	initOrtho(2, 50, -20, 35);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glCallList(MyListId[5]);
	initOrtho(-2, 50, -20, 35);
	glCallList(MyListId[5]);

	initOrtho(0, 50, -20, 35);
	createBuilidng(texture[0], 3, 0, 3, 3, 0);

	initOrtho(-2, 50, -28, 35);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glCallList(MyListId[2]);
	glCallList(MyListId[3]);



	/* fifth restroom */
	initOrtho(0, 60, -50, 10);
	glCallList(MyListId[4]);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glCallList(MyListId[5]);
	createBuilidng(texture[0], 2, 0, 1, 2, 0);


	/*background map*/

	initOrtho(0, 10, 0, 10);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glCallList(MyListId[0]);
	glPopMatrix();

}

void drawLineWithDisplayList(void) {

	glEnable(GL_LINE_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();
	initOrtho(-15.0, 5.0, -16.0, 4.0); //draw car
	glCallList(MyListId[6]);

	initOrtho(-15, 35, -20, 35);
	glCallList(MyListId[5]);
	createBuilidng(NULL, 0, 0, 0, 0, 0);

	initOrtho(-23.5, 35, -50, 5);
	glCallList(MyListId[7]);
	initOrtho(-15, 35, -50, 10);
	createBuilidng(NULL, 0, 0, 0, 0, 0);

	/* third building with star */

	initOrtho(-100, 27, -120, 65);
	glCallList(MyListId[1]);


	initOrtho(-50, 20, -30, 20);
	glCallList(MyListId[5]);
	createBuilidng(NULL, 2, 0, 1.8, 2, 0);


	/* fourth school */
	initOrtho(2, 50, -20, 35);
	glCallList(MyListId[5]);
	initOrtho(-2, 50, -20, 35);
	glCallList(MyListId[5]);

	initOrtho(0, 50, -20, 35);
	createBuilidng(NULL, 3, 0, 3, 3, 0);

	initOrtho(-2, 50, -28, 35);
	glCallList(MyListId[2]);
	glCallList(MyListId[3]);


	/* fifth restroom */
	initOrtho(0, 60, -50, 10);
	glCallList(MyListId[4]);
	glCallList(MyListId[5]);
	createBuilidng(NULL, 2, 0, 1, 2, 0);


	/*background map*/

	initOrtho(0, 10, 0, 10);
	glCallList(MyListId[0]);


	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LINE_SMOOTH);
}
