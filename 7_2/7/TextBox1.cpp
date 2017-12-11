#include "TextBox1.h"

int TextBox1::xCursor = 0;
int TextBox1::y1Cursor = 0;
int TextBox1::y2Cursor = 0;
int TextBox1::stopCursor = 1;
int TextBox1::pauseCursor = 0;
int TextBox1::colorCursor = 0;
int TextBox1::colorBg = 0;
int TextBox1::clickInTxb = 0;


void TextBox1::Draw()
{
	DrawFrame();
	ShowTextDefault();
	outtextxy(textX1, y1, &showText[0]);
	StartCursor();
	
}


 void TextBox1::DrawFrame()
{
	 if (status<=0)
		DrawFrame( color2);
	 else
		DrawFrame(color1);
}

 void TextBox1::DrawCurSor() {
	
	int a = 1;
	while (stopCursor)
	{
		if (pauseCursor)
		{
			
			if (a == 1) //hiện color1 là màu chữ,color2 là màu nền
			{
				setcolor(colorCursor);
				line(xCursor, y1Cursor, xCursor, y2Cursor);
				a = 0;
			}
			else //ẩn
			{
				setcolor(colorBg);
				line(xCursor, y1Cursor, xCursor, y2Cursor);
				a = 1;
			}
		}
		Sleep(250);
	}
}

void TextBox1::StartCursor() {
	thread CS(&TextBox1::DrawCurSor);
	if (CS.joinable())
		CS.detach();
}

void TextBox1::StopCursor() {
	stopCursor = 0;
}

int TextBox1::ClickInThis(int x, int y) {
	if (x > x1&&x<x2&&y>y1&&y < y2)//kích vào trong txb
	{
		if (clickInTxb == 1)
		{
			status = 2;//trạng thái đã click vào rồi
			clickInTxb = 2;
		}
		else
		{
			status = 1;//trạng thái đã click vào rồi
			clickInTxb = 1;
		}
		y1Cursor = y1 + le;
		y2Cursor = y2 - le;
		colorCursor = color1;
		colorBg = color2;
		if (textwidth(&showText[0]) > x - x1)//nếu click vào chuỗi kí tự
		{
			int j; string t;
			for (j = i; j <= endShowText; j++)//lấy chuỗi từ i->j sao cho chuỗi đó là chuỗi đàu tiên có textwidth > x - x1
			{									//=> j-1 là vị trí của con trỏ tương ứng trong str
				t.push_back(str[j]);
				if (textwidth(&t[0]) > x - x1)
					break;
			}
			cursor = j - 1;//con trỏ = j-1
			//cập nhật tọa độ con trỏ hiện trên mà hình
			CopyStr(temp, str, i, cursor);
			xCursor = textX1 + textwidth(&temp[0]);
		}
		else// nếu click vào trong txb nhưng nàm ngoài chuỗi thì cho con trỏ về cuối chuỗi
		{
			if (showText.size() != 0)
			{
				cursor = endShowText;
				CopyStr(temp, str, i, cursor);
				xCursor = textX1 + textwidth(&temp[0]);
			}
			else
			{
				xCursor = x1 + le;
			}

		}
		//vẽ lại txb
		DrawFrame(color1);
		setbkcolor(color1);
		setcolor(color2);

		settextstyle(font, 0, charSize);
		ShowTextS();
		return 1;
	}
	else //click ngoài txb
	{
		if (status > 0) {
			DrawFrame(color2);
			setbkcolor(color2);
			setcolor(color1);
			ShowTextDefault();
			outtextxy(textX1, y1 + (y2 - y1 - textheight(&str[0])) / 2, &showText[0]);
		}

		if (status == clickInTxb)
			pauseCursor = 0;
		status = 0;
		return 0;
	}
	
}

