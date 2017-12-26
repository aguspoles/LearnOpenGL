#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <string>
#include <GLFW\glfw3.h>

class Display
{
public:
	Display(unsigned int width, unsigned int height, const std::string& title);
	virtual ~Display();

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	GLFWwindow* window;
	unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;

protected:
private:
};

#endif
