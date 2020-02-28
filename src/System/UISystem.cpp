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
#include <GraphicEngine/imgui.h>

#include "RuntimeObjectSystem/IObject.h"
#include "RuntimeObjectSystem/SystemTable.h"
#include "RuntimeObjectSystem/ISimpleSerializer.h"
#include "RuntimeObjectSystem/IRuntimeObjectSystem.h"
#include "RuntimeObjectSystem/IObjectFactorySystem.h"

#include "RuntimeObjectSystem/RuntimeSourceDependency.h"
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../GraphicEngine/imgui", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../GraphicEngine/imgui_widgets", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../GraphicEngine/imgui_draw", ".cpp");
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE("../../GraphicEngine/imgui_demo", ".cpp");


// add imgui source dependencies
// an alternative is to put imgui into a library and use RuntimeLinkLibrary

enum InterfaceIDEnumConsoleExample
{
	IID_IRCCPP_MAIN_LOOP = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

	IID_ENDInterfaceIDEnumConsoleExample
};
struct UISystem : IUISystem, TInterface<IID_IRCCPP_MAIN_LOOP, IObject>
{

	bool Inited()
	{
		return true;
	}


	void MainLoop() override
	{
		ImGui::SetCurrentContext(PerModuleInterface::g_pSystemTable->pImContext);     //這邊是NULL   有問題------------------

		ImGui::SetNextWindowPos(ImVec2(50, 400), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::Begin("RCCppMainLoop Window");
		ImGui::Text("You can change Window's code at runtime! ");
		ImGui::Image(0,ImVec2(200,200));
		ImGui::End();
	}
	UISystem()
	{
		PerModuleInterface::g_pSystemTable->pRCCppMainLoopI = this;
	}
};
REGISTERSINGLETON(UISystem, true);