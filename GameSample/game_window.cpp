/*========================================================================================

 ゲームウインドウ  GAMEWINDOW <GameWindow.h>					LCH
																DATE:06/06/2005

------------------------------------------------------------------------------------------

=========================================================================================*/
#include "game_window.h"
#include <algorithm>
#include "keyboard.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


static constexpr char WINDOW_CLASS[] = "GameWindow";
static constexpr char TITLE[] = "Game";

static const constexpr int SCREEN_WIDTH = 1980;
static const constexpr int SCREEN_HEIGHT = 1080;




HWND GameWindow_Create(HINSTANCE hInstance)
{
	
	WNDCLASSEX wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WINDOW_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);



	
	RECT window_rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	DWORD style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	AdjustWindowRect(&window_rect, style, FALSE);

	const int WINDOW_WIDTH = window_rect.right - window_rect.left;
	const int WINDOW_HEIGHT = window_rect.bottom - window_rect.top;


	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	
	const int WINDOW_X = std::max((desktop_width - WINDOW_WIDTH) / 2, 0);
	const int WINDOW_Y = std::max((desktop_height - WINDOW_HEIGHT) / 2, 0);


	HWND hWnd = CreateWindow(
		WINDOW_CLASS,
		TITLE,
		style,
		WINDOW_X,
		WINDOW_Y,
		WINDOW_WIDTH,
		SCREEN_HEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	return HWND(hWnd);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATEAPP:
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(message, wParam, lParam);
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "Are you sure you want to close?", "Confirm Exit", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		// If NO is selected, do nothing (prevents closing)
		break;
	case WM_DESTROY:// Triggers WM_DESTROY
		PostQuitMessage(0);

		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}