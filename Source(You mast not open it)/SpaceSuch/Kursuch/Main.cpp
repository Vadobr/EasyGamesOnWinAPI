#include "Windows.h"
#include "resource.h"
#include <thread>


#include <vector>
#include <list>
#include <string>



// Глобальны переменные:

bool AA(const POINT&, const POINT&, const POINT&, const POINT&);
bool Collision(const std::vector <POINT>, const std::vector <POINT>);

HINSTANCE hInst;

LPCTSTR szWindowClass = "szMainWindowClass";
LPCTSTR szTitle = "WorldOfWarship";

HWND MainWindow;

HDC MainDC;
HDC MemDC;

RECT client_rect;

static HBITMAP bmp_move_left;
static HBITMAP bmp_move_right;

static HFONT hFont;


bool is_drawing;

bool is_firing;

int sm_x;

struct {

	int fire_int;
	bool stop_fire_lt;
	bool stop_fire_rt;

	int score;

	int score_cnt;
	int score_prev_cnt;

} game_info;

struct {

	HBITMAP Fly;
	HBITMAP no_Fly;
	HBITMAP Fly_lft;
	HBITMAP Fly_rt;

	HBITMAP current_Fly;

	int x = 0;
	int v;
	int a;

	std::vector <POINT> GetConvex() {
	
		std::vector <POINT> res;

		POINT buf;

		buf.x = x + 28;
		buf.y = 93;

		res.push_back(buf);

		buf.x = x + 48;
		buf.y = 105;

		res.push_back(buf);

		buf.x = x + 63;
		buf.y = 170;

		res.push_back(buf);

		buf.x = x + 78;
		buf.y = 105;

		res.push_back(buf);

		buf.x = x + 98;
		buf.y = 93;

		res.push_back(buf);

		return res;

	}

	int prev_dir;

	void move() {

		ship_info.a = 0;

		if (GetAsyncKeyState(VK_RIGHT)) {

			game_info.stop_fire_rt = false;

			ship_info.a = 2;
			ship_info.prev_dir = -2;

			ship_info.current_Fly = ship_info.Fly_rt;

		}
		else if (GetAsyncKeyState(VK_LEFT)) {

			game_info.stop_fire_lt = false;

			ship_info.a = -2;
			ship_info.prev_dir = 2;

			ship_info.current_Fly = ship_info.Fly_lft;

		}
		else {

			if (ship_info.v != 0) {
				ship_info.a = -1 * ship_info.v / std::abs(ship_info.v);
				ship_info.current_Fly = ship_info.Fly;
			}
			else {
				ship_info.prev_dir = 0;
				ship_info.current_Fly = ship_info.no_Fly;
			}
		}

		ship_info.v += ship_info.a;

		ship_info.x += ship_info.v;

		if (ship_info.x <= 0 - 20) {
			ship_info.x = 0 - 20;

			ship_info.a = 0;
			ship_info.v = 0;
		}

		if (ship_info.x >= GetSystemMetrics(SM_CXSCREEN) - 105) {
			ship_info.x = GetSystemMetrics(SM_CXSCREEN) - 105;

			ship_info.a = 0;
			ship_info.v = 0;
		}

	}

	void paint(HDC mMainDC) {

		HDC WarshipDC;

		WarshipDC = CreateCompatibleDC(mMainDC);

		SelectObject(WarshipDC, ship_info.current_Fly);

		GdiTransparentBlt(mMainDC, ship_info.x, 0, 128, 170, WarshipDC, 0, 86, 128, 170, RGB(0, 255, 0));

		DeleteDC(WarshipDC);

	}

} ship_info;

struct {

	HBITMAP bmp1;
	HBITMAP bmp2;
	HBITMAP bmp3;

	std::vector<POINT> convex1;
	std::vector<POINT> convex2;
	std::vector<POINT> convex3;

	int full_size = 128;
	
