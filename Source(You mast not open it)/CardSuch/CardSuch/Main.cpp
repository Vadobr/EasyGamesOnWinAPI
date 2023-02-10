#include "windows.h"
#include <vector>

// Глобальны переменные:

HINSTANCE hInst;

LPCTSTR szWindowClass = "szMainWindowClass";
LPCTSTR szTitle = "Kосинка";

HWND MainWindow;

#define other_side 4, 0

struct card_info{

	enum POSITION{

		column,
		buffer_cl,
		buffer_opn,
		win_buffer

	}position;

	int cloumn_number;

	int position_on_steck;

	enum LOCK{

		opened,
		closed

	} lock;

	int x;
	int y;

	int mast;
	int number;

	bool is_flying;

} arr[4][13];

struct {

public:

	struct col_info {

		std::vector <card_info*> stack;

	};

	col_info column[7];

	col_info bufer_closed;
	col_info bufer_opend;

	col_info win_bufer[4];

	int roof[2] = { 50, 218 };
	int floor[2] = { 120, 288 };
	int back[7] = { 59, 145, 230, 316, 402, 482, 572 };
	int face[7] = { 111, 197, 282, 368, 454, 534, 624 };

	int card_width = 50;
	int card_height = 70;

	std::vector <card_info*> flying_card;

} game_info;

// Прототипы функций:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void CreatingMainWindow();

#include <Windows.h>

// Gogo

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

HBRUSH BackBrush;

void CreatingMainWindow() {

	HBITMAP BackBmp = LoadBitmap(hInst, MAKEINTRESOURCE(102));

	BackBrush = CreatePatternBrush(BackBmp);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(104));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = BackBrush;
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
		675,
		600,
		NULL,
		NULL,
		hInst,
		NULL
	);

	ShowWindow(MainWindow, SW_NORMAL);
	UpdateWindow(MainWindow);

	for (int i(0); i < 4; i++) {

		for (int j(0); j < 13; j++) {

			arr[i][j].number = j;
			arr[i][j].mast = i;

		}

	}

}

void PaintTable(HDC hDC) {

	static HBITMAP TableBMP = LoadBitmap(hInst, MAKEINTRESOURCE(103));

	HDC MemDC = CreateCompatibleDC(hDC);

	SelectObject(MemDC, TableBMP);

	BitBlt(hDC, 0, 0, 675, 675, MemDC, 0, 0, SRCCOPY);

	DeleteDC(MemDC);

}

void TestPaint(HDC hdc) {

	HGDIOBJ oldPen;
	HGDIOBJ oldBrush;

	oldBrush = SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	oldPen = SelectObject(hdc, GetStockObject(NULL_PEN));
	
	for (int i(0); i < 7; i++) {

		Rectangle(hdc, game_info.back[i], game_info.roof[0], game_info.back[i] + 10, game_info.roof[0] + 10);
		Rectangle(hdc, game_info.back[i], game_info.roof[1], game_info.back[i] + 10, game_info.roof[1] + 10);

		Rectangle(hdc, game_info.face[i] - 10, game_info.floor[0] - 10, game_info.face[i], game_info.floor[0]);
		Rectangle(hdc, game_info.face[i] - 10, game_info.floor[1] - 10, game_info.face[i], game_info.floor[1]);


	}

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);

}

void RefreshGame();

