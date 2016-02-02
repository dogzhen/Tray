#include <stdexcept>

#include "Tray.h"

int TRAY::GetTaskbarHeight()
{
	HWND taskbar = FindWindow("Shell_TrayWnd", 0);
	if (!taskbar)
		return 0;
	RECT rect;
	if (GetClientRect(taskbar, &rect))
		return rect.bottom-rect.top;
	else return 0;
}

void TRAY::UpdatePosition()
{
	SetWindowPos(
		hwnd,
		0,
		GetSystemMetrics(SM_CXSCREEN)-rect.width-rect.px,
		GetSystemMetrics(SM_CYSCREEN)-GetTaskbarHeight()-rect.height-rect.py,
		rect.width,
		rect.height,
		SWP_NOZORDER);
}
