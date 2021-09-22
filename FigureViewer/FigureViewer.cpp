#include <windows.h>
#include <windowsx.h>
#include "Sight.h"
#include "Sight2.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� ��������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Figure Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,500,500,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);
	
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Sight
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
Sight sight(30, RGB(255, 0, 0));
Sight2 sight2(40,RGB(0,255,0));
int wSize = 500;
LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch(msg)
	{
	case WM_PAINT:						// ��������� ��������� WM_PAINT ������������ ������ ���, ����� ��������� ��������� ��� ����������� �����������
		{
			HDC dc = GetDC(hWnd);		// ������� GetDC ���������� �������� ����������, � ������� �������� ���������� � ���, � ����� ���� ������������ �����, ������ ������� ������� ������� ���� hWnd, � ����� ����� ������ ��������� ������ ��������� ������� ������� � �.�.
			sight.Clear(dc,hWnd);
			sight.Draw(dc);
			sight2.Draw(dc);
			ReleaseDC(hWnd, dc);		// ������� ReleaseDC �������� �������, ��� ��������� � ����� hWnd �������� dc ������ �� �����
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_LEFT:
				{ 
					if(sight.inWindow(wSize,-2,0))
					sight.Move(-2, 0);
				
					//sight2.Move(-2, 0);
					break;
				}
			case VK_RIGHT:
				{
				if (sight.inWindow(wSize, 2, 0))
					sight.Move(2, 0);
					break;
				}
			case VK_UP:
			{
				if (sight.inWindow(wSize, 0, -2))
				sight.Move(0, -2);
				break;
			}
			case VK_DOWN:
			{
				if (sight.inWindow(wSize, 0, 2))
				sight.Move(0, 2);
				break;
			}
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
		if (sight.inWindow(wSize, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
		{
			sight.MoveTo(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
		}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			if (sight.InnerPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))/*&& sight.inWindow(wSize, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))*/)
				sight.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			else if (sight2.InnerPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))/*&& sight2.inWindow(wSize, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))*/)
				sight2.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if (sight.IsDragging()&&sight.inWindow(wSize, GET_X_LPARAM(lParam)-sight.getX(), GET_Y_LPARAM(lParam)-sight.getY()))
			{
				sight.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			else if (sight2.IsDragging()&& sight2.inWindow(wSize, GET_X_LPARAM(lParam) - sight2.getX(), GET_Y_LPARAM(lParam) - sight2.getY()))
			{
				sight2.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);
		if (sight.InnerPoint(P.x, P.y)&&sight.MkCtrl(GET_KEYSTATE_WPARAM(wParam))&& sight.inWindowNewSize(wSize)) {
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			sight.ChangeSize(zDelta);
			InvalidateRect(hWnd, nullptr, false);
		}
		else if (sight2.InnerPoint(P.x, P.y) && sight2.MkCtrl(GET_KEYSTATE_WPARAM(wParam))&& sight2.inWindowNewSize(wSize)) {
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			sight2.ChangeSize(zDelta);
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;
		}
	case WM_LBUTTONUP:
		{
			sight.StopDragging();
			sight2.StopDragging();
			return 0;
		}
	case WM_SIZE:
		{
			InvalidateRect(hWnd, nullptr, false);	// ������� InvalidateRect ��������� ������� ������� ���� hWnd ��������� �����������, � ���������� ���� ������������ ��������� ��������� WM_PAINT
			return 0;								// ����� ������� �� ���������� ����, ��� ����������� ���������� � ��� ���������� �������� ����
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	return 0;
}
