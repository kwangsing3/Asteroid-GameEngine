/**
	Copyright (c) 2020 kwangsing3 (kwangsing3@gmail.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#define AGE_GRAPGICAPI_OPENGL

#include <System/GraphicSystem.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern unsigned int Window_Width, Window_Height;

bool GraphicSystem::Inited()
{
	
#ifdef AGE_GRAPGICAPI_OPENGL

	if (!glfwInit()) {AGE_PRINTCONSLE("GLFW Init failed"); return false;}

#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	glfwWindowHint(GLFW_SAMPLES, 4);

#else AGE_GRAPGICAPI_VULKAN
	
#endif // AGE_GRAPGICAPI_OPENGL

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	Window_Width = mode->width;
	Window_Height = mode->height;
	MainGLFWwindow = glfwCreateWindow(Window_Width, Window_Height, "Asteroid-GameEngine", NULL, NULL);
	if (MainGLFWwindow == NULL)
	{
		AGE_PRINTCONSLE("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMaximizeWindow(MainGLFWwindow);
	//glfwHideWindow(MainGLFWwindow);
	//glfwSetWindowMonitor(MainGLFWwindow, monitor, 0, 0, _Width, _Height, mode->refreshRate);
	glfwMakeContextCurrent(MainGLFWwindow);
	glfwSetFramebufferSizeCallback(MainGLFWwindow, (GLFWframebuffersizefun)framebuffer_size_callback);
	glfwSetCursorPosCallback(MainGLFWwindow, (GLFWcursorposfun)mouse_move_callback);
	glfwSetScrollCallback(MainGLFWwindow, (GLFWscrollfun)scroll_callback);
	glfwSetMouseButtonCallback(MainGLFWwindow, (GLFWmousebuttonfun)mouse_button_callback);
	glfwSetKeyCallback(MainGLFWwindow, key_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(MainGLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { AGE_PRINTCONSLE("Failed to initialize GLAD");  return false;}



	// -----------------------------configure global opengl state
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_MULTISAMPLE);
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_FRAMEBUFFER_SRGB); //gamma校正
	// build and compile our shader zprogram
	return true;
}

bool GraphicSystem::MainLoop()
{
	if (glfwWindowShouldClose(MainGLFWwindow))return false;



	return true;
}






void GraphicSystem::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void GraphicSystem::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{


}
void GraphicSystem::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

}
void GraphicSystem::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
}
// 開發調適用
void GraphicSystem::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}