void GetAreas(LPARAM lParam) {

#define into x >= w1 && x <= w2 && y <= h2 && y >= h1

	RECT client_rect;

	GetClientRect(MainWindow, &client_rect);

	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	int w1, w2;
	int h1, h2;

	{

		if (game_info.flying_card.size() == 1) {

			h1 = game_info.roof[0];
			h2 = game_info.floor[0];

			for (int i(0); i < 4; i++) {

				w1 = game_info.back[i + 3];
				w2 = game_info.face[i + 3];

				if (into) {

					if (game_info.flying_card[0]->number == game_info.win_bufer[i].stack.size()) {

						if (game_info.win_bufer[i].stack.size() == 0) {

							game_info.win_bufer[i].stack.push_back(game_info.flying_card[0]);

							if (game_info.flying_card[0]->position == card_info::POSITION::buffer_opn) {

								game_info.bufer_opend.stack.pop_back();

							}
							if (game_info.flying_card[0]->position == card_info::POSITION::column) {

								game_info.column[game_info.flying_card[0]->cloumn_number].stack.pop_back();

							}

							game_info.flying_card[0]->x = w1;
							game_info.flying_card[0]->y = h1;

						}
						else if (game_info.win_bufer[i].stack[0]->mast == game_info.flying_card[0]->mast) {

							game_info.win_bufer[i].stack.push_back(game_info.flying_card[0]);

							if (game_info.flying_card[0]->position == card_info::POSITION::buffer_opn) {

								game_info.bufer_opend.stack.pop_back();

							}
							if (game_info.flying_card[0]->position == card_info::POSITION::column) {

								game_info.column[game_info.flying_card[0]->cloumn_number].stack.pop_back();

							}

							game_info.flying_card[0]->x = w1;
							game_info.flying_card[0]->y = h1;

						}
					

						game_info.flying_card[0]->is_flying = false;

						game_info.flying_card.clear();


					
						

					}

					RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

					return;

				}
			}

		}

		if (game_info.flying_card.size() > 0 && game_info.flying_card[0]->position == card_info::POSITION::buffer_opn) {

			for (int i(0); i < 7; i++) {

				w1 = game_info.back[i];
				w2 = game_info.face[i];

				h1 = game_info.roof[1] + game_info.column[i].stack.size() * 15;
				h2 = game_info.floor[1] + game_info.column[i].stack.size() * 15;

				if (into) {

					if (game_info.flying_card[0]->number == 12 && game_info.column[i].stack.size() == 0) {

						game_info.flying_card[0]->is_flying = false;

						game_info.column[i].stack.push_back(game_info.flying_card[0]);

						game_info.flying_card[0]->position = card_info::POSITION::column;

						game_info.flying_card[0]->cloumn_number = i;

						game_info.flying_card[0]->position_on_steck = 0;

						game_info.flying_card[0]->x = game_info.back[i];

						game_info.flying_card[0]->y = game_info.roof[1];

						game_info.bufer_opend.stack.pop_back();

						game_info.flying_card.clear();

						RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

						return;

					}
					else if (
						game_info.column[i].stack.size() > 0 &&
						game_info.flying_card[0]->number == game_info.column[i].stack[game_info.column[i].stack.size() - 1]->number - 1 &&
						game_info.flying_card[0]->mast % 2 != game_info.column[i].stack[game_info.column[i].stack.size() - 1]->mast % 2
						) {

						game_info.flying_card[0]->is_flying = false;

						game_info.column[i].stack.push_back(game_info.flying_card[0]);

						game_info.flying_card[0]->position = card_info::POSITION::column;

						game_info.flying_card[0]->cloumn_number = i;

						game_info.flying_card[0]->position_on_steck = game_info.column[i].stack.size() - 1;

						game_info.flying_card[0]->x = game_info.back[i];

						game_info.flying_card[0]->y = game_info.roof[1] + game_info.flying_card[0]->position_on_steck*15;

						game_info.bufer_opend.stack.pop_back();

						game_info.flying_card.clear();

						RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

						return;

					}
					else {

						game_info.flying_card[0]->is_flying = false;
						game_info.flying_card.clear();

						RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

						return;

					}


				}

			}

		}

		for (int i(0); i < 7; i++) {

			w1 = game_info.back[i];
			w2 = game_info.face[i];

			h1 = game_info.roof[1];
			h2 = game_info.floor[1] + game_info.column[i].stack.size() * 15;

			if (into) {

				h2 = game_info.floor[1];
				
				if (
					game_info.flying_card.size() > 0 &&
					game_info.flying_card[0]->number == 12 &&
					game_info.column[i].stack.size() == 0 
					) {

					if (game_info.column[game_info.flying_card[0]->cloumn_number].stack.size() > 1) {

						game_info.column[game_info.flying_card[0]->cloumn_number].stack[game_info.column[game_info.flying_card[0]->cloumn_number].stack.size() - 2]->lock = card_info::LOCK::opened;

					}

					for (int k(0); k < game_info.flying_card.size(); k++) {

						game_info.flying_card[k]->is_flying = false;

						game_info.column[game_info.flying_card[0]->cloumn_number].stack.pop_back();

					}

					for (int k(0); k < game_info.flying_card.size(); k++) {

						game_info.flying_card[k]->position_on_steck = game_info.column[i].stack.size() + k;

						game_info.flying_card[k]->cloumn_number = i;

						game_info.column[i].stack.push_back(game_info.flying_card[k]);

						game_info.flying_card[k]->x = game_info.back[i];
						game_info.flying_card[k]->y = game_info.roof[1] + game_info.flying_card[k]->position_on_steck * 15;

					}

					game_info.flying_card.clear();

					RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

					return;
				}


				for (int j = game_info.column[i].stack.size() - 1; j >= 0; j--) {

					h1 = game_info.roof[1] + j * 15;
					h2 = game_info.floor[1] + j * 15;

					if (into) {

						if (game_info.flying_card.size() == 0) {

							if (game_info.column[i].stack[j]->lock == card_info::LOCK::opened) {

								for (int k(j); k < game_info.column[i].stack.size(); k++) {

									game_info.flying_card.push_back(game_info.column[i].stack[k]);

									game_info.column[i].stack[k]->is_flying = true;

								}

								RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

							}

						}
						else {

							if (
								game_info.flying_card[0]->number == game_info.column[i].stack[j]->number - 1 &&
								game_info.flying_card[0]->mast % 2 != game_info.column[i].stack[j]->mast % 2
								) {

								if (game_info.column[game_info.flying_card[0]->cloumn_number].stack.size() > 1) {

									for (int d(0); d <= game_info.flying_card.size(); d++) {

										game_info.column[game_info.flying_card[0]->cloumn_number].stack[game_info.column[game_info.flying_card[0]->cloumn_number].stack.size() - 2]->lock = card_info::LOCK::opened;
									
									}
								}

								for (int k(0); k < game_info.flying_card.size(); k++) {

									game_info.flying_card[k]->is_flying = false;

									game_info.column[game_info.flying_card[0]->cloumn_number].stack.pop_back();

								}

								for (int k(0); k < game_info.flying_card.size(); k++) {

									game_info.flying_card[k]->position_on_steck = game_info.column[i].stack.size() + k;

									game_info.flying_card[k]->cloumn_number = i;

									game_info.column[i].stack.push_back(game_info.flying_card[k]);

									game_info.flying_card[k]->x = game_info.back[i];
									game_info.flying_card[k]->y = game_info.roof[1] + game_info.flying_card[k]->position_on_steck * 15;

								}

								game_info.flying_card.clear();

								RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);
							}
							else {

								for (int i(0); i < game_info.flying_card.size(); i++) {

									game_info.flying_card[i]->is_flying = false;

								}
								game_info.flying_card.clear();
								RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

							}

						}

						return;

					}

				}

			}

		}

	}

	{
	{

		w1 = client_rect.left;
		w2 = client_rect.right + game_info.card_width;

		h1 = client_rect.bottom - game_info.card_height;
		h2 = client_rect.bottom;

		if (into) {

			RefreshGame();

			return;

		}

	}
	}

	{

		h1 = game_info.roof[0];
		h2 = game_info.floor[0];

		w1 = game_info.back[0];
		w2 = game_info.face[0];

		if (into) {
		
			if (game_info.bufer_closed.stack.size() > 0) {

				game_info.bufer_closed.stack[game_info.bufer_closed.stack.size() - 1]->lock = card_info::LOCK::opened;

				game_info.bufer_closed.stack[game_info.bufer_closed.stack.size() - 1]->x = game_info.back[1];

				game_info.bufer_closed.stack[game_info.bufer_closed.stack.size() - 1]->position = card_info::POSITION::buffer_opn;

				game_info.bufer_opend.stack.push_back(game_info.bufer_closed.stack[game_info.bufer_closed.stack.size() - 1]);

				game_info.bufer_closed.stack.pop_back();



			}
			else {

				while(game_info.bufer_opend.stack.size() > 0){

					game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->x = game_info.back[0];

					game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->position = card_info::POSITION::buffer_cl;

					game_info.bufer_closed.stack.push_back(game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]);

					game_info.bufer_opend.stack.pop_back();

				}

			}

			RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

			return;

		}

	}

	{
	

		h1 = game_info.roof[0];
		h2 = game_info.floor[0];

		w1 = game_info.back[1];
		w2 = game_info.face[1];

		if (into) {

			if (game_info.bufer_opend.stack.size() > 0 && game_info.flying_card.size() == 0) {

				game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->is_flying = true;

				game_info.flying_card.push_back(game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]);

			}

			RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

			return;

		}
	
	}

	{
	
		for (int i(0); i < game_info.flying_card.size(); i++) {

			game_info.flying_card[i]->is_flying = false;

		}

		game_info.flying_card.clear();
	
		RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

	}

}

