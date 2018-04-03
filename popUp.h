#pragma once

#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include "createCity.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

static int window;
static int menu_id;
static int submenu_id[3];
static int value = 0;


class popUp
{
public:
	popUp();
	~popUp();

	void createMenu(void);
	void menu(int num);

};

void menu(int num){
	if (num == 0){
		glutDestroyWindow(window);
		exit(0);
	}
	else{
		value = num;
	}
	glutPostRedisplay();
}

void createMenuCG(void){
	submenu_id[0] = glutCreateMenu(menu);
	glutAddMenuEntry("Slow", 2);
	glutAddMenuEntry("Medium", 3);
	glutAddMenuEntry("Fast", 4);

	submenu_id[1] = glutCreateMenu(menu);
	glutAddMenuEntry("Filled", 5);
	glutAddMenuEntry("Outline", 6);

	submenu_id[2] = glutCreateMenu(menu);
	glutAddMenuEntry("ON", 7);
	glutAddMenuEntry("OFF", 8);

	//main pop up menu
	menu_id = glutCreateMenu(menu);
	glutAddSubMenu("Display List", submenu_id[2]);
	glutAddSubMenu("Polygons", submenu_id[1]);
	glutAddMenuEntry("Restart", 1);
	glutAddSubMenu("Speed", submenu_id[0]);
	glutAddMenuEntry("Quit", 0);     
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

