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
#include <System/UISystem.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GraphicEngine/imgui.h>
#include <GraphicEngine/imgui_impl_glfw.h>
#include <GraphicEngine/imgui_impl_opengl3.h>
#include <GraphicEngine/imgui_Custom.hpp>

#include <System/AGE_EngineCore.hpp>
#include <System/GraphicSystem.hpp>
//#include <AGE_FileBrowser.hpp>
extern AGE_EngineCore* _AGE_EngineCore;

bool UISystem::Inited()
{
	
#ifdef  __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";

#endif //__APPLE__
	//UI ªì©l¤Æ-------------
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); //(void)io;
	ImFontConfig font_config; font_config.OversampleH = 1; font_config.OversampleV = 1; font_config.PixelSnapH = 1;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//	io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 15.0f, &font_config, io.Fonts->GetGlyphRangesChineseFull());
	//	io.Fonts->Build();

		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
	ImGui::StyleColorsCustom();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(_AGE_EngineCore->_GraphicSystem->MainGLFWwindow, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	return true;
}
void Updated_WindowEvent();
bool UISystem::MainLoop()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	Updated_WindowEvent();


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	glfwSwapBuffers(_AGE_EngineCore->_GraphicSystem->MainGLFWwindow);
	glfwPollEvents();
	return true;
}

void Updated_WindowEvent()
{
	static bool Open_FileBrowser = true;
	if (!ImGui::Begin("FileBrowser", &Open_FileBrowser))	// Early out if the window is collapsed, as an optimization.
	{
		ImGui::End();
		return;
	}
	//AGE_FileBrowser::ImGUIListTheBrowser();
	ImGui::End();


}