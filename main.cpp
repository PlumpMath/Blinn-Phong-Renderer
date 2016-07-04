# include <iostream>

#include <sstream>
#include <fstream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <TOBJ/tiny_obj_loader.h>


GLuint loadAndCompileShader(GLenum shaderType, const std::string& path)
{
	std::ifstream f;
	f.open(path.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		throw std::runtime_error(std::string("Can't open shader file ") + path);
	}

	std::stringstream buffer;
	buffer << f.rdbuf();

	GLuint shader = glCreateShader(shaderType);
	if (!shader)
	{
		throw std::runtime_error(std::string("Can't create shader for file ") + path);
	}

	const std::string& bufferAsString = buffer.str();
	const GLchar* shaderCode = bufferAsString.c_str();
	const GLchar* codeArray[] = { shaderCode };
	GLint size = strlen(shaderCode);
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		std::cerr << "Compilation error in shader file " << path << std::endl;
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char *log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			std::cerr << "Shader log: " << std::endl;
			std::cerr << log << std::endl;
			delete[] log;
		}
		throw std::runtime_error(
			std::string("Can't compile the shader defined in file ") + path);
	}
	return shader;
}


GLuint createVertexFragmentProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{

	GLuint vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertex_shader_path);
	GLuint fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragment_shader_path);

	GLuint program = glCreateProgram();
	if (!program) {
		throw std::runtime_error("Can't create GLSL program.");
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		std::cerr << "Linking error in shader program!" << std::endl;
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char *log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(program, logLen, &written, log);
			std::cerr << "Shader log: " << std::endl;
			std::cerr << log << std::endl;
			delete[] log;
		}
		throw std::runtime_error("Can't link shader program.");
	}
	return program;
}


void GLFW_key_callback(GLFWwindow* window, int keyCode, int scanCode, int action, int modifiers)
{
	switch (keyCode)
	{
	case GLFW_KEY_P:
		if (action == GLFW_PRESS && modifiers == 0x0000)
		{
			std::cout << "Pressed a lower-case p, scanCode = " << scanCode << std::endl;
			//          exportPNGImage(window, std::string("triangles"));
		}
		break;
	case GLFW_KEY_Q:
		if (action == GLFW_PRESS && modifiers == 0x0000) {
			std::cout << "Pressed a lower-case q, scanCode = " << scanCode << std::endl;
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
	return;
}


void GLFW_error_callback(int errorCode, const char* msg)
{
	throw std::runtime_error(msg);
}
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