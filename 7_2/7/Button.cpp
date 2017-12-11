#include "Button.h"

int frameFont = 0;

void Button::DrawFrame()
{
	setfillstyle(1, color); //to mau cho hinh chu nhat
	bar(x1, y1, x2, y2); //hinh chu nhat
	setcolor(frameColor);
	setlinestyle(frameFont, 0, frameSize);
	rectangle(x1, y1, x2 - 1, y2 -1); //khung hình chử nhật
	
}

void Button::OutTextBetween()
{
	settextstyle(font, 0, charSize); //cài cho chuỗi
	int textHight = textheight(_strdup(text.c_str())); //lay chieu cao  text
	int textWidth = textwidth(_strdup(text.c_str())); //lay chieu rong
	setcolor(textColor);
	setbkcolor(color);
	outtextxy(x1 + (x2 - x1 - textWidth) / 2, y1 + (y2 - y1 - textHight) / 2, _strdup(text.c_str()));
}

void Button::OutTextLeft()
{
	setbkcolor(color);
	setcolor(textColor);
	settextstyle(font, 0, charSize); //cài cho chuỗi
	int textHight = textheight(_strdup(text.c_str())); //lay chieu cao  text
	int textWidth = textwidth(_strdup(text.c_str())); //lay chieu rong
	outtextxy(x1 + 5, y1 + (y2 - y1 - textHight) / 2, _strdup(text.c_str()));
}

void Button::DrawBetween()
{
	DrawFrame();
	OutTextBetween();
}

void Button::DrawLeft()
{
	DrawFrame();
	OutTextLeft();
}

void Button::Selected(const int fontOutText)
{
	checkMouse = true;
	color = color2;
	frameFont = 2;
	if (fontOutText == 0)
	{
		Draw();
	}
	else
	{
		DrawFrame();
		OutTextLeft();
	}
}

void Button::UnSelected(const int fontOutText)
{
	color = color1;
	frameFont = 0;
	if (fontOutText == 0)
	{
		Draw();
	}
	else
	{
		DrawFrame();
		OutTextLeft();
	}
	checkMouse = false;
}

bool Button::CheckMouseMove(const int fontOutText)
{
	if (mousex() > x1 && mousex() < x2 && mousey() > y1 && mousey() < y2)
	{
		if (checkMouse == false)
		{
			Selected(fontOutText);
		}
	}
	else
		if (checkMouse == true)
		{
			UnSelected(fontOutText);
		}
	return checkMouse;
}

bool Button::CheckMouseClick(const int MouseX,const int MouseY)
{
	return MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2 ? true : false;	
}

bool Button::CheckEmpty()
{
	if (text.length() > 0)
		return false;
	return true;
}

void Button::Init(int X1, int Y1, int X2, int Y2,int TextColor, int Color1, int Color2, string Text, int CharSize, int Font, int FrameSize, int FrameColor, int Length)
{
	x1 = X1; y1 = Y1;
	x2 = X2; y2 = Y2;
	textColor = TextColor; color1 = Color1; color2 = Color2; color = color1;
	text = Text; charSize = CharSize; length = Length;
	font = Font;
	frameSize = FrameSize; frameColor = FrameColor;
	checkMouse = false;
}


Button::Button()
{
	frameFont = 0;
}

Button::Button(int X1, int Y1, int X2, int Y2, int Color1, int Color2, string Text, int CharSize, int Font, int SizeFrame, int FrameColor)
{
	x1 = X1; y1 = Y1;
	x2 = X2; y2 = Y2;
	color1 = Color1; color2 = Color2; color = color1;
	text= Text; charSize = CharSize;
	font = Font;
	frameSize = SizeFrame;
	frameColor = FrameColor;
	checkMouse = false;
	frameFont = 0;
}


Button::~Button()
{
}
