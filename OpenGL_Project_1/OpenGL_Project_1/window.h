#ifndef _WINDOW_H
#define _WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& title);

	void clear(float r, float g, float b, float a);
	void swapBuffers();

	virtual ~Window();
	
	GLFWwindow* MainWindow;
//	void windowResize(GLFWwindow* main_window, int width, int height);
		
protected:
private:
//	int width;
//	int height;

};

#endif

