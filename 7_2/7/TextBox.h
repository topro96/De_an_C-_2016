#pragma once
#include "Button.h"

enum InputStatus
{
	None,Enter, Up, Down, Left, Right, Mouse, Tab
};

class TextBox :public Button
{

	InputStatus status; //trang thai khi nhap xong

public:

	void OutTextChange(); //xuat theo kieu

	void Input(int &mouseX, int &mouseY);
	
	void InputNumber(int &mouseX, int &mouseY, const int lengthMax);

	void OutPassWord(); //xuat theo ****

	void InputPassWord(int &mouseX, int &mouseY);

	void Draw();
	
	void DrawPassWord();

	InputStatus getStatus() { return status; } void setStatus(InputStatus x) { status = x; } //get set status

	TextBox();

	TextBox(int X1, int Y1, int X2, int Y2, int Color1, int Color2, char Text[30], int CharSize, int Font, int FrameSize,int FrameColor, int Length);
	~TextBox();
};

