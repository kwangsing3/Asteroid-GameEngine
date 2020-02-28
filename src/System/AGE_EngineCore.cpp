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
#include <System/AGE_EngineCore.hpp>
#include <System/InputSystem.hpp>
#include <System/TimeSystem.hpp>
#include <System/AudioSystem.hpp>
#include <System/ScriptEventSystem.hpp>
#include <System/World.hpp>
#include <System/GraphicSystem.hpp>
#include <System/UISystem.hpp>
#include <filesystem>

#include <RuntimeObjectSystem/RuntimeObjectSystem.h>
#include <RuntimeObjectSystem/SystemTable.h>

#include "StdioLogSystem.h"



#include <GraphicEngine/imgui.h>
#include <GraphicEngine/imgui_impl_glfw.h>
#include <GraphicEngine/imgui_impl_opengl3.h>
#include <GraphicEngine/imgui_Custom.hpp>

 InputSystem*                    AGE_EngineCore::_InputSystem=0;
 TimeSystem*                     AGE_EngineCore::_TimeSystem=0;
 static SystemTable              g_SystemTable;

 unsigned int Window_Width = 1920,Window_Height = 1080;
 bool AGE_EngineCore::RCCppInit()
 {

	 g_pRuntimeObjectSystem = new RuntimeObjectSystem;
	 if (!g_pRuntimeObjectSystem->Initialise(m_pCompilerLogger, &g_SystemTable))
	 {
		 delete g_pRuntimeObjectSystem;
		 g_pRuntimeObjectSystem = NULL;
		 return false;
	 }

	 // ensure include directories are set - use location of this file as starting point
	 FileSystemUtils::Path basePath = g_pRuntimeObjectSystem->FindFile(__FILE__).ParentPath();
	 FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
	 g_pRuntimeObjectSystem->AddIncludeDir(imguiIncludeDir.c_str());


	 return true;
 }
 void AGE_EngineCore::RCCppUpdate()
 {
	 //check status of any compile
	 if (g_pRuntimeObjectSystem->GetIsCompiledComplete())
	 {
		 // load module when compile complete
		 g_pRuntimeObjectSystem->LoadCompiledModule();
	 }

	 if (!g_pRuntimeObjectSystem->GetIsCompiling())
	 {
		 float deltaTime = 1.0f / ImGui::GetIO().Framerate;
		 g_pRuntimeObjectSystem->GetFileChangeNotifier()->Update(deltaTime);
	 }
 }

bool AGE_EngineCore::Inited()
{
	// Their constructer are all null on default
	 _GraphicSystem = new GraphicSystem();
	 _InputSystem = new InputSystem();
	 _TimeSystem = new TimeSystem();      //static for Application and non-static belongs to world, would related to main TimeSystem by its time coefficient ( delta scale ).
	 _AudioSystem = new AudioSystem();
	 _ScriptEventSystem = new ScriptEventSystem();
	 _MainEditorWorld = new World();
	 //_UISystem = new UISystem();
	 m_pCompilerLogger = new StdioLogSystem();

	 //Initialise the RuntimeObjectSystem
	 RCCppInit();
	 g_pRuntimeObjectSystem->AddIncludeDir(std::filesystem::absolute("../../../../src").string().c_str());
	 
	 _GraphicSystem->Inited();  //Always let Graphic Initlized first
	 _InputSystem->Inited();
	 _TimeSystem->Inited();
	 _AudioSystem->Inited();
	 _ScriptEventSystem->Inited();
	 _MainEditorWorld->Inited();     // Editor world
	
	 //Initialise ImGUI
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
		 ImGui_ImplGlfw_InitForOpenGL(_GraphicSystem->MainGLFWwindow, true);
		 ImGui_ImplOpenGL3_Init(glsl_version);

		
	 }



	 g_SystemTable.pImContext = ImGui::GetCurrentContext();
	 return true;

}
bool AGE_EngineCore::Update()
{



	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	RCCppUpdate();
	g_SystemTable.pRCCppMainLoopI->MainLoop();


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	glfwSwapBuffers(_GraphicSystem->MainGLFWwindow);
	glfwPollEvents();







	return
		/*Loop order*/
		//1.
		_InputSystem->Update() &&
		//2.
		_TimeSystem->Update() &&
		//3.
		_AudioSystem->Update() &&
		//4.
		_ScriptEventSystem->Update() &&
		//5.
		_MainEditorWorld->Update() &&       //Physics runs here
		//6.
		_GraphicSystem->Update();//&&
		//7.
		
}

void AGE_EngineCore::OnConstructorsAdded()
{
	// This could have resulted in a change of object pointer, so release old and get new one.



}