bool RandomPosition(card_info& sr){

	int t = rand() % 14;

	if (t <= 6) {

		if (game_info.column[t].stack.size() < t + 1) {

			game_info.column[t].stack.push_back(&sr);

			sr.position_on_steck = game_info.column[t].stack.size() - 1;
			sr.position = card_info::POSITION::column;

			sr.cloumn_number = t;

			if (game_info.column[t].stack.size() == t + 1) {

				sr.lock = card_info::LOCK::opened;

			}
			else {

				sr.lock = card_info::LOCK::closed;

			}

			return false;

		}
		else {

			return true;

		}

	}else{

		if (game_info.bufer_closed.stack.size() < 24) {

			sr.position_on_steck = game_info.bufer_closed.stack.size() - 1;
			sr.position = card_info::POSITION::buffer_cl;

			game_info.bufer_closed.stack.push_back(&sr);

			sr.lock = card_info::LOCK::closed;

			return false;
		
		}
		else{
		
			return true;

		}

	}

	return true;


}

void RefreshGame() {

	for (int i(0); i < 4; i++) {
		for (int j(0); j < 13; j++) {
			arr[i][j].is_flying = false;
		}
	}

	for (int i(0); i < 7; i++) {

		game_info.column[i].stack.clear();

	}

	for (int i(0); i < 4; i++) {

		game_info.win_bufer[i].stack.clear();

	}

	game_info.bufer_opend.stack.clear();
	game_info.bufer_closed.stack.clear();

	for (int i(0); i < 4; i++) {

		for (int j(0); j < 13; j++) {

			while (RandomPosition(arr[i][j]));

		}

	}

	for (int i(0); i < 7; i++) {

		for (int j = 0; j < game_info.column[i].stack.size(); j++) {

			game_info.column[i].stack[j]->x = game_info.back[i];

			game_info.column[i].stack[j]->y = game_info.roof[1] + j*15;

		}

	}

	int rd;

	for (int i(0); i < game_info.bufer_closed.stack.size(); i++) {

		rd = rand() % 24;

		std::swap(game_info.bufer_closed.stack[i], game_info.bufer_closed.stack[rd]);

	}

	for (int i(0); i < game_info.bufer_closed.stack.size(); i++) {

		game_info.bufer_closed.stack[i]->x = game_info.back[0];
		game_info.bufer_closed.stack[i]->y = game_info.roof[0];

	}


	RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

}

