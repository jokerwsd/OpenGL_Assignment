#include <GL/glew.h>
#include "window.h"
#include <iostream>

window::window()
{
}


window::window(int width, int height, const std::string& title)
{
	if (!glfwInit()) throw std::runtime_error("glfwInitWindow failed. Can your hardware handle OpenGL 4.2?");
	// open a window with GLFW
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	MainWindow = glfwCreateWindow(width, height, "OBJLoader", NULL, NULL);

	if (!MainWindow)
		throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.2?");
	glfwMakeContextCurrent(MainWindow);

	//glfwSetWindowSizeCallback(MainWindow, handleResize); //callback function of GLFW to handle window resize
	//glfwSetKeyCallback(MainWindow, handleKeypress); //callback function to handle keypress

	if (glewInit() != GLEW_OK)
		throw std::exception("Failed to initialize GLEW\n");
	// run while the window is open

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

window::~window()
{
	glfwDestroyWindow(MainWindow);
	glfwTerminate();
}

void window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::swapBuffers()
{
	glfwSwapBuffers(MainWindow);
	glfwPollEvents();
}

#if 0
void window::windowResize(GLFWwindow* main_window, int width, int height)
{
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
								 //Set the camera perspective
	glLoadIdentity(); //reset the camera
					  //The far z clipping coordinate
}
#endif
