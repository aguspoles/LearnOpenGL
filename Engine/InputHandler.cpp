#include "InputHandler.h"
#include "Game.h"
#include <iostream>
bool firstMouse = true;
float lastX = 400;
float lastY = 300;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

InputHandler* InputHandler::m_instance = nullptr;


InputHandler * InputHandler::Instance()
{
	if (!m_instance)
		m_instance = new InputHandler();
	return m_instance;
}

InputHandler::InputHandler() {
	for (size_t i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
	glfwSetFramebufferSizeCallback(Game::display->window, framebuffer_size_callback);
	glfwSetCursorPosCallback(Game::display->window, mouse_callback);
	glfwSetScrollCallback(Game::display->window, scroll_callback);
}

InputHandler::~InputHandler()
{
}

void InputHandler::CheckInput()
{
}

void InputHandler::Update()
{
	processInput(Game::display->window);
	if (glfwGetKey(Game::display->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_mouseButtonStates[RIGHT_CLICK] = true;
	if (glfwGetKey(Game::display->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_mouseButtonStates[LEFT_CLICK] = true;
	if (glfwGetKey(Game::display->window, GLFW_KEY_LEFT) == GLFW_RELEASE)
		m_mouseButtonStates[LEFT_CLICK] = false;
	if (glfwGetKey(Game::display->window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
		m_mouseButtonStates[RIGHT_CLICK] = false;
}

bool InputHandler::GetMouseButtonState(int buttonNumber) const
{
	return m_mouseButtonStates[buttonNumber];
}

glm::vec2 InputHandler::GetMousePos() const
{
	return m_mousePos;
}

glm::vec2 InputHandler::GetMouseWheel() const
{
	return m_mouseWheel;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Game::camera->ProcessKeyboard(FORWARD, Game::DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Game::camera->ProcessKeyboard(BACKWARD, Game::DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Game::camera->ProcessKeyboard(LEFT, Game::DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Game::camera->ProcessKeyboard(RIGHT, Game::DeltaTime());
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	Game::camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game::camera->ProcessMouseScroll(yoffset);
}

