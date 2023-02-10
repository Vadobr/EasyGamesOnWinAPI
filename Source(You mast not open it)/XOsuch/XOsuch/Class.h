#pragma once
#include "Windows.h"
#include <vector>

int x_scroll = 0, y_scroll = 0;

int win_condition;

enum Q{

	x = 0,
	o = 1,
	none = 3

}turn;

struct {

	HBITMAP x[8] = {

		(HBITMAP)LoadImage(NULL, "Imgs\\X1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X7.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\X8.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)

	};

	HBITMAP o[6]{

		(HBITMAP)LoadImage(NULL, "Imgs\\O1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\O2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\O3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\O4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\O5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),
		(HBITMAP)LoadImage(NULL, "Imgs\\O6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),

	};

	HBITMAP left_down = (HBITMAP)LoadImage(NULL, "Imgs\\LD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP right_down = (HBITMAP)LoadImage(NULL, "Imgs\\RD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP left = (HBITMAP)LoadImage(NULL, "Imgs\\RT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP down = (HBITMAP)LoadImage(NULL, "Imgs\\DWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	HBITMAP drops = (HBITMAP)LoadImage(NULL, "Imgs\\Drops.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	HBRUSH bBrush = CreatePatternBrush((HBITMAP)LoadImage(NULL, "Imgs\\Back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

}Bitmapof;

class Sprite {

public:

	int x;
	int y;

	bool isitdrop;

	virtual void Print(HDC hdc, int x, int y) = 0;

	Sprite(int x, int y) {

		this->x = x;
		this->y = y;

		isitdrop = false;

	}

	Sprite(int x, int y, bool iid) {

		this->x = x;
		this->y = y;

		isitdrop = iid;

	}

};

class SpriteX : public Sprite {

public:

	int type;

	SpriteX(int x, int y, int type) : Sprite(x, y){
		
		if (type < 8)
			this->type = type;
		else
			this->type = 2;
	
	}

	void Print(HDC hdc, int x, int y) {

		HDC MemDC = CreateCompatibleDC(hdc);

		SelectObject(MemDC, Bitmapof.x[this->type]);

		GdiTransparentBlt(hdc, x, y, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

		DeleteDC(MemDC);

	}


};

class SpriteO : public Sprite {

public:

	int type;

	SpriteO(int x, int y, int type) : Sprite(x, y) {

		if (type < 6) {

			this->type = type;

		}
		else {

			this->type = 1;

		}

	}

	void Print(HDC hdc, int x, int y) {

		HDC MemDC = CreateCompatibleDC(hdc);

		SelectObject(MemDC, Bitmapof.o[this->type]);

		GdiTransparentBlt(hdc, x, y, 50, 50, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

		DeleteDC(MemDC);

	}

};

class SpriteDrop : public Sprite {

public:

	SpriteDrop(int x, int y) : Sprite(x, y, true) {}

	void Print(HDC hdc, int x, int y) {

		HDC MemDC = CreateCompatibleDC(hdc);

		SelectObject(MemDC, Bitmapof.drops);

		GdiTransparentBlt(hdc, x, y, 400, 400, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

		DeleteDC(MemDC);

	}

};

class SpriteWin : public Sprite {

public:

#define dwn_type 0
#define rt_type 1
#define ld_type 2
#define rd_type 3

	int type;

	SpriteWin(int x, int y, int type) : Sprite(x- 25, y - 25){

		if (type < 4) {

			this->type = type;

		}
		else {

			type = 0;

		}
	
	}

	void Print(HDC hdc, int x, int y) {

		HDC MemDC = CreateCompatibleDC(hdc);

		switch (type) {

		case dwn_type:

			SelectObject(MemDC, Bitmapof.down);

			GdiTransparentBlt(hdc, x, y, 50, 250, MemDC, 150, 0, 75, 400, RGB(0, 255, 0));

			break;

		case rt_type:

			SelectObject(MemDC, Bitmapof.left);

			GdiTransparentBlt(hdc, x, y - 20, 250, 50, MemDC, 0, 150, 400, 75, RGB(0, 255, 0));

			break;

		case rd_type:

			SelectObject(MemDC, Bitmapof.right_down);

			GdiTransparentBlt(hdc, x, y, 250, 250, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

			break;

		case ld_type:

			SelectObject(MemDC, Bitmapof.left_down);

			GdiTransparentBlt(hdc, x - 200, y, 250, 250, MemDC, 0, 0, 400, 400, RGB(0, 255, 0));

			break;

		default:

			break;

		}

		DeleteDC(MemDC);

	}

};

class ContainerSprite {

public:

	struct {

		Sprite* sp;

	}Sprite_info;

#define x_type		0
#define o_type		1
#define drop_type	2
#define line_type	3


	void Push_back(int type, int x, int y){
	
		Sprite* newSprite;

		switch (type) {

		case x_type:

			newSprite = new SpriteX(x, y, rand() % 8);

			break;
		case o_type:

			newSprite = new SpriteO(x, y, rand() % 6);

			break;
		case drop_type:

			newSprite = new SpriteDrop(x, y);

			break;

		case line_type:

			newSprite = new SpriteWin(x, y, win_condition);

			break;
		default:
			return;
		}

		arr.push_back(newSprite);

	}

	std::vector <Sprite*> arr;

	void Print(HDC hdc) {

		for (int i(0); i < arr.size(); i++) {

			arr[i]->Print(hdc, arr[i]->x + x_scroll, arr[i]->y + y_scroll);

		}

	}

	void Clear(){
	
		std::vector <Sprite*> cparr;

		for (int i(0); i < arr.size(); i++) {

			if (arr[i]->isitdrop)
				cparr.push_back(arr[i]);
			else
				delete arr[i];

		}

		arr.clear();
	
		arr = cparr;

		turn = Q::x;

	}

	~ContainerSprite(){
	
		for (int i(0); i < arr.size(); i++) {

			delete arr[i];

		}
	
	}

}Arr;

struct Cell {

	int x;
	int y;

	Cell(int x, int y){
	
		this->x = x;
		this->y = y;
	
	}

	Cell(const Cell &Source) {

		this->x = Source.x;

		this->y = Source.y;

	}

	Cell(const POINT &Source) {

		this->x = Source.x;

		this->y = Source.y;

	}

	bool operator < (const Cell& Source) {

		return this->x < Source.x && this->y < Source.y;

	}

	bool operator > (const Cell& Source) {

		return this->x > Source.x && this->y > Source.y;

	}

	bool operator == (const Cell& Source) {
	
	
		return this->x == Source.x && this->y == Source.y;

	}


};

class {

public:

	std::vector <Cell> c_arr;
	std::vector <Q> q_arr;

	void push(Cell a, Q b) {
	
		c_arr.push_back(a);
		q_arr.push_back(b);

	}

	bool count(const Cell& a) {
	
		for (int i(0); i < c_arr.size(); i++) {
		
			if (c_arr[i] == a)
				return true;

		}

		return false;

	}

	Q operator [] (const Cell& a) {

		for (int i(0); i < c_arr.size(); i++) {

			if (c_arr[i] == a)
				return q_arr[i];

		}
	
	}

	void Clear() {

		c_arr.clear();
		q_arr.clear();

	}


}field;

Cell WinPoint(0, 0);

bool is_game_going = true;

bool CheckForWin(Cell newPoint) {

	Cell checker(0, 0);

	bool is_win = false;

	bool is_street;

	int win_count = 5;

	////////////
	
	for(int k(0); k< win_count; k++){
	
		checker.x = newPoint.x - k;
		checker.y = newPoint.y;

		is_street = true;
		for (int i(0); i < win_count; i++) {

			if (field.count(checker)) {
				if (field[checker] != turn) {
					is_street = false;
				}
			}
			else
				is_street = false;

		checker.x++;

		}

		if (is_street)
			break;
	}

	if (is_street) {
		is_win = true;
		win_condition = rt_type;
		WinPoint = checker;
		WinPoint.x -= 5;
	}

	///////////

	for (int k(0); k < win_count; k++) {

		checker.x = newPoint.x;
		checker.y = newPoint.y - k;

		is_street = true;
		for (int i(0); i < win_count; i++) {

			if (field.count(checker)) {
				if (field[checker] != turn) {
					is_street = false;
				}
			}
			else
				is_street = false;

			checker.y++;

		}

		if (is_street)
			break;

	}

	if (is_street) {
		is_win = true;
		win_condition = dwn_type;
		WinPoint = checker;
		WinPoint.y -= 5;
	}

	///////////

	for (int k(0); k < win_count; k++) {

		checker.x = newPoint.x - k;
		checker.y = newPoint.y - k;

		is_street = true;
		for (int i(0); i < win_count; i++) {

			if (field.count(checker)) {
				if (field[checker] != turn) {
					is_street = false;
				}
			}
			else
				is_street = false;

			checker.y++;
			checker.x++;

		}

		if (is_street)
			break;

	}

	if (is_street) {
		is_win = true;
		win_condition = rd_type;
		WinPoint = checker;
		WinPoint.x -= 5;
		WinPoint.y -= 5;
	}

	///////////

	for (int k(0); k < win_count; k++) {

		checker.x = newPoint.x - k;
		checker.y = newPoint.y + k;

		is_street = true;
		for (int i(0); i < win_count; i++) {

			if (field.count(checker)) {
				if (field[checker] != turn) {
					is_street = false;
				}
			}
			else
				is_street = false;

			checker.y--;
			checker.x++;

		}

		if (is_street)
			break;

	}

	if (is_street) {
		is_win = true;
		win_condition = ld_type;
		WinPoint = checker;
		WinPoint.x -= 1;
		WinPoint.y += 1;
	}
	
	////////////

	return is_win;

}
