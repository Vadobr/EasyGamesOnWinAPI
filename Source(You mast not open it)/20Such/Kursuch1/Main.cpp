#include "windows.h"
#include <vector>
#include "resource.h"
#include <string>

// Глобальны переменные:

#define IDB_BITMAP_BACKGROUND IDB_BITMAP3

HINSTANCE hInst;

LPCTSTR szWindowClass = "szMainWindowClass";
LPCTSTR szWinWindowClass = "szWinWindowClass";
LPCTSTR szTitle = "Is sum 20?";

HWND MainWindow;
HWND SubWindow;

bool uncheck = true;

struct {

	struct {

		int count_1 = 10;
		int count_2 = 7;
		int count_3 = 5;

	} player_1;

	struct {

		int count_1 = 10;
		int count_2 = 6;
		int count_3 = 5;		

	} player_2;

	int player_1_score = 0;

	int player_2_score = 0;

	int BO = 1;

	int player_s_turn = 1;

	std::vector <int> table;

	int sum() {

		int res = 0;

		for (int i(0); i < table.size(); i++) {
			res += table[i];
		}

		return res;

	}

	void clear() {

		player_1.count_1 = 10;
		player_1.count_2 = 7;
		player_1.count_3 = 5;

		player_2.count_1 = 10;
		player_2.count_2 = 6;
		player_2.count_3 = 5;

		player_s_turn = played % 2 + 1;

		table.clear();

	}

	int played = 0;

} game_info;

// Прототипы функций:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SubWndProc(HWND, UINT, WPARAM, LPARAM);

//

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hInst = hInstance;

	MSG msg;

	{
		HBITMAP hBMP = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND));

		HBRUSH hBrush = CreatePatternBrush(hBMP);

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(112));
		wcex.hCursor = LoadCursorFromFile("res/Cursor.cur");
		wcex.hbrBackground = hBrush;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = NULL;

		RegisterClassEx(&wcex);

	}
	
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(215, 215, 215));

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)SubWndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(112));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = hBrush;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWinWindowClass;
		wcex.hIconSm = NULL;

		RegisterClassEx(&wcex);

	}

	{

		MainWindow = CreateWindowEx(
			NULL,
			szWindowClass,
			szTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			900,
			630,
			NULL,
			NULL,
			hInst,
			NULL
		);

		ShowWindow(MainWindow, SW_NORMAL);
		UpdateWindow(MainWindow);


	}

	// Цикл обработки событий:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void DrawCoin(HDC coin, HDC hDC, int x, int y){

	BitBlt(coin, 0, 0, 70, 70, hDC, x, y, SRCCOPY);
	Ellipse(coin, 0, 0, 70, 70);
	BitBlt(hDC, x, y, 70, 70, coin, 0, 0, SRCCOPY);

}

void EndGameWindow(HWND ParrentWnd){

		SubWindow = CreateWindow(
			szWinWindowClass,
			"Continue?",
			WS_OVERLAPPED,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			400,
			300,
			ParrentWnd,
			NULL,
			hInst,
			NULL
		);

		ShowWindow(SubWindow, SW_NORMAL);
		UpdateWindow(SubWindow);

		std::string str;

		RECT cl_r;

		str = "play \"Best of " + std::to_string(game_info.BO) + "\"";

		GetClientRect(SubWindow, &cl_r);

		CreateWindow(
			"BUTTON",
			str.c_str(),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10,
			(cl_r.bottom - cl_r.top)*4/5 - 10,
			(cl_r.right - cl_r.left)/2 - 20,
			(cl_r.bottom - cl_r.top)/ 5,
			SubWindow,
			(HMENU)777,
			hInst,
			NULL
		);

		CreateWindow(
			"BUTTON",
			"Quit",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			(cl_r.right - cl_r.left) / 2 + 10,
			(cl_r.bottom - cl_r.top) * 4 / 5 - 10,
			(cl_r.right - cl_r.left) / 2 - 20,
			(cl_r.bottom - cl_r.top) / 5,
			SubWindow,
			(HMENU)776,
			hInst,
			NULL
		);




}