	void pool_convexes() {

		POINT buf;
		
			
			buf.x = 6; buf.y = 64;
			convex1.push_back(buf);
			buf.x = 12;buf.y =  37;
			convex1.push_back(buf);
			buf.x = 29;buf.y =  23;
			convex1.push_back(buf);
			buf.x = 59;buf.y =  3;
			convex1.push_back(buf);
			buf.x = 68;buf.y =  3;
			convex1.push_back(buf);
			buf.x = 87;buf.y =  12;
			convex1.push_back(buf);
			buf.x = 118;buf.y =  41;
			convex1.push_back(buf);
			buf.x = 124;buf.y =  53;
			convex1.push_back(buf);
			buf.x = 121;buf.y =  64;
			convex1.push_back(buf);

			buf.x = 12;buf.y =  64;
			convex2.push_back(buf);
			buf.x = 12;buf.y =  31;
			convex2.push_back(buf);
			buf.x = 25;buf.y =  16;
			convex2.push_back(buf);
			buf.x = 42;buf.y =  7;
			convex2.push_back(buf);
			buf.x = 85;buf.y =  5;
			convex2.push_back(buf);
			buf.x = 92;buf.y =  14;
			convex2.push_back(buf);
			buf.x = 100;buf.y =  28;
			convex2.push_back(buf);
			buf.x = 112;buf.y =  64;
			convex2.push_back(buf);

			buf.x = 5;buf.y =  64;
			convex3.push_back(buf);
			buf.x = 7;buf.y =  57;
			convex3.push_back(buf);
			buf.x = 21;buf.y =  49;
			convex3.push_back(buf);
			buf.x = 29;buf.y =  36;
			convex3.push_back(buf);
			buf.x = 53;buf.y =  27;
			convex3.push_back(buf);
			buf.x = 78;buf.y =  16;
			convex3.push_back(buf);
			buf.x = 87;buf.y =  16;
			convex3.push_back(buf);
			buf.x = 100;buf.y =  26;
			convex3.push_back(buf);
			buf.x = 117;buf.y =  44;
			convex3.push_back(buf);
			buf.x = 124;buf.y =  57;
			convex3.push_back(buf);
			buf.x = 125;buf.y =  64;
			convex3.push_back(buf);

	}

} astro_info;

struct{

public:

	struct astro {
	
		int x;
		int y;

		int own_speed;

		HBITMAP bmp;

		double scale_x;
		double scale_y;

		std::vector <POINT>* convex;

		astro() {

			own_speed = rand() % 3 + 1;

			int i_r = rand() % 3;

			scale_x = 1;// (rand() % 90) + 10;// 100.;
			scale_x /= double( rand() % 5);

			scale_y = scale_x;

			x = rand() %GetSystemMetrics(SM_CXSCREEN) - 64*scale_x;
			y = GetSystemMetrics(SM_CYSCREEN);

			switch (i_r) {

			case 0:
				bmp = astro_info.bmp1;
				convex = &astro_info.convex1;
				break;
			case 1:
				bmp = astro_info.bmp2;
				convex = &astro_info.convex2;
				break;
			case 2:
			default:
				bmp = astro_info.bmp3;
				convex = &astro_info.convex3;
				break;

			}
		}

		astro(const astro &source){

			x = source.x;
			y = source.y;

			scale_x = source.scale_x;
			scale_y = source.scale_y;

			bmp = source.bmp;

			convex = source.convex;

		}

		std::vector <POINT> GetConvex() {

			std::vector <POINT> res = (*convex);

			for (int i(0); i < res.size(); i++) {

				res[i].x = double(res[i].x) * this->scale_x + this->x;
				res[i].y = double(res[i].y) * this->scale_y + this->y;

			}

			return res;

		}

	};

	std::list <astro> arr;

	void push() {
		
		arr.push_back(astro());

		game_info.score_cnt++;

	};

