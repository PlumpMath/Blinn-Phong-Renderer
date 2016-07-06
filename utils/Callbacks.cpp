# include "Callbacks.h"

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