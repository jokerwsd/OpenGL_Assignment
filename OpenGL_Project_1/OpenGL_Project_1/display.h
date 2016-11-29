#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <string>
//#include "SDL.h"
#include <GL/glew.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class display
{
public:
	display();
	virtual ~display();


	display(int width, int height, const std::string& title);


	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

protected:
private:
	void operator=(const display& display) {}
	display(const display& display) {}
#if 0
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
#endif
};

#endif
