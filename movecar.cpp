
#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

using namespace std;
/* global variable */

GLfloat box[2][2];
GLsizei window[2];

float theta = 0.0, angle = 0.0, posX = 0, posY = 0, posZ = 0;

/*create brick texture*/
int textureNum = 7;
GLuint texture[7];

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

	glDisable(GL_DEPTH_TEST);
}

/*
* display()
* This routine gets called each time the window is redrawn.
*/
void display()
{
	/* clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	/* save the state of the ModelView matrix by pushing (copying) */
	glPushMatrix();

	/* rotate the box by theta degrees -- about z-axis */
	glTranslatef(posX, posY, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-posX, -posY, 0.0);
	glTranslatef(posX, posY, 0.0);

	std::cout <<"posX = " << posX << ", posY = " << posY << "\n";

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex2f(-0.5, -0.5 );
	glTexCoord2f(0, 1.0f);
	glVertex2f(0.5, -0.5 );
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.5 , 0.5 );
	glTexCoord2f(1.0f, 0);
	glVertex2f(-0.5 , 0.5);
	glEnd();



	/* draw a filled polygon 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex2f(-0.5 + posX, -0.5 + posY);
	glTexCoord2f(0, 1.0f);
	glVertex2f(0.5 + posX, -0.5 + posY);
	glTexCoord2f(1.0f , 1.0f);
	glVertex2f(0.5 + posX, 0.5 + posY);
	glTexCoord2f(1.0f , 0 );
	glVertex2f(-0.5 + posX, 0.5 + posY);
	glEnd();*/



	/* eliminate the rotation from above from the ModelView matrix */
	/* for fun -- try moving this before the line drawing */
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	/* Ready to draw now! forces buffered OGL commands to execute */
	/* glFlush  is replaced by glSwapBuffers when we used doublebuffering */
	//	glFlush(); 
	glutSwapBuffers();


}



/*
*
* myreshape()
* This routine is called upon initial window creation and in the event
* that the user changes the size or shape of the window.
*
* Notice that the viewing functions have been moved here.This is to
* take into account changes in the window size.
*/


/* init_graphics()
* Initialize graphics states -- called before entering event loop
*/
void init_graphics()
{
	/* set background clear color to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	/* later there will be more here .... */
}

float move_unit = 0.1f;

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


/* main()
* The main program
*/
int main(int argc, char** argv)
{
	/* create a window, position it, and name it */
	glutInit(&argc, argv);
	/* if you use single buffer, then use glflush in display() */
	/* if you use double buffer, then use glswapbuffers in display() */
	//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);


	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("basic interaction and animation demo");

	setTexture();
	/* create a callback routine for (re-)display */

	glutDisplayFunc(display);

	/* init data and some states */
	init_graphics();
	glutSpecialFunc(keyboardown);


	/* entering the event loop */
	glutMainLoop();

	/* code here will not be executed */
}
