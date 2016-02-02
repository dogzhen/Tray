#include <stdexcept>
#include "Tray.h"

TRAY::TRAY(const char* class_name, HINSTANCE hInstance)
{
	try
	{
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = class_name;
		wc.lpfnWndProc = TrayEventProc;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

		if (!RegisterClassEx(&wc))
			throw std::logic_error("Window class registration error.");

		try
		{
			hwnd = CreateWindowEx(
				0,
				class_name,
				0,
				WS_POPUP,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				hInstance,
				0);

			if (!hwnd)
				throw std::logic_error("Window creation error.");

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

			try
			{
				ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
				nid.cbSize = sizeof(NOTIFYICONDATA);
				nid.hWnd = hwnd;
				nid.hIcon = LoadIcon(0, IDI_APPLICATION);
				nid.uFlags = NIF_ICON | NIF_MESSAGE;
				nid.uID = static_cast<UINT>(reinterpret_cast<unsigned __int64>(this));
				nid.uCallbackMessage = WM_TRAY;
	
				if (!Shell_NotifyIcon(NIM_ADD, &nid))
					throw std::logic_error("Notify icon creation error.");
				
				try
				{
					if (FAILED(CoCreateInstance(
						CLSID_TaskbarList, 
						NULL, 
						CLSCTX_INPROC_SERVER, 
						__uuidof(ITaskbarList),
						reinterpret_cast<void**>(&taskbar))))
						throw std::logic_error("ITaskbarList interface creation failed.");

					try
					{
						if (FAILED(taskbar->HrInit()))
							throw std::logic_error("ITaskbarList interface error.");
					}
					catch(...)
					{
						taskbar->Release();
						throw;
					}
				}
				catch(...)
				{
					Shell_NotifyIcon(NIM_DELETE, &nid);
					throw;
				}
			}
			catch(...)
			{
				DestroyWindow(hwnd);
				throw;
			}
		}
		catch(...)
		{
			UnregisterClass(wc.lpszClassName, wc.hInstance);
			throw;
		}
	}
	catch(...)
	{
		throw;
	}
}

TRAY::~TRAY()
{
	taskbar->Release();
	CoUninitialize();
	Shell_NotifyIcon(NIM_DELETE, &nid);
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}

