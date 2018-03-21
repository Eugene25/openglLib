
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
///////////////////////////////////////////////////
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;
GLFrame				cameraFrame;
GLFrustum			viewFrustum;
GLBatch				cubeBatch;
GLBatch				floorBatch;
GLBatch				topBlock;
GLBatch				frontBlock;
GLBatch				leftBlock;

GLGeometryTransform	transformPipeline;
M3DMatrix44f		shadowMatrix;
/////////////////////////////////////////////////////


void myinit()
{ 
	glClearColor(1.0, 1.0, 1.0, 1.0);// white background

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}




//how to create two view port
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 500.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	modelViewMatrix.LoadIdentity();
}

void display(void){

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, (1.5*h)/5, w, (3.5*h)/5);
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(0.05, 0, 0.0); //Left bottom
	glVertex3f(0.91, 0, 0.0); //Right bottom
	glVertex3f(0.91, 0.9, 0.0); //Right top
	glVertex3f(0.05, 0.9, 0.0); //Left top
	glEnd();
	glFlush();

	//viewprot for pop up menu;
	glViewport(0, 0, w, (h*1.5) / 5);
	glColor3f(1.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(0.05, 0.1, 0.0);
	glVertex3f(0.91, 0.1, 0.0);
	glVertex3f(0.91, 1, 0.0);
	glVertex3f(0.05, 1, 0.0);
	glEnd();
	glFlush();

}

int main(int argc, char* argv[])
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CG First Project");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	glutDisplayFunc(display);
	//glutReshapeWindow(500, 500);
	myinit();

	glutMainLoop();
	return 0;
}
