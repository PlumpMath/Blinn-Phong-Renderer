# include <iostream>

#include <sstream>
#include <fstream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <TOBJ/tiny_obj_loader.h>

// User includes
# include "utils/Callbacks.h"
# include "utils/Shader.h"
# include "utils/Helper.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

GLuint program;
GLuint modelVAO;
GLFWwindow* window;


void update(const double &difference_time)
{

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*Bind the vertex array*/

	/*Bind shader*/

	/*Setup rendering context*/

}

/* Init GLFW and window*/
void init_stage()
{

	// GLFW init
	glfwSetErrorCallback(GLFW_error_callback);
	if (!glfwInit())
		Helper::log_error("Failed to init GLFW\n");
		
	/* Now, let's give GLFW hints about the window we need */
	/* We want OpenGL version at least 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	/* We will also request a bleeding-edge core profile*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* IMPORTANT: Tell GLFW to give us a framebuffer which can do sRGB */
	glfwWindowHint(GLFW_SRGB_CAPABLE, TRUE);

	
	// Create GLFW window 
	window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "Color management demo", NULL, NULL);
	if (window == nullptr)
	{
		glfwTerminate();
		Helper::log_error("Failed to create GLFW windonw\n");
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, GLFW_key_callback); /*Setup key call back function*/


	// gl3w init, load opengl
	if (gl3wInit()) 
		Helper::log_error("failed to initialize OpenGL\n");
	if (!gl3wIsSupported(4, 3)) 
		Helper::log_error("OpenGL 4.3 not supported\n");
}
void setup_stage()
{

}
void main_loop()
{
	double previous_time = glfwGetTime();
	double current_time, difference_time;
	while (!glfwWindowShouldClose(window))
	{
		current_time = glfwGetTime();
		difference_time = current_time - previous_time;
		previous_time = current_time;
		update(difference_time);
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void cleanup()
{
	glfwTerminate();
	glDeleteProgram(program);
}

int main()
{
	init_stage();
	setup_stage();
	main_loop();
	cleanup();
	return 0;
}