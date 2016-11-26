#include <GLFW/glfw3.h>

int main(void)
{
	GLFWwindow *window;

	//initial the GLFW
	if (!glfwInit())
	{
		return -1;
	}

	//create a window node and it's OpenGL Context
	window = glfwCreateWindow(640, 480, "OpenGL project 1", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//make the window's context current

	//loop until the user close the window
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//render the openGL here

		//sweap the OpenGL here

		//Sweap front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}
}