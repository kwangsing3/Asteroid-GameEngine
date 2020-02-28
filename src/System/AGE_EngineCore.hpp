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
#ifndef AGE_ENGINECORE_H
#define AGE_ENGINECORE_H
#include <AGE_Assert.hpp>
#include "RuntimeObjectSystem/IObjectFactorySystem.h"
#include "RuntimeObjectSystem/ObjectInterface.h"


struct IUpdateable;
struct IRuntimeObjectSystem;
class InputSystem;
class TimeSystem;
class AudioSystem;
class ScriptEventSystem;
class GraphicSystem;
class World;
class UISystem;
class IRuntimeObjectSystem;
class AGE_EngineCore : public IObjectFactoryListener
{
public:
	static InputSystem* _InputSystem;
	static TimeSystem* _TimeSystem;
	AudioSystem* _AudioSystem=0;
	ScriptEventSystem* _ScriptEventSystem=0;
	GraphicSystem* _GraphicSystem=0;
	World* _MainEditorWorld=0;
	UISystem* _UISystem=0;
	

	AGE_EngineCore() {}

	 bool Inited();
	 virtual bool Update();
	 virtual void OnConstructorsAdded();
	 bool Diposed()
	{
		 delete g_pRuntimeObjectSystem;
		return true;
	}

private:
	// Runtime Systems
	ICompilerLogger* m_pCompilerLogger=0;
	IRuntimeObjectSystem* g_pRuntimeObjectSystem = 0;
	// Runtime object
	IUpdateable* m_pUpdateable=0;
	ObjectId	   			m_ObjectId;

	bool RCCppInit();
	void RCCppUpdate();
};




#endif // !AGE_ENGINECORE_H
