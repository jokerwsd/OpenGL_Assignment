#include <iostream>
#include "shader.h"
#include "mesh.h"
#include "window.h"
#include "texture.h"
#include "transform.h"

//#include "glfunc.h"
//#include "methods.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

int main()
{
	window window((int)800, int(800), "Main Window");

	vertex vertices[] = {
		vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0,0)),
		vertex(glm::vec3(0,0.5,0) ,glm::vec2(0.5,1.0)),
		vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0)),};

	mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	shader shader("basicShader");

	texture texture("bricks.jpg");
	transform transform;

	float counter = 0.0f;

	while (!glfwWindowShouldClose(window.MainWindow))
	{
		// Clear the color and depth buffers.
		window.clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetRot().z = counter;
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform);

		

		
		mesh.draw();
		window.swapBuffers();	
		counter += 0.001f;
	}

#if 0
	GLFWwindow* MainWindow;
//	glfunc *gl = new glfunc(SCREEN_WIDTH, SCREEN_HEIGHT);
//	window *new_window = new window(SCREEN_WIDTH, SCREEN_HEIGHT, "Main Window");
//	gl->initGL();
	if (!glfwInit()) return 5555;
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	MainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OBJLoader", NULL, NULL);
	if (!MainWindow)
		{
			glfwTerminate();
			return -44444;
		}
	

	while (!glfwWindowShouldClose(MainWindow))
	{

		// Clear the color and depth buffers.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// We don't want to modify the projection matrix. */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glTranslatef( 0.0f, 0.0f, -6.0f );
		// Move down the z-axis.
		glTranslatef(0.0, 0.0, -5.0);
		glRotatef(120, 1.0, 1.0, 0.0);


		glBegin(GL_TRIANGLES);
		glColor3f(0.1, 0.2, 0.3);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(0, 1, 0);
		glEnd();

		int nodesSize = vertices.size();
		int i;
		for (i = 0; i<nodesSize; i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glfwSwapBuffers(MainWindow);
		glfwPollEvents();
		
	}

	while (true)
	{

		gl->renderGL(MainWindow);
	}
#endif
	return 0;
}

