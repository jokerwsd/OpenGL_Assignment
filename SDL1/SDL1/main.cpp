#include <iostream>
#include "csdl.h"
#include "cgl.h"
#include "SDL.h"

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT =800;
const int SCREEN_BPP = 32;

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
    CGL *gl = new CGL(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Color depth in bits of our window.
	int flags= SDL_OPENGL|SDL_RESIZABLE;
    CSDL *sdl = new CSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,flags, gl);
    sdl->setCaption("Load obj in OpenGL");
    gl->initGL();
    while(true)
    {
        sdl->handleEvent(gl);
        gl->renderGL();
    }
	SDL_Quit();
    cout << "Hello world!" << endl;
    return 0;
}