void DroppShadow(HDC Dest, HDC Source, int x, int y) {

	HBITMAP shadow = CreateCompatibleBitmap(Dest, 90, 80);

	static HFONT hFont = CreateFont(15, 10, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");

	HGDIOBJ oldBMP = SelectObject(Source, shadow);
	HGDIOBJ oldBrush = SelectObject(Source, GetStockObject(WHITE_BRUSH));
	HGDIOBJ oldPen = SelectObject(Source, GetStockObject(NULL_PEN));

	Ellipse(Source, 0, 0, 90, 80);

	BLENDFUNCTION ftn;

	ftn.SourceConstantAlpha = (BYTE)110;
	ftn.BlendOp = (BYTE)AC_SRC_OVER;
	ftn.AlphaFormat = (BYTE)AC_SRC_ALPHA;
	ftn.BlendFlags = (BYTE)0;

	AlphaBlend(Dest, x, y, 90, 80, Source, 0, 0, 90, 80, ftn);

	DeleteObject(shadow);

}

PAINTSTRUCT ps;
RECT client_rect;

HDC BackgrounDC;
HDC TurnDC;
HDC ShadowDC;

static HFONT hFont;

static HBITMAP BackgroundBmp;

static HBITMAP turn_1;
static HBITMAP turn_2;

static HBRUSH yellow_brush;

static HBRUSH coin_1_brush;
static HBRUSH coin_2_brush;
static HBRUSH coin_3_brush;

HDC coin_1;
HDC coin_2;
HDC coin_3;

HBITMAP coin_1_bmp;
HBITMAP coin_2_bmp;
HBITMAP coin_3_bmp;

int x, y, x0, yF;

RECT rt;

std::string str;

void Redraw(HDC MainDC) {

	HDC hDC = CreateCompatibleDC(MainDC);

	GetClientRect(MainWindow, &client_rect);

	HBITMAP MemBitmap = CreateCompatibleBitmap(MainDC, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top);

	SelectObject(hDC, MemBitmap);

	SelectObject(hDC, GetStockObject(NULL_PEN));

	///////////


	BackgrounDC = CreateCompatibleDC(hDC);
	SelectObject(BackgrounDC, BackgroundBmp);
	BitBlt(hDC, 0, 0, 900, 600, BackgrounDC, 0, 0, SRCCOPY);

	coin_1 = CreateCompatibleDC(hDC);
	coin_2 = CreateCompatibleDC(hDC);
	coin_3 = CreateCompatibleDC(hDC);

	TurnDC = CreateCompatibleDC(hDC);

	ShadowDC = CreateCompatibleDC(hDC);

	//////////

	if (game_info.player_s_turn == 1 && game_info.sum() < 20) {
		SelectObject(TurnDC, turn_1);
		BitBlt(hDC, 120, 410, 330, 70, TurnDC, 0, 0, SRCCOPY);
	}
	if (game_info.player_s_turn == 2 && game_info.sum() < 20) {
		SelectObject(TurnDC, turn_2);
		BitBlt(hDC, 455, 125, 330, 70, TurnDC, 0, 0, SRCCOPY);
	}

	coin_1_bmp = CreateCompatibleBitmap(hDC, 70, 70);
	coin_2_bmp = CreateCompatibleBitmap(hDC, 70, 70);
	coin_3_bmp = CreateCompatibleBitmap(hDC, 70, 70);

	SelectObject(coin_1, coin_1_bmp);
	SelectObject(coin_1, coin_1_brush);
	SelectObject(coin_1, GetStockObject(NULL_PEN));

	SelectObject(coin_2, coin_2_bmp);
	SelectObject(coin_2, coin_2_brush);
	SelectObject(coin_2, GetStockObject(NULL_PEN));

	SelectObject(coin_3, coin_3_bmp);
	SelectObject(coin_3, coin_3_brush);
	SelectObject(coin_3, GetStockObject(NULL_PEN));

	////////////////

	for (int i(0); i < game_info.player_1.count_1; i++) {

		DrawCoin(coin_1, hDC, 100 + i * 3, 490);

	}

	for (int i(0); i < game_info.player_1.count_2; i++) {

		DrawCoin(coin_2, hDC, 250 + i * 3, 490);

	}

	for (int i(0); i < game_info.player_1.count_3; i++) {

		DrawCoin(coin_3, hDC, 400 + i * 3, 490);

	}

	for (int i(0); i < game_info.player_2.count_1; i++) {

		DrawCoin(coin_1, hDC, 350 + i * 3, 40);

	}

	for (int i(0); i < game_info.player_2.count_2; i++) {

		DrawCoin(coin_2, hDC, 500 + i * 3, 40);

	}

	for (int i(0); i < game_info.player_2.count_3; i++) {

		DrawCoin(coin_3, hDC, 650 + i * 3, 40);

	}


	for (int i(0); i < 10 && i < game_info.table.size(); i++) {

		if (game_info.table[i] == 1)
			DrawCoin(coin_1, hDC, 100 + i * 45, 200);
		if (game_info.table[i] == 2)
			DrawCoin(coin_2, hDC, 100 + i * 45, 200);
		if (game_info.table[i] == 3)
			DrawCoin(coin_3, hDC, 100 + i * 45, 200);

	}

	for (int i(10); i < game_info.table.size(); i++) {

		if (game_info.table[i] == 1)
			DrawCoin(coin_1, hDC, 100 + (i - 10) * 45, 300);
		if (game_info.table[i] == 2)
			DrawCoin(coin_2, hDC, 100 + (i - 10) * 45, 300);
		if (game_info.table[i] == 3)
			DrawCoin(coin_3, hDC, 100 + (i - 10) * 45, 300);

	}

	SelectObject(hDC, hFont);

	SetBkMode(hDC, TRANSPARENT);

	SetTextColor(hDC, RGB(0, 0, 0));

	rt.left = 50;
	rt.top = 53;
	rt.bottom = 153;
	rt.right = 350;

	str = "SCORE: " + std::to_string(game_info.player_2_score);

	DrawText(hDC, str.c_str(), str.size(), &rt, DT_LEFT);

	SetTextColor(hDC, RGB(75, 75, 75));

	rt.left = 580;
	rt.top = 500;
	rt.bottom = 600;
	rt.right = 880;

	str = "SCORE: " + std::to_string(game_info.player_1_score);

	DrawText(hDC, str.c_str(), str.size(), &rt, DT_LEFT);


	//////////

	BitBlt(MainDC, 0, 0, 900, 600, hDC, 0, 0, SRCCOPY);

	DeleteObject(MemBitmap);

	DeleteDC(hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	HDC hDC;

	int y0;
	
	switch (message)
	{
	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);

		Redraw(hDC);

		/////////////////////

		EndPaint(hWnd, &ps);

		DeleteObject(coin_1_bmp);
		DeleteObject(coin_2_bmp);
		DeleteObject(coin_3_bmp);

		DeleteDC(coin_1);
		DeleteDC(coin_2);
		DeleteDC(coin_3);

		DeleteDC(BackgrounDC);
		DeleteDC(TurnDC);

		DeleteDC(coin_1);
		DeleteDC(coin_2);
		DeleteDC(coin_3);

		break;

	case WM_LBUTTONDOWN:

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		if (game_info.player_s_turn == 1) {

			y0 = 525;

			x0 = 100 + (game_info.player_1.count_1 - 1) * 3 + 35;

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 1225) {
				game_info.player_1.count_1--;
				game_info.table.push_back(1);
				game_info.player_s_turn = 2;
			}

			x0 = 250 + (game_info.player_1.count_2 - 1) * 3 + 35;

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 1225) {
				game_info.player_1.count_2--;
				game_info.table.push_back(2);
				game_info.player_s_turn = 2;
			}

			x0 = 400 + (game_info.player_1.count_2 - 1) * 3 + 35;

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 1225) {
				game_info.player_1.count_3--;
				game_info.table.push_back(3);
				game_info.player_s_turn = 2;
			}
		
		}

		if (game_info.player_s_turn == 2) {
			
			y0 = 75;

			x0 = 350 + (game_info.player_2.count_1 - 1) * 3 + 35;

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 1225) {
				game_info.player_2.count_1--;
				game_info.table.push_back(1);
				game_info.player_s_turn = 1;
			}

			x0 = 500 + (game_info.player_2.count_2 - 1) * 3 + 35;

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 1225) {
				game_info.player_2.count_2--;
				game_info.table.push_back(2);
				game_info.player_s_turn = 1;
			}

			x0 = 650 + (game_info.player_2.count_2 - 1) * 3 + 35;

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 1225) {
				game_info.player_2.count_3--;
				game_info.table.push_back(3);
				game_info.player_s_turn = 1;
			}

		}

		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	case WM_CREATE:

		////

		yellow_brush = CreateSolidBrush(RGB(200, 200, 40));

		BackgroundBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));

		coin_1_brush = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5)));
		coin_2_brush = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6)));
		coin_3_brush = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7)));

		turn_1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
		turn_2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));

		hFont = CreateFont(50, 20, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	if (game_info.sum() >= 20 && uncheck) {

		game_info.played++;

		if (game_info.player_s_turn == 2) {

			game_info.player_1_score++;

			if (game_info.player_1_score == (game_info.BO + 1) / 2) {
				
				uncheck = false;
				EnableWindow(MainWindow, false);

				EndGameWindow(hWnd);
			}
			else {

				game_info.clear();

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}

		}

		if (game_info.player_s_turn == 1) {
			
			game_info.player_2_score++;

			if (game_info.player_2_score == (game_info.BO + 1) / 2) {

				uncheck = false;
				EnableWindow(MainWindow, false);

				EndGameWindow(hWnd);
			}
			else {

				game_info.clear();

				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			}

		}
				
		
	}

	return 0;
}

