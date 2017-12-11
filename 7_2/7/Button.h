#pragma once
#include <string.h>
#include "graphics.h"
#include "Scanner.h"
#pragma comment(lib, "graphics.lib")

class Button :public Scanner
{
protected:
	int x1, y1; //toa do diem trai tren cua button
	int x2, y2; //toa do diem phai duoi cua button
	int color, color1, color2; //mau duoc chon, mau ban dau va mau khi co event
	string text; //chuoi hien thi
	int charSize; //do lon cua chu hien thi
	int font; //kieu chu
	int frameSize; //size của khung button
	int frameColor; //mau khung
	bool checkMouse;
	int textColor;
	int length; //do dai chuoi toi da cho phep

public:

	 void DrawFrame(); //ve khung button
	void OutTextBetween(); //out text o phia  giua
	void OutTextLeft(); //out text o phia trai

	void DrawBetween(); //ve ca khung va chu o giua
	void DrawLeft(); //ve ca khung va chu
	 void Draw()
	{
		DrawFrame();
		OutTextBetween();
	}
	 void Selected(const int fontOutText);
	void UnSelected(const int fontOutText);

	bool CheckMouseMove(const int fontOutText); //xem con tro chuot co dang nam trong button hay khong, font la xuat giua hay trai... 0 la giua 1 la trai
	bool CheckMouseClick(const int MouseX,const int MouseY); //button co duoc click hay ko

	bool CheckEmpty();

	void Init(int X1, int Y1, int X2, int Y2,int TextColor, int Color1, int Color2, string Text, int CharSize, int Font, int FrameSize, int FrameColor, int Length);

	string getText() { return text; } void setText(string x) { text = x; } //get set text

	bool getCheckMouse() { return checkMouse; } void setCheckMouse(bool CheckMouse) { checkMouse = CheckMouse; }

	

	Button();
	Button(int X1, int Y1, int X2, int Y2, int Color1, int Color2,string Text, int CharSize, int Font, int FrameSize, int FrameColor);
	~Button();
};

