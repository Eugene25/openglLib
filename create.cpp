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
GLuint textures[3];

GLBatch				topBlock;
GLBatch				frontBlock;
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;

GLfloat vLightPos[] = { -8.0f, 20.0f, 100.0f, 1.0f };


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,100.0, 0.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);

}

void display(void) {



	///////////////////////////////////// front of buliding
	glColor3f(1.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(40.0, 10.0); //Left bottom

	glTexCoord2f(1.0f, 0);
	glVertex2f(60.0, 10.0); //Right bottom

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(70.0, 50.0); //Right top

	glTexCoord2f(0, 1.0f);
	glVertex2f(30.0, 50.0); //Left top
	glEnd();
	glFlush();
	
	///////////////////////////////////// window
	glColor3f(0.5, 0.0, 1.0);

	glBegin(GL_QUAD_STRIP);
	glVertex2f(40.0, 35.0); 
	glVertex2f(38.0, 45.0); 
	glVertex2f(50.0, 35.0); 
	glVertex2f(50.0, 45.0);
	glVertex2f(60.0, 35.0);
	glVertex2f(62.0, 45.0);
	glEnd();
	glFlush();


	/////////////////////////////////////top of building
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_TRIANGLE_STRIP);

	glTexCoord2f(1.0f, 0);
	glVertex2f(30.0, 50.0 ); //Left bottom

	glTexCoord2f(0, 0);
	glVertex2f(40.0, 70.0); //Left top


	glVertex2f(50.0, 50.0);

	glTexCoord2f(0, 1.0f);
	glVertex2f(60.0, 70.0); //Right top

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(70.0, 50.0 ); //Right bottom
	glEnd();
	glFlush();

}

void SetupRC() {

	GLbyte *pBytes;
	GLint nWidth, nHeight, nComponents;
	GLenum format;

	shaderManager.InitializeStockShaders();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Make front
	frontBlock.Begin(GL_QUADS, 4, 1);

	frontBlock.MultiTexCoord2f(0, 0.0f, 0.0f);
	frontBlock.Vertex3f(40, 10, 0);

	frontBlock.MultiTexCoord2f(0, 1.0f, 0);
	frontBlock.Vertex3f(60.0, 10.0, 0);

	frontBlock.MultiTexCoord2f(0, 1.0f, 1.0f);
	frontBlock.Vertex3f(70.0, 50.0, 0);

	frontBlock.MultiTexCoord2f(0, 0.0f, 1.0f);
	frontBlock.Vertex3f(30.0, 50.0, 0);
	frontBlock.End();

	// Make top
	topBlock.Begin(GL_TRIANGLE_FAN, 4, 1);
	
	topBlock.MultiTexCoord2f(0, 1.0f, 0);
	topBlock.Vertex3f(30.0, 50.0, 0);

	topBlock.MultiTexCoord2f(0, 0, 0);
	topBlock.Vertex3f(40.0, 70.0, 0);

	topBlock.MultiTexCoord2f(0, 0, 1.0f);
	topBlock.Vertex3f(60.0, 70.0, 0);

	topBlock.MultiTexCoord2f(0, 1.0f, 1.0f);
	topBlock.Vertex3f(70.0, 50.0, 0);
	topBlock.End();



	glGenTextures(2, textures);

	pBytes = gltReadTGABits("birck.jpg", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	pBytes = gltReadTGABits("birck.jpg", &nWidth, &nHeight, &nComponents, &format);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
		format, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

}

void RenderScene(void)
{

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, modelViewMatrix.GetMatrix(),
		projectionMatrix.GetMatrix(), vLightPos, vWhite, 0);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	topBlock.Draw();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	frontBlock.Draw();


}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Making a building");
	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	init();
	glutDisplayFunc(RenderScene);

	SetupRC();

	glutMainLoop();
	return 0;
}