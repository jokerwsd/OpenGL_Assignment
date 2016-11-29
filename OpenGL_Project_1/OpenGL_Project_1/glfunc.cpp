#include "glfunc.h"



glfunc::glfunc()
{
}

glfunc::glfunc(int _width, int _height)
{
	this->width = _width;
	this->height = _height;
}


glfunc::~glfunc()
{
}

bool glfunc::initGL()
{

	float ratio = width / height;
	// Our shading model--Gouraud (smooth).
	glShadeModel(GL_SMOOTH);
	// Set the clear color.
	glClearColor(0, 0, 0, 0);
	// Setup our viewport.
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	//Change to the projection matrix and set our viewing volume.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, ratio, 1.0, 100.0);

	GLfloat light_position[] = { 13.0, 13.0, 13.0, 0.0 };
	GLfloat white_light[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	methods methods;
	//Read .obj file and store the infos
	bool res = methods.loadOBJ("monkey.obj", vertices, uvs, normals);
	return(true);
}

bool glfunc::resizeGL(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	//Reset View
	glViewport(0, 0, (GLint)width, (GLint)height);
	//Choose the Matrix mode
	glMatrixMode(GL_PROJECTION);
	//reset projection
	glLoadIdentity();
	//set perspection
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	//choose Matrix mode
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return(true);


}

bool glfunc::renderGL(GLFWwindow* window)
{
	/* These are to calculate our fps */
	static GLint T0 = 0;
	static GLint Frames = 0;
	// Clear the color and depth buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// We don't want to modify the projection matrix. */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef( 0.0f, 0.0f, -6.0f );
	// Move down the z-axis.
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(120, 1.0, 1.0, 0.0);

	int nodesSize = vertices.size();
	int i;
	glBegin(GL_TRIANGLES);
	for (i = 0; i<nodesSize; i++)
	{
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}

	glEnd();

	return(true);
}
