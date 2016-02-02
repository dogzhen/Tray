#include <stdexcept>

#include "Tray.h"

LRESULT CALLBACK TrayEventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TRAY* trptr = reinterpret_cast<TRAY*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (trptr && trptr->EventProc(uMsg, wParam, lParam))
		return 0;
	else 
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool TRAY::EventProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_TRAY:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return true;
	}

	return false;
}