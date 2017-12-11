#pragma once
#include "Button.h"
#include <thread>
using namespace std;

void CopyStr(string &a, string b, int i, int e);

class TextBox1 
{
	int x1, x2, y1, y2, font, charSize, color1, color2,frameSize,frameColor;
	int length; //do dai chuoi toi da cho phep
	int widthCursor; //tọa độ con trỏ văn bản
	string str //str: string nhập vào
		, showText//showText: string được hiển thị ra màn hình
		, temp;//temp: string từ điểm bắt đầu hiển thị re màn hình đến con trỏ văn bản
	int cursor = -1//cursor: vị trí trong str ứng với con trỏ
		, i=0 //showText = str[i]->str[endShowText],temp= str[i]->str[cursor]
		, endShowText=0;//showText = str[i]->str[endShowText],temp= str[i]->str[cursor]
	int le = 3, status = 0, style;//le: khoảng cách cách lề trái và phải,clicked: =1 khi textbox được kích hoạt ngược lại =0
	int textX1, textX2;// văn bản được hiển thị trong khoảng textX1 đến textX2
	static int xCursor, y1Cursor, y2Cursor, stopCursor, pauseCursor, colorCursor, colorBg, clickInTxb;
public:
	
	// void Input(int &mouseX, int &mouseY);
	void Draw();
	
	void DrawFrame();
	void Init(int X1, int Y1, int X2, int Y2, int Color1, int Color2, int CharSize, int Font, int FrameSize, int FrameColor, int Style = 0, int Length = -1) {
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
	int Status() { return status; }
	static void DrawCurSor();//vẻ con trỏ
	static void StartCursor();//bát đầu chạy thread vẻ con trỏ
	void Input() {
		settextstyle(font, 0, charSize);
		char c;
		int x, y;
		ShowCursor();
		while (true)
		{
			if (ismouseclick(WM_LBUTTONDOWN))
			{
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if (!ClickInThis(x, y))
					break;
			}
			if (kbhit()) {
				c=getch();
				Input(c);
				if (status == -1)
					break;
			}
		}
	}
	void InputNumber() {
		settextstyle(font, 0, charSize);
		char c;
		int x, y;
		ShowCursor();
		while (true)
		{
			if (ismouseclick(WM_LBUTTONDOWN))
			{
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if (!ClickInThis(x, y))
					break;
			}
			if (kbhit()) {
				c = getch();
				InputNumber(c);
				if (status == -1)
					break;
			}
		}
	}
	void ShowCursor() { pauseCursor = 1; }
	void StopCursor();//dừng thread vẽ con trỏ
	int ClickInThis(int x, int y);//click vào nó
	void KeyL();//phím trái
	void KeyR();//phím phải
	void InPutChar(char c);//nhập char
	void KBackSpace();//phím backspace
	void Enter()//phím enter
	{
		status = -1;
		pauseCursor = 0;
	}
	void InputNumber(char c) {
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
				if (c >= 48 && c <= 57) {
					if (length >= 0) {
						if (str.size() < length)
							InPutChar(c);
					}
					else
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
	void KDelete();//phím delete
	void Input(char c); //
	string getText() { return str; }
	void setText(string s) { str = s; }
	void ShowTextS() {
		if (style == 0)
			outtextxy(textX1, y1 + (y2 - y1 - textheight(&str[0])) / 2, &showText[0]);
		else
		{
			string t;
			for (int i = 0; i < showText.size(); i++)
				t.push_back('*');
			outtextxy(textX1, y1 + (y2 - y1 - textheight(&str[0])) / 2, &t[0]);
			
			if (status > 0) {
				t.clear();
				for (int j = i; j <= cursor; j++)
					t.push_back('*');
				xCursor = textX1 + textwidth(&t[0]);
			}
			
		}
	}
	void ShowTextDefault() {
		string t;
		for (int i = 0; i < str.size(); i++)
		{
			if (style == 0)
				t.push_back(str[i]);
			else
				t.push_back('*');
			if (textwidth(&t[0]) > textX2 - textX1) {
				t.pop_back();
				break;
			}

		}
		showText = t;
		endShowText = showText.size() - 1;
		i = 0;
	}

	void DrawFrame(int color) {
		setfillstyle(1, color);
		bar(x1, y1, x2, y2); //hinh chu nhat
		setcolor(frameColor);
		setlinestyle(0, 0, frameSize);
		rectangle(x1, y1, x2 - 1, y2 - 1); //khung hình chử nhật
	}
	TextBox1();
	TextBox1(int X1, int Y1, int X2, int Y2, int Color1, int Color2, int CharSize, int Font, int FrameSize,int FrameColor, int Style=0, int Length=-1);
	~TextBox1();
};