	void move() {

		std::list<astro>::iterator i = arr.begin();
		std::list<astro>::iterator j;

		std::vector <POINT> ship = ship_info.GetConvex();
		
		
		while (i != arr.end()) {

			i->y -= 3;

			if (i->y <= 0 - i->scale_y * 128. || i->x < -10000) {
				j = i;
				i++; 
				arr.erase(j);
			}else
				i++;

		}
		

		i = arr.begin();

		while (i != arr.end()) {

			i->y -= 3;

			if (Collision(ship, i->GetConvex())) {
				this->clear();
				break;
			}

			i++;
		}

	}

	void paint(HDC mMainDC){

		HDC AstroDC = CreateCompatibleDC(mMainDC);

		std::list<astro>::iterator i = arr.begin();

		while (i != arr.end()) {

			SelectObject(AstroDC, i->bmp);

			GdiTransparentBlt(mMainDC, i->x, i->y, 128*i->scale_x, 128*i->scale_y, AstroDC, 0, 0, 128, 128, RGB(0, 255, 0));

			i++;
		}

		DeleteDC(AstroDC);

	}

	void clear() {

		game_info.stop_fire_lt = true;
		game_info.stop_fire_rt = true;

		arr.clear();

		game_info.fire_int = 1100;

		game_info.score = 1100;

		game_info.score_prev_cnt = game_info.score_cnt;

		game_info.score_cnt = 0;

	}



} astro_list;



// Прототипы функций:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 

bool AA(const POINT &A, const POINT& B, const POINT& C, const POINT& D) {

		double x1 = A.x, y1 = A.y, x2 = B.x, y2 = B.y, x3 = C.x, y3 = C.y, x4 = D.x, y4 = D.y;
		double Ua, Ub, numerator_a, numerator_b, denominator;

		denominator = (y4 - y3) * (x1 - x2) - (x4 - x3) * (y1 - y2);

		if (denominator == 0) {
			if ((x1 * y2 - x2 * y1) * (x4 - x3) - (x3 * y4 - x4 * y3) * (x2 - x1) == 0 && (x1 * y2 - x2 * y1) * (y4 - y3) - (x3 * y4 - x4 * y3) * (y2 - y1) == 0)
				return true;
			else
				return false;
		}
		else {
			
			numerator_a = (x4 - x2) * (y4 - y3) - (x4 - x3) * (y4 - y2);
			numerator_b = (x1 - x2) * (y4 - y2) - (x4 - x2) * (y1 - y2);
			Ua = numerator_a / denominator;
			Ub = numerator_b / denominator;
			
			if (Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1)
				return true;
			else
				return false;

		}


}

bool Collision(const std::vector <POINT> a, const std::vector <POINT> b) {

	for (int i(1); i < a.size(); i++) {

		for (int j(1); j < b.size(); j++) {

			if (AA(a[i-1], a[i], b[j-1], b[j]))
				return true;

		}

	}

	return false;

}

void Fire() {

	game_info.fire_int = 1100;

	game_info.stop_fire_lt = true;
	game_info.stop_fire_rt = true;

	while (is_firing) {

		while (is_firing && (game_info.stop_fire_lt || game_info.stop_fire_rt)) {
			Sleep(100);
		}

		Sleep(game_info.fire_int);

		if (game_info.fire_int >= 100)
			game_info.fire_int-=5;

		astro_list.push();

	}

}

