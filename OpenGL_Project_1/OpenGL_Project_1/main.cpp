#include <iostream>
#include "glfunc.h"
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

int main()
{
	glfunc *gl = new glfunc(SCREEN_WIDTH, SCREEN_HEIGHT);
	gl->initGL();
	while (true)
	{
		gl->renderGL();
	}
	return 0;
}