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
#define CONSOLE_TOPMOST
#ifdef CONSOLE_TOPMOST
#include<Windows.h>


#endif
#include <System/AGE_EngineCore.hpp>
#include <ConsoleGame.h>
#include <conio.h>
AGE_EngineCore* _AGE_EngineCore = new AGE_EngineCore();

int main()
{
	SetWindowPos(GetConsoleWindow(),HWND_TOPMOST,0,0,0,0,SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);  //本身沒有意義  只是為了讓CMD保持在最上層 *Windows 限定
	/*ConsoleGame game;
	if (game.Init())
	{
		while (game.MainLoop())
		{
		}
	}
	else
	{
		std::cout << "\nFailed Initialisation, press a key to exit.\n";
		_getche();
	}

	std::cout << "Exiting...\n";

	*/

	if (!_AGE_EngineCore->Inited()) { return -1; }

	while (_AGE_EngineCore->Update())
	{
		


	}

	_AGE_EngineCore->Diposed();
	return 0;
}