void Drawing() {

	RECT score_rect;

	HDC BackgrounDC;

	MainDC = GetDC(MainWindow);

	BackgrounDC = CreateCompatibleDC(MainDC);

	HBITMAP hBitmap = CreateCompatibleBitmap(MainDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	MemDC = CreateCompatibleDC(MainDC);

	ReleaseDC(MainWindow, MainDC);

	SelectObject(MemDC, hBitmap);

	HBITMAP hbBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(102));

	HDC DC_move_left_right;

	DC_move_left_right = CreateCompatibleDC(MemDC);

	SelectObject(BackgrounDC, hbBitmap);

	score_rect.left = 0;
	score_rect.right = GetSystemMetrics(SM_CXSCREEN);
	score_rect.top = 200;
	score_rect.bottom = 500;

	sm_x = 0;

	game_info.score = 0;

	std::string str;

	while (is_drawing) {

		sm_x += 1;

		if (sm_x >= 4080)
			sm_x = 0;

		ship_info.move();

		astro_list.move();

		BitBlt(MemDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackgrounDC, sm_x, 0, SRCCOPY);

		ship_info.paint(MemDC);

		astro_list.paint(MemDC);

		SelectObject(DC_move_left_right, bmp_move_left);

		if (game_info.stop_fire_lt)
			GdiTransparentBlt(MemDC, 200, 100, 329, 128, DC_move_left_right, 0, 64, 329, 128, RGB(0, 255, 0));

		SelectObject(DC_move_left_right, bmp_move_right);

		if (game_info.stop_fire_rt)
			GdiTransparentBlt(MemDC, GetSystemMetrics(SM_CXSCREEN) - 539, 100, 329, 128, DC_move_left_right, 0, 64, 329, 128, RGB(0, 255, 0));

		if ((game_info.stop_fire_rt || game_info.stop_fire_lt) && game_info.score > 0) {

			SelectObject(MemDC, hFont);

			SetBkMode(MemDC, TRANSPARENT);

			SetTextColor(MemDC, RGB(255, 255, 255));

			str = "YOU LOSE\n\rYour score:\t" + std::to_string(game_info.score_prev_cnt);

			DrawText(MemDC, str.c_str(), str.size(), &score_rect, DT_CENTER);

			game_info.score--;

		}

		RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

		Sleep(42);

	}

	DeleteDC(DC_move_left_right);
	DeleteDC(BackgrounDC);

	DeleteObject(hbBitmap);
	DeleteObject(hBitmap);

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	hInst = hInstance;

	is_drawing = true;
	is_firing = true;

	std::thread drawing(Drawing);
	std::thread firing(Fire);


	MSG msg;

	{

		WNDCLASSEX wcex;

		HBRUSH bBrush = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(101)));

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = NULL;
		wcex.lpfnWndProc = (WNDPROC)WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(112));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = bBrush;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = NULL;

		RegisterClassEx(&wcex);

		DEVMODE D_M;

		D_M.dmSize = sizeof(DEVMODE);
		D_M.dmPelsHeight =  768;
		D_M.dmPelsWidth =  1360;
		D_M.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;

		ChangeDisplaySettings(&D_M, CDS_FULLSCREEN);

		MainWindow = CreateWindow(
			szWindowClass,
			szTitle,
			WS_POPUP | WS_VISIBLE,
			0,
			0,
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CXSCREEN),
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

	is_drawing = false;
	is_firing = false;

	drawing.join();
	firing.join();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	

	switch (message)
	{
	case WM_PAINT:

		MainDC = BeginPaint(hWnd, &ps);

		BitBlt(MainDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), MemDC, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY: 

		PostQuitMessage(0);

		break;

	case WM_CREATE:

		GetClientRect(MainWindow, &client_rect);

		ship_info.no_Fly = LoadBitmap(hInst, MAKEINTRESOURCE(103));
		ship_info.Fly = LoadBitmap(hInst, MAKEINTRESOURCE(104));
		ship_info.Fly_lft = LoadBitmap(hInst, MAKEINTRESOURCE(105));
		ship_info.Fly_rt = LoadBitmap(hInst, MAKEINTRESOURCE(106));

		astro_info.bmp1 = LoadBitmap(hInst, MAKEINTRESOURCE(107));
		astro_info.bmp2 = LoadBitmap(hInst, MAKEINTRESOURCE(108));
		astro_info.bmp3 = LoadBitmap(hInst, MAKEINTRESOURCE(109));

		bmp_move_left = LoadBitmap(hInst, MAKEINTRESOURCE(110));
		bmp_move_right = LoadBitmap(hInst, MAKEINTRESOURCE(111));

		astro_info.pool_convexes();

		hFont = CreateFont(75, 50, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