void TextBox1::KeyL() {
	if (xCursor != textX1)//tọa độ con trỏ chưa ở đầu txb
	{
		if (cursor > 0) //nếu con trỏ chưa trỏ về 0 thì trừ đi 1
		{
			cursor--;
			CopyStr(temp, str, i, cursor);
			xCursor = textX1 + textwidth(&temp[0]);
		}
		else //nếu con trỏ bằng 0
		{
			xCursor = textX1;//cho tọa độ con trỏ nằm ở đầu txb
			cursor = -1;
		}
	}
	else//tọa độ con trỏ nằm ở đầu txb
	{
		if (i != 0)
		{
			cursor--;
			i--;
			endShowText--;
		}

	}
}

void TextBox1::KeyR()
{
	if (cursor < endShowText)
	{
		cursor++;
		CopyStr(temp, str, i, cursor);
		xCursor = textX1 + textwidth(&temp[0]);
	}
	else
	{
		if (cursor < str.size() - 1)
		{
			cursor++;
			i++;
			endShowText++;
		}
	}
}

void TextBox1::InPutChar( char c) {
	cursor++;
	str.insert(cursor, 1, c);
	CopyStr(temp, str, i, cursor);
	if (textwidth(&str[0]) < textX2 - textX1)//str nam trong txb
	{
		endShowText = str.size() - 1;
	}
	else//str lớn hơn txb
	{
		if (textwidth(&temp[0]) >= textX2 - textX1)//con tro dang nam o cuoi
		{
			endShowText++;
			i++;
			temp.erase(0, 1);
		}
	}
	xCursor = textX1 + textwidth(&temp[0]);
}

void TextBox1::KBackSpace() {
	if (cursor >= 0) 
	{
		if (i > 0)
			i--;
		if (cursor == 0) 
			xCursor = textX1;
			
		endShowText--;
		str.erase(cursor, 1);
		cursor--;
		CopyStr(temp, str, i, cursor);
		xCursor = textX1 + textwidth(&temp[0]);
		
	}
}

void TextBox1::KDelete()
{
	int l = str.size() - 1;
	if (cursor < l)
	{
		
		if (i > 0)
		{
			if (cursor != endShowText)
			{
				i--;
				endShowText--;
				CopyStr(temp, str, i, cursor);
				xCursor = textX1 + textwidth(&temp[0]);
			}
		}
		else
			if (str.size()-1 == endShowText)
				endShowText--;
		str.erase(cursor + 1, 1);
	}
}

void TextBox1::Input(char c) {

	if (status) {
		switch (c)
		{
		case 8: //backspace
		{
			KBackSpace();
			break;
		}
		case 13: //enter
		{
			Enter();
			break;
		}
		case 0: {
			c = getch();
			if (c == 75) //TRAI
				KeyL();
			if (c == 77) //phai
				KeyR();
			if (c == 83)//delete
				KDelete();
			break;
		}
		default:
		{
			if (length >= 0) {
				if (str.size() < length)
					InPutChar(c);
			}
			else
			{
				InPutChar(c);
			}
			break;
		}
		}
		CopyStr(showText, str, i, endShowText);
		DrawFrame();
		setbkcolor(color1);
		setcolor(color2);
		ShowTextS();
	}
}

TextBox1::TextBox1()
{
	
}

TextBox1::TextBox1(int X1, int Y1, int X2, int Y2, int Color1, int Color2, int CharSize, int Font, int FrameSize,int FrameColor,int Style, int Length)
{
	StartCursor();
	style = Style;
	x1 = X1; y1 = Y1;
	x2 = X2; y2 = Y2;
	color1 = Color1; color2 = Color2;
	 charSize = CharSize; length = Length;
	font = Font;
	frameSize = FrameSize; frameColor = FrameColor;
	status = 0;
	textX1 = x1 + le, textX2 = x2 - le;
	
}

TextBox1::~TextBox1()
{
}

void CopyStr(string & a, string b, int i, int e) {
	a.clear();
	for (int j = i; j <= e; j++)
	{
		a.push_back(b[j]);
	}
}