LRESULT CALLBACK SubWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	RECT client_rect;

	HDC hdc;

	RECT win_rect;

	static HFONT hFont;

	std::string str;

	switch (message)
	{
	case WM_PAINT:

		GetClientRect(SubWindow, &client_rect);

		client_rect.top = (client_rect.bottom - client_rect.top) / 3;

		hdc = BeginPaint(hWnd, &ps);

		str = "player №";

		if (game_info.player_s_turn == 1) {
			str += "2";
			SetTextColor(hdc, RGB(0, 100, 0));
		}
		if (game_info.player_s_turn == 2) {
			SetTextColor(hdc, RGB(100, 0, 100));
			str += "1";
		}

		str += " wins!";

		SelectObject(hdc, hFont);

		SetBkColor(hdc, RGB(215, 215, 215));

		DrawText(hdc, str.c_str(), str.size(), &client_rect, DT_CENTER);

		EndPaint(hWnd, &ps);

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case 776:

			PostQuitMessage(0);
			
			break;

		case 777:

			DestroyWindow(hWnd);

			break;

		default:

			break;

		}

		break;

	case WM_DESTROY:

		DeleteObject(hFont);

		EnableWindow(MainWindow, true);

		game_info.clear();

		uncheck = true;

		GetWindowRect(MainWindow, &win_rect);

		SetWindowPos(MainWindow, HWND_TOP, win_rect.left, win_rect.top, win_rect.right - win_rect.left, win_rect.bottom - win_rect.top, SWP_SHOWWINDOW);

		RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);
		ShowWindow(MainWindow, SW_NORMAL);	
		UpdateWindow(MainWindow);

		break;

	case WM_CREATE:

		game_info.BO += 2;

		hFont = CreateFont(50, 20, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

