#include <stdexcept>

#include "Tray.h"

void TRAY::SetCaptionText(const char* txt)
{
	SetWindowText(hwnd, txt);
}

void TRAY::SetPosition(int width, int height, int px, int py)
{
	rect.width = width;
	rect.height = height;
	rect.px = px;
	rect.py = py;
	UpdatePosition();
}

void TRAY::Show(int nCmdShow)
{
	ShowWindow(hwnd, nCmdShow);
}

void TRAY::ShowOnTaskbar(bool mode)
{
	if (mode)
		taskbar->AddTab(hwnd);
	else taskbar->DeleteTab(hwnd);
}

void TRAY::ShowOnHover(bool mode)
{
	show_on_hover.on = mode;
}


