#include <Windows.h>
#include <stdexcept>
#include "Tray/Tray.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	int ret_value = 0;
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);

	try
	{
		TRAY* Tray = new TRAY("TrayClass", hInstance);
		Tray->SetPosition(200, 200, 0, 0);
		Tray->SetCaptionText("example text");
		Tray->ShowOnTaskbar(false);
		Tray->Show();

		MSG msg;
		while(GetMessage(&msg, 0, 0, 0))
		{	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		delete Tray;
		ret_value = static_cast<int>(msg.wParam);
	} 
	catch (...)
	{

	}
	CoUninitialize();
	return ret_value;
}