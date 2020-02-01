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

 InputSystem* AGE_EngineCore::_InputSystem=0;
 TimeSystem* AGE_EngineCore::_TimeSystem=0;

 unsigned int Window_Width = 1920,Window_Height = 1080;

bool AGE_EngineCore::Inited()
{

	
	// Their constructer are all null
	 _GraphicSystem = new GraphicSystem();
	 _InputSystem = new InputSystem();
	 _TimeSystem = new TimeSystem();      //static for Application and non-static belongs to world, would related to main TimeSystem by its time coefficient.
	 _AudioSystem = new AudioSystem();
	 _ScriptEventSystem = new ScriptEventSystem();
	 _MainEditorWorld = new World();
	 _UISystem = new UISystem();
	 
	 return 
		 _GraphicSystem->Inited() &&  //Always let Graphic Initlized first
		 _InputSystem->Inited() &&
		 _TimeSystem->Inited() &&
		 _AudioSystem->Inited() &&
		 _ScriptEventSystem->Inited() &&
		 _MainEditorWorld->Inited() &&      // Editor world
		 _UISystem->Inited();
}
bool AGE_EngineCore::MainLoop()
{
	return
	/*Loop order*/
	//1.
		_InputSystem->MainLoop()&&
	//2.
		_TimeSystem->MainLoop()&&
	//3.
		_AudioSystem->MainLoop()&&
	//4.
		_ScriptEventSystem->MainLoop()&&
	//5.
		_MainEditorWorld->MainLoop()&&       //Physics runs here
	//6.
		_GraphicSystem->MainLoop()&&
	//7.
		_UISystem->MainLoop();
}
