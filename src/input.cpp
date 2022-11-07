#include "input.h"

bool Qpressed = false;
bool Qsignal = false;
bool Epressed = false;
bool Esignal = false;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (Esignal == true) {
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	Esignal = false;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !Epressed) {
		Epressed = true;
		Esignal = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) != GLFW_PRESS) {
		Epressed = false;
	}

	Qsignal = false;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && !Qpressed) {
		Qpressed = true;
		Qsignal = true;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS) {
		Qpressed = false;
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
		firstMouse = true;
	}
	else {
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			xpos = middle_x;
			ypos = middle_y;

			firstMouse = false;
		}

		float xoffset = xpos - (float)middle_x;
		float yoffset = (float)middle_y - ypos;

		glfwSetCursorPos(window, middle_x, middle_y);

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
