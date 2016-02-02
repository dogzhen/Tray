#pragma once

#include <Windows.h>
#include <ShObjIdl.h>

class TRAY
{
protected:
	WNDCLASSEX wc; // klasa okna
	HWND hwnd;	// wyœwietlane okno
	NOTIFYICONDATA nid; // struktura dla ikonki traya
	static const unsigned int WM_TRAY = 0x8001;

	struct TRAY_RECT
	{
		int width;
		int height;
		int px;
		int py;

		TRAY_RECT() :
			width(0),
			height(0),
			px(0),
			py(0) {}
	};
	TRAY_RECT rect; // po³o¿enie okna

	struct SHOW_ON_HOVER
	{
		bool on;
		bool visible;

		SHOW_ON_HOVER() :
			on(false),
			visible(false) {}
	};
	SHOW_ON_HOVER show_on_hover;

	ITaskbarList* taskbar; // dostêp do paska menu start

	// ... tray_protected.cpp
	int GetTaskbarHeight();
	void UpdatePosition();
	//void TrayShowing_TrayIconHover();
	//void TrayShowing_MouseOn();
	//void TrayShowing_MouseOut();

public:
	// ... tray_con_dest.cpp
	TRAY(const char* class_name, HINSTANCE hInstance);
	TRAY(const TRAY&) = delete;
	TRAY& operator= (const TRAY&) = delete;
	~TRAY();

	// metody dostêpowe
	HWND RetHwnd() { return hwnd; }

	// ... tray_controls.cpp
	void SetCaptionText(const char* txt);
	void SetPosition(int width, int height, int x_pos = 0, int y_pos = 0);
	void Show(int nCmdShow = SW_SHOWNORMAL);
	void ShowOnTaskbar(bool mode);
	void ShowOnHover(bool mode);

	// ... tray_event_proc.cpp
	friend LRESULT CALLBACK TrayEventProc(HWND, UINT, WPARAM, LPARAM);
	bool EventProc(UINT, WPARAM, LPARAM);
};