#include "windows.h"

// Глобальны переменные:

#include "Class.h"

HINSTANCE hInst;

LPCTSTR szWindowClass = "szMainWindowClass";
LPCTSTR szTitle = "X of O?";

HWND MainWindow;

// Прототипы функций:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 

void CreatingMainWindow() {

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = (HICON)LoadImage(NULL, "Imgs\\ico.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE),
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = Bitmapof.bBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	MainWindow = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		650,
		500,
		NULL,
		NULL,
		hInst,
		NULL
	);

	SetTimer(MainWindow, 1111, 1000, NULL);

	ShowWindow(MainWindow, SW_NORMAL);
	UpdateWindow(MainWindow);

	turn = Q::x;

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hInst = hInstance;

	MSG msg;

	CreatingMainWindow();

	// Цикл обработки событий:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void paintImage(HDC hdc, HBITMAP hBitmap) {

	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, hBitmap);

	//GDITransparentBlt

	DeleteDC(MemDC);

	
}

void TestPrint(HDC hdc) {
	
	HDC MemDC = CreateCompatibleDC(hdc);
	
	//

	SelectObject(MemDC, Bitmapof.x[0]);

	GdiTransparentBlt(hdc, 0, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[1]);

	GdiTransparentBlt(hdc, 50, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[2]);

	GdiTransparentBlt(hdc, 100, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[3]);

	GdiTransparentBlt(hdc, 150, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[4]);

	GdiTransparentBlt(hdc, 200, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[5]);

	GdiTransparentBlt(hdc, 250, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[6]);

	GdiTransparentBlt(hdc, 300, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.x[7]);

	GdiTransparentBlt(hdc, 350, 0, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.o[0]);

	GdiTransparentBlt(hdc, 0, 50, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.o[1]);

	GdiTransparentBlt(hdc, 50, 50, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.o[2]);

	GdiTransparentBlt(hdc, 100, 50, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.o[3]);

	GdiTransparentBlt(hdc, 150, 50, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.o[4]);

	GdiTransparentBlt(hdc, 200, 50, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.o[5]);

	GdiTransparentBlt(hdc, 250, 50, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.down);

	GdiTransparentBlt(hdc, 0, 100, 50, 250, MemDC, 150, 0, 75, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.left);

	GdiTransparentBlt(hdc, 50, 100, 250, 50, MemDC, 0, 150, 400, 75, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.right_down);

	GdiTransparentBlt(hdc, 50, 150, 250, 250, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.left_down);

	GdiTransparentBlt(hdc, 50, 150, 250, 250, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	SelectObject(MemDC, Bitmapof.drops);

	GdiTransparentBlt(hdc, 250, 100, 400, 400, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	//

	DeleteDC(MemDC);

}

void PaintX(HDC hdc, int x, int y) {

	int r = rand() % 8;

	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, Bitmapof.x[r]);

	GdiTransparentBlt(hdc, x, y, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	DeleteDC(MemDC);

}

void PaintO(HDC hdc, int x, int y){

	int r = rand() % 6;
	
	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, Bitmapof.o[r]);

	GdiTransparentBlt(hdc, x, y, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	DeleteDC(MemDC);

}

void PaintBackGround(HDC hdc){

	int y_from;
	int x_from;

	RECT client_rect;

	GetClientRect(MainWindow, &client_rect);

	HDC MemDC = CreateCompatibleDC(hdc);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 400, 400);

	SelectObject(MemDC, hBitmap);
	SelectObject(MemDC, GetStockObject(NULL_PEN));
	SelectObject(MemDC, Bitmapof.bBrush);

	Rectangle(MemDC, 0, 0, 401, 401);

	if(x_scroll < 0)
		x_from = x_scroll % 400;
	else {
		x_from = x_scroll % 400 - 400;
	}


	while (x_from < client_rect.right - client_rect.left) {
		
		if (y_scroll < 0)
			y_from = y_scroll % 400;
		else {
			y_from = y_scroll % 400 - 400;
		}

		while (y_from < client_rect.bottom - client_rect.top) {

			BitBlt(hdc, x_from, y_from, 400, 400, MemDC, 0, 0, SRCCOPY);
		
			y_from += 400;

		}

		x_from += 400;

	}

	DeleteObject(hBitmap);

	DeleteDC(MemDC);

}

void PaintDrops(HDC hdc, int x, int y) {

	int r = rand() % 6;

	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, Bitmapof.drops);

	GdiTransparentBlt(hdc, x, y, 400, 400, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

	DeleteDC(MemDC);

}

void Redraw(HDC MainDC) {

	RECT client_rect;

	GetClientRect(MainWindow, &client_rect);

	HDC hdc = CreateCompatibleDC(MainDC);

	HBITMAP hBitmap = CreateCompatibleBitmap(MainDC, client_rect.right - client_rect.left + std::abs(x_scroll), client_rect.bottom - client_rect.top);

	SelectObject(hdc, hBitmap);

	SelectObject(hdc, GetStockObject(NULL_PEN));
	SelectObject(hdc, Bitmapof.bBrush);

	PaintBackGround(hdc);

//	TestPrint(hdc);

	Arr.Print(hdc);

	BitBlt(MainDC, client_rect.left, client_rect.top, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, hdc, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);

	DeleteDC(hdc);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;

	HDC hdc;

	static POINT cur = { 0, 0 };

	switch (message)
	{
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		Redraw(hdc);

		EndPaint(hWnd, &ps);

		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		
		if (is_game_going) {

			{

				int x = cur.x;
				int y = cur.y;

				int d;

				if (std::abs(x % 50) > 40 || std::abs(x % 50) < 10 || std::abs(y % 50) > 40 || std::abs(y % 50) < 10) {

					Arr.Push_back(drop_type, cur.x - 200, cur.y - 200);

					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

					break;

				}

				d = x % 50;

				if (d > 0) {

					x -= d;

				}
				else {

					x = x - d - 50;

				}

				d = y % 50;

				if (d > 0) {

					y -= d;

				}
				else {

					y = y - d - 50;

				}

				x /= 50;
				y /= 50;
				
				//412

				if (field.count(Cell(x, y))) {

					Arr.Push_back(field[Cell(x, y)] == Q::x? x_type : o_type, cur.x - 25, cur.y - 25);

					RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

					break;
				}

				field.push(Cell(x, y), turn);

			}

			Arr.Push_back((int)turn, cur.x - 25, cur.y - 25);

			if (CheckForWin(field.c_arr[field.c_arr.size() - 1])) {

				Arr.Push_back(line_type, WinPoint.x * 50 + 25, WinPoint.y * 50 + 25);

				is_game_going = false;

			}

			switch (turn) {

			case Q::o:

				turn = Q::x;

				break;
			case Q::x:
			default:

				turn = Q::o;

				break;
			}

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

		}
		else {

			is_game_going = true;

			Arr.Clear();

			field.Clear();

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

		}

		break;

	case WM_KEYDOWN:

		if (is_game_going) {

			if (GetAsyncKeyState(VK_SPACE)) {

				Arr.Push_back(drop_type, cur.x - 200, cur.y - 200);

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {

				x_scroll -= 10;

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {

				x_scroll += 10;

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {

				y_scroll -= 10;

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {

				y_scroll += 10;

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}

		}
		else {

			is_game_going = true;

			Arr.Clear();

			field.Clear();

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

		}

		break;

	case WM_MOUSEMOVE:

		cur.x = LOWORD(lParam) - x_scroll;

		cur.y = HIWORD(lParam) - y_scroll;

		break;

	case WM_TIMER:

		if (!is_game_going) {

			{

				int x, y;

				RECT client_rect;

				GetClientRect(MainWindow, &client_rect);

				x = rand() % (client_rect.right - client_rect.left);
				y = rand() % (client_rect.bottom - client_rect.top);

				Arr.Push_back(drop_type, x - 200, y - 200);
			
			}

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

		}

		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	case WM_CREATE:

	{

		POINT pt;

		GetCursorPos(&pt);

	}

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

