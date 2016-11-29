#ifndef CGL_H
#define CGL_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include "util.h"
class CGL
{
    public:
        CGL();
        CGL(int _width, int _height);
        virtual ~CGL();
        bool initGL();
        bool resizeGL(int width,int height);
        bool renderGL();
    protected:
    private:
        int width;
        int height;
        // Read our .obj file
        vector<glm::vec3> vertices;
        vector<glm::vec2> uvs;
        vector<glm::vec3> normals; // Won't be used at the moment.
};

#endif // CGL_H
