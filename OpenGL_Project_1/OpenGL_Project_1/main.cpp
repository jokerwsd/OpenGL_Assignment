#include <iostream>
#include "shader.h"
#include "mesh.h"
#include "window.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

//#include "glfunc.h"
//#include "methods.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
using namespace cameraControl;

int main()
{
	window window1((int)800, int(800), "Main Window");

#if 0
	vertex vertices[] = {
		vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0,0)),
		vertex(glm::vec3(0,0.5,0) ,glm::vec2(0.5,1.0)),
		vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0)),};
		

	unsigned int indices[] = { 0, 1, 2 };

	mesh mesh1(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
#endif

	mesh mesh2("..//res//monkey.obj");

	shader shader1("..//res//basicShader");

	texture texture1("..//res//fur.jpg");

	camera camera1(glm::vec3(0, 0, -4), 70.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 1000.0f);
	
	trackball* trackball1 = &trackball::GetInstance(&camera1, glm::vec4(0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT));
	trackball1->Init(&window1);

	transform transform1;

	float counter = 0.0f;

	while (!glfwWindowShouldClose(window1.MainWindow))
	{
		// Clear the color and depth buffers.
		window1.clear(0.0f, 0.15f, 0.3f, 1.0f);

		trackball1->Update();

#if 0
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform1.GetPos().x = sinCounter;
		transform1.GetRot().z = cosCounter;
		transform1.GetRot().x = counter * 10;
		transform1.GetRot().y = counter * 10;
		transform1.GetRot().z = counter * 10;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
#endif

		shader1.Bind();
		texture1.Bind(0);
		shader1.Update(transform1, camera1);

		mesh2.draw();
		window1.swapBuffers();	
		counter += 0.0001f;
	}

	return 0;
}

