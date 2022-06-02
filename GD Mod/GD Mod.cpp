#include "framework.h"
#include "GD Mod.h"

#define ID_CLOSE 0x001



std::string titleBar = "GDMod - Seggs_Mode.gdmm";
BOOL isMouseDownOnCloseButton = FALSE;

void onMouseDown(HWND hWnd);
void Update(HWND hWnd, HDC hdc);
void addBTN(HWND hWnd);
void drawTitleBar(HWND hWnd);
void drawIcon(HWND hWnd, HDC hdc);
void drawOutlinedRect(HDC hdc, int x, int y, int width, int height, int lineWidth, COLORREF outlineColour, COLORREF fillColour);

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = {0};

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"myWindowClass", L"My Window", WS_VISIBLE | WS_POPUP, 100, 50, 1280, 720,
				NULL, NULL, NULL, NULL);

	MSG msg = {0};
	
	while ( GetMessage(&msg, NULL, NULL, NULL) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	LRESULT move = NULL;

	int x;
	int y;

	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		
		case WM_CREATE:
			SetTimer(hWnd, 1, 20, NULL);

			addBTN(hWnd);
			drawTitleBar(hWnd);
			break;

		case WM_TIMER:
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			Update(hWnd, hdc);
			//drawIcon(hWnd, hdc);
			EndPaint(hWnd, &ps);

			break;
		case WM_LBUTTONUP:
			
			//onMouseDown(hWnd);

			x = LOWORD(lp);
			y = HIWORD(lp);

			break;

		

		case WM_NCHITTEST:
			RECT rc;
			POINT pt;

			GetCursorPos(&pt);

			GetWindowRect(hWnd, &rc);
			rc.bottom = rc.top + 26;

			//if cursor position is within top layered drawn rectangle then  
			//set move to HTCAPTION for moving the window from its client  
			if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
			{
				move = DefWindowProc(hWnd, msg, wp, lp);
				if (move == HTCLIENT)
				{
					move = HTCAPTION;
				}
			}

			return move;

			break;

		
		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
	}
}


void Update(HWND hWnd, HDC hdc)
{
	
	RECT rect;
	HBRUSH brush;
	
	GetClientRect(hWnd, &rect);

	

	brush = CreateSolidBrush(RGB(9, 9, 9));

	FillRect(hdc, &rect, brush);

	rect.bottom = rect.top + 26;
	brush = CreateSolidBrush(RGB(21, 21, 21));
	FillRect(hdc, &rect, brush);

	RECT rc;
	POINT pt;

	GetCursorPos(&pt);

	GetWindowRect(hWnd, &rc);

	rc.bottom = rc.top + 26;

	rc.left = rc.right - 20;

	if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
	{
		SetBkColor(hdc, RGB(255, 0, 0));

	}
	else
	{
		SetBkColor(hdc, RGB(21, 21, 21));

	}
	SetTextColor(hdc, RGB(200, 200, 200));

	TextOut(hdc, rect.right - 20, 5, L"X", 1);
	SetBkColor(hdc, RGB(21, 21, 21));


	std::wstring stemp = std::wstring(titleBar.begin(), titleBar.end());
	LPCWSTR sw = stemp.c_str();

	TextOut(hdc, 26, 5, sw, titleBar.length());

	drawIcon(hWnd, hdc);

	GetWindowRect(hWnd, &rect);

	rect.left = 0;
	rect.top = 26;
	rect.bottom = rect.top + 22;
	
	brush = CreateSolidBrush(RGB(15, 15, 15));
	FillRect(hdc, &rect, brush);

	GetWindowRect(hWnd, &rect);
	
	SetBkColor(hdc, RGB(15, 15, 15));

	TextOut(hdc, 12, 29, L"File", 4);

	if (currentSceneName == "MainLayer")
	{
		rect.left = 0;
		rect.right = rect.left + 50;
		rect.top = 26 + 22;

		brush = CreateSolidBrush(RGB(15, 15, 15));
		FillRect(hdc, &rect, brush);

		
	}
}


void addBTN(HWND hWnd)
{
	//CreateWindowW(L"static", L"test.gdmm", WS_VISIBLE | WS_CHILD, 400, 200, 100, 50, hWnd,
		//(HMENU)ID_CLOSE, NULL, NULL);
}

void drawTitleBar(HWND hWnd)
{
	//auto closeButton = CreateWindowW(L"button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 100, 100, 100, 100, hWnd, (HMENU)ID_CLOSE, NULL, NULL);
}

void drawIcon(HWND hWnd, HDC hdc)
{
	//BASE
	drawOutlinedRect(hdc, 6, 6, 14, 14, 1, RGB(237, 237, 237), RGB(21, 21, 21));

	drawOutlinedRect(hdc, 8, 13, 10, 4, 1, RGB(237, 237, 237), RGB(21, 21, 21));

	//EYES
	drawOutlinedRect(hdc, 8, 8, 4, 4, 1, RGB(237, 237, 237), RGB(21, 21, 21));

	drawOutlinedRect(hdc, 14, 8, 4, 4, 1, RGB(237, 237, 237), RGB(21, 21, 21));
}


void drawOutlinedRect(HDC hdc, int x, int y, int width, int height, int lineWidth, COLORREF outlineColour, COLORREF fillColour)
{
	RECT rect;
	HBRUSH brush;

	rect.top = y;
	rect.left = x;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	brush = CreateSolidBrush(outlineColour);
	FillRect(hdc, &rect, brush);

	rect.top = rect.top + lineWidth;
	rect.left = rect.left + lineWidth;
	rect.right = rect.right - lineWidth;
	rect.bottom = rect.bottom - lineWidth;
	brush = CreateSolidBrush(fillColour);
	FillRect(hdc, &rect, brush);
}

HBITMAP loadImage(std::string directory)
{
	std::wstring stemp = std::wstring(titleBar.begin(), titleBar.end());
	LPCWSTR sw = stemp.c_str();

	auto log = (HBITMAP)LoadImageW(NULL, sw, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return log;
}


void onMouseDown(HWND hWnd)
{
	RECT rc;
	POINT pt;

	GetCursorPos(&pt);

	GetWindowRect(hWnd, &rc);

	rc.bottom = rc.top + 26;

	rc.left = rc.right - 20;
	
	if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
	{
		PostQuitMessage(0);
	}
}