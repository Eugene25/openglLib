#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

/*create brick texture*/
int textureNum = 5;
GLuint texture[5];

GLBatch				topBlock;
GLBatch				frontBlock;
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;

int w, h;


void init(void) {

	GLbyte *pBytes;
	GLint nWidth, nHeight, nComponents;
	GLenum format;

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0,10, 0,10);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);*/

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

	glGenTextures(textureNum, texture);
	//glBindTexture(GL_TEXTURE_2D, texture);


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

}

void initOrtho(int x, int y, int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(x, y, width, height);
	glMatrixMode(GL_MODELVIEW);
}

void createWindow(void) {
	glBindTexture(GL_TEXTURE_2D, texture[1]);
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
	glFlush();
}

void createBuilidng(GLuint selectedTexture, int level1x, int level1y, int level2x, int level3x, int level3y ) {

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
	glFlush();

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
	glFlush();

}

void createCircle(void) {
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	double rad = 2;
	for (int i = 0; i<360; i++)
	{
		double angle = i*3.141592 / 180;
		double x = rad*cos(angle);
		double y = rad*sin(angle);
		glTexCoord2f(x, y);
		glVertex2f(x, y);
	}
	glEnd();
	glFinish();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glViewport(0, 0, w, h);

	/* first apart building */

	initOrtho(-15, 35, -20, 35);
	createWindow();
	createBuilidng(texture[0],0,0,0,0,0);

	/* second apple office */

	initOrtho(-23.5, 35, -50, 5);
	createCircle();
	initOrtho(-15, 35, -50, 10);
	createBuilidng(texture[2],0, 0, 0, 0, 0);

	/* third restroom */

	initOrtho(-50,20, -30, 20);
	createBuilidng(texture[0], 2, 0, 1.8, 2, 0);

	glBegin(GL_LINE_LOOP);
	glVertex2f( 0,  2 );
	glVertex2f( 1,  1 );
	glVertex2f( 2,  0.5 );
	glVertex2f( 1,  0 );
	glVertex2f( 2, - 1 );
	glVertex2f( 0,  0 );
	glVertex2f( 2, - 1 );
	glVertex2f( 1, 0  );
	glVertex2f( 2, 0.5 );
	glVertex2f( 1,  1 );
	glEnd();
	glFlush();

	/* fourth restroom */

	/* fifth restroom */


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
	glFlush();


	glDisable(GL_TEXTURE_2D);

}




int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Making a building");

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	init();
	glutDisplayFunc(display);


	glutMainLoop();
	return 0;
}
