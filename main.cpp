# include <iostream>

#include <sstream>
#include <fstream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <TOBJ/tiny_obj_loader.h>

// User includes
# include "utils/Callbacks.h"
# include "utils/Shader.h"
GLuint program;


int main()
{
	// Setup window
	glfwSetErrorCallback(GLFW_error_callback);
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


	// GLFW window init
	GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW windonw" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// gl3w init
	gl3wInit();


	// Viewport init
	//Instead of setting a width and height of 800 and 600 respectively 
	//we take the viewport dimensions from GLFW such that it also works on high DPI screens (like Apple's retina displays).
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	program = createVertexFragmentProgram("shaders/vshader.vert", "shaders/fshader.frag");

	// callback functions
	glfwSetKeyCallback(window, GLFW_key_callback);

	// glfwWindowShouldClose �� �� �������� close instruction�� �Դ��� �˻��Ѵ�.
	// glfwpollevents �� �ƹ������� �̺�Ʈ�� Ʈ���ŵǸ� (Ű����, ���콺 ��) corresponding callback function�� ���Ѵ�.
	// gflwswapbuffer�� �����츶�� ������ �ִ� front�� backbuffer�� �����Ѵ�.
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// Back buffer�� �׸��� ����
		// Rendering command ȣ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window); // front�� back buffer ����(�׷����� �̹��� ���÷��� ����)
	}

	// Cleanup
	glfwTerminate();
	glDeleteProgram(program);
	return 0;
}