typedef void(*DrawCardFunc)(HDC, WORD, WORD, int, int);

void PaintALLCards(HDC hdc, DrawCardFunc DrawCard) {

	for (int i(0); i < 7; i++) {

		for (int j = 0; j < game_info.column[i].stack.size(); j++) {

			game_info.column[i].stack[j]->x = game_info.back[i];

			game_info.column[i].stack[j]->y = game_info.roof[1] + j * 15;

		}

	}



#define PerfectCardDrawing(mast, number, x, y){\
\
if(!arr[mast][number].is_flying){\
\
if(arr[mast][number].lock == card_info::LOCK::opened)\
\
DrawCard(hdc, mast, number, x, y);\
\
if (arr[mast][number].lock == card_info::LOCK::closed)\
\
DrawCard(hdc, other_side, x, y);\
\
}\
\
}

	for (int i(0); i < 7; i++) {

		if(game_info.column[i].stack.size() > 0)
			game_info.column[i].stack[game_info.column[i].stack.size() - 1]->lock = card_info::LOCK::opened;

		for (int j(0); j < game_info.column[i].stack.size(); j++) {

			PerfectCardDrawing(game_info.column[i].stack[j]->mast, game_info.column[i].stack[j]->number, game_info.column[i].stack[j]->x, game_info.column[i].stack[j]->y);

		}

	}

	if (game_info.bufer_closed.stack.size() > 0) {

		DrawCard(hdc, other_side, game_info.bufer_closed.stack[0]->x, game_info.bufer_closed.stack[0]->y);

	}

	if (game_info.bufer_opend.stack.size() > 0) {
		
		if (game_info.bufer_opend.stack.size() > 1) {

			DrawCard(hdc, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 2]->mast, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 2]->number, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 2]->x, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 2]->y);

		}

		PerfectCardDrawing(game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->mast, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->number, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->x, game_info.bufer_opend.stack[game_info.bufer_opend.stack.size() - 1]->y);

	}

	for (int i(0); i < 4; i++) {

		if (game_info.win_bufer[i].stack.size() > 0) {

			DrawCard(hdc, game_info.win_bufer[i].stack[game_info.win_bufer[i].stack.size() - 1]->mast, game_info.win_bufer[i].stack[game_info.win_bufer[i].stack.size() - 1]->number, game_info.win_bufer[i].stack[game_info.win_bufer[i].stack.size() - 1]->x, game_info.win_bufer[i].stack[game_info.win_bufer[i].stack.size() - 1]->y);

		}

	}

}

