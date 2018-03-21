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
GLuint texture[2];

GLBatch				topBlock;
GLBatch				frontBlock;
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;

GLfloat vLightPos[] = { -8.0f, 20.0f, 100.0f, 1.0f };


void init(void) {

	GLbyte *pBytes;
	GLint nWidth, nHeight, nComponents;
	GLenum format;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

	glGenTextures(2, texture);
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


}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_REPLACE);


	///////////////////////////////////// window
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

	/////////////////////////////////////top of building
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0, 0);
	glVertex3f(3.0, 5.0, 0); //Left bottom

	glTexCoord2f(0, 1.0f);
	glVertex3f(4.0, 7.0, 0); //Left top

	glTexCoord2f(1.0f, 0);
	glVertex3f(7.0, 5.0, 0);

	glTexCoord2f(1.0f, 0);
	glVertex3f(7.0, 5.0, 0);

	glTexCoord2f(0, 1.0f);
	glVertex3f(4.0, 7.0, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(6.0, 7.0, 0);

	glEnd();
	glFlush();

	///////////////////////////////////// front of buliding

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(4.0, 1.0, 0); //Left bottom

	glTexCoord2f(1.0f, 0);
	glVertex3f(6.0, 1.0, 0); //Right bottom

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(7.0, 5.0, 0); //Right top

	glTexCoord2f(0, 1.0f);
	glVertex3f(3.0, 5.0, 0); //Left top
	glEnd();
	glFlush();



	glDisable(GL_TEXTURE_2D);

}




int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Making a building");

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