void Redrawing(HDC MainDC, DrawCardFunc DrawCard){

	RECT cr;

	GetClientRect(MainWindow, &cr);

	HDC hdc = CreateCompatibleDC(MainDC);

	HBITMAP hBitmap = CreateCompatibleBitmap(MainDC, cr.right - cr.left, cr.bottom - cr.top);

	SelectObject(hdc, hBitmap);

	SelectObject(hdc, GetStockObject(NULL_PEN));

	SelectObject(hdc, BackBrush);


	//////////

	Rectangle(hdc, cr.left, cr.top, cr.right - cr.left, cr.bottom - cr.top);

	POINT cursor_pos;

	GetCursorPos(&cursor_pos);

	PaintTable(hdc);

	DrawCard(hdc, other_side, cr.left, cr.bottom - game_info.card_height);

	PaintALLCards(hdc, DrawCard);

	if (game_info.flying_card.size() > 0) {

		GetWindowRect(MainWindow, &cr);

		cursor_pos.x -= cr.left + 30;
		cursor_pos.y -= cr.top + 40;
		for (int i(0); i < game_info.flying_card.size(); i++) {

			DrawCard(hdc, game_info.flying_card[i]->mast, game_info.flying_card[i]->number, cursor_pos.x, cursor_pos.y + i * 15);

		}
		GetClientRect(MainWindow, &cr);

	}


	/////

	BitBlt(MainDC, 0, 0, cr.right - cr.left, cr.bottom - cr.top, hdc, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);

	DeleteDC(hdc);


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	RECT client_rect;

	HDC hdc;

	static HMODULE hmd;

	static DrawCardFunc DrawCard;

	bool is_card_on_hand = false;

	card_info* card_on_hand = NULL;

	switch (message)
	{
	case WM_PAINT:

		GetClientRect(hWnd, &client_rect);

		hdc = BeginPaint(hWnd, &ps);

		Redrawing(hdc, DrawCard);

//		TestPaint(hdc);

		EndPaint(hWnd, &ps);

		break;

	case WM_KEYDOWN:

		if (GetAsyncKeyState(VK_ESCAPE)) {

			if (game_info.flying_card.size() > 0) {

				for (int i(0); i < game_info.flying_card.size(); i++) {

					game_info.flying_card[i]->is_flying = false;
				
				}
				game_info.flying_card.clear();
				RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);
			}
		}

		break;

	case WM_MOUSEMOVE:

		if (game_info.flying_card.size() > 0)
			RedrawWindow(MainWindow, NULL, NULL, RDW_INVALIDATE);

		break;

	case WM_LBUTTONDOWN:

		GetAreas(lParam);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		FreeLibrary(hmd);

		break;

	case WM_CREATE:

		hmd = LoadLibrary("cards32.dll");

		DrawCard = (DrawCardFunc)GetProcAddress(hmd, "DrawCard");

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

