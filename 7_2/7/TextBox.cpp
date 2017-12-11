#include "TextBox.h"

int frameFontText = 0;

void XoaKhoangTrangCuoi(string  &a)
{
	int lengthCurrent = a.length();
	if (lengthCurrent > 0 && a[lengthCurrent - 1] == 32) //xoa khoang canh cuoi
	{
		a.erase(lengthCurrent - 1,1);
	}
	
}

void TextBox::OutTextChange()
{
		setbkcolor(1);
		setcolor(7);
		settextstyle(font, 0, charSize); //cài cho chuỗi
		int textHight = textheight(_strdup(text.c_str())); //lay chieu cao  text
		int textWidth = textwidth(_strdup(text.c_str())); //lay chieu rong
		outtextxy(x1 + 5, y1 + (y2 - y1 - textHight) / 2, _strdup(text.c_str()));
}

void TextBox::Input(int &mouseX, int &mouseY)
{
	int lengthCurrent;
	Selected(1);
	int x;
	while (kbhit()) getch(); //xoa bo nho dem
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (CheckMouseClick(mouseX, mouseY) == false)
			{				
				UnSelected(1);
				status = Mouse;
				return;
			}
		}
		//lay ki tu duoc chon
		while (kbhit())
		{
			lengthCurrent = text.length();
			x = getch();
			if (x == 0)
			{
				x = getch();
				if (x == 72) //up
				{
					XoaKhoangTrangCuoi(text);
					UnSelected(1);
					status =  Up;
					return;
				}
				else
					if (x == 80) //down
					{
						XoaKhoangTrangCuoi(text);
						UnSelected(1);
						status =  Down;
						return;
					}
			}
			else
			if ((int)x == 13) //phim enter
			{
				XoaKhoangTrangCuoi(text);
				UnSelected(1);
				status = Enter;
				return;
			}
			else
				if ((int)x == 9) //phim tab
				{
					XoaKhoangTrangCuoi(text);
					UnSelected(1);
					status = Down;
					return;
				}
			else
				if (x == 8 && lengthCurrent > 0) //phim xoa
				{
					text.erase(lengthCurrent - 1,1);
				}
				else
					if (lengthCurrent >= length)
					{
						
					}
					else
						if (x > 47 && x < 58 || x > 64 && x < 91) //so vs chu hoa
						{
							text += (char)x;
						}
						else
							if (x == 32)
							{
								if (text.length() != 0 && text[lengthCurrent - 1] != 32) //kiem tra nhap dau cach
								{
									text += (char)x;
								}
							}
							else
								if (x > 96 && x < 123) //chử thường
								{
									x -= 32;
									text += x;
								}
			Draw();
		}
	}
	XoaKhoangTrangCuoi(text);
	UnSelected(1);
	status = None;
}

void CheckNumber(int x, InputStatus &status, string &text, int lengthMax)
{
	int lengthCurrent = text.length();
	if (x == 0)
	{
		x = getch();
		if (x == 72) //up
		{
			status = Up;
			return;
		}
		else
			if (x == 80) //down
			{
				status = Down;
				return;
			}
	}
	else
		if ((int)x == 13) //phim enter
		{
			status = Enter;
			return;
		}
		else
			if ((int)x == 9) //phim tab
			{
				status = Down;
				return;
			}
			else
				if (x == 8 && lengthCurrent > 0) //phim xoa
				{
					text.erase(lengthCurrent - 1, 1);
				}
				else
					if (lengthCurrent >= lengthMax)
					{
						//cout << "\nDo dai toi da cho phep la: " << n;
					}
					else
						if (x == 46)
						{
							if (text[lengthCurrent - 1] != '.')
							{
								text += (char)x;
							}
						}
						else
							if (x > 47 && x < 58) //so
							{
								text += (char)x;
							}
}

void TextBox::InputNumber(int & mouseX, int & mouseY, const int lengthMax)
{
	while (kbhit()) getch(); //xoa bo nho dem
	Selected(1);
	status = None;
	int x;

	OutTextChange();
	bool check = false;

	while (true) 
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
			if (CheckMouseClick(mouseX, mouseY) == false)
			{
				UnSelected(1);
				if (text[0] < 48 || text[0] >57) //Không phải là số
					setText("");
				
				status = Mouse;
				return;
			}
		}
		while (kbhit())
		{
			x = getch();
			if (x > 47 && x < 58 || x == 46)
			{
				
				text = x;
				check = true;
			}
			else
				if (x == 8)
				{
					text = "";
					check = true;
				}
				else
					if (x == KEY_RIGHT)
						check = true;
		}
		if (check)
			break;
	}

	Draw();
	
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
			if (CheckMouseClick(mouseX, mouseY) == false)
			{				
				UnSelected(1);
				status = Mouse;
				return;
			}
		}
		//lay ki tu duoc chon
		while (kbhit())
		{
			x = getch();
			CheckNumber(x, status, text, lengthMax);
			Draw();
		}

		if (status != None)
			break;
	}
}


void TextBox::OutPassWord()
{
	setbkcolor(color);
	setcolor(textColor);
	settextstyle(font, 0, charSize); //cài cho chuỗi
	int textHight = textheight(_strdup(text.c_str())); //lay chieu cao  text
	int textWidth = textwidth(_strdup(text.c_str())); //lay chieu rong
	string x ="";
	int length = text.length();
	for (int i = 0; i < length; i++)
		x += "*";
	outtextxy(x1 + 5, y1 + (y2 - y1 - textHight) / 2,_strdup(x.c_str()));
}


void TextBox::InputPassWord(int & mouseX, int & mouseY)
{
	int lengthCurrent;
	color = color2;
	checkMouse = true;
	DrawPassWord();
	int x;
	while (kbhit()) getch(); //xoa bo nho dem
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
			if (CheckMouseClick(mouseX, mouseY) == false)
			{
				XoaKhoangTrangCuoi(text);
				color = color1;
				checkMouse = false;
				DrawPassWord();
				status = Mouse;
				return;
			}
		}
		//lay ki tu duoc chon
		while (kbhit())
		{
			lengthCurrent = text.length();
			x = getch();
			if (x == 0)
			{
				x = getch();
				if (x == 72) //up
				{
					XoaKhoangTrangCuoi(text);
					color = color1;
					checkMouse = false;
					DrawPassWord();
					status = Up;
					return;
				}
				else
					if (x == 80) //down
					{
						XoaKhoangTrangCuoi(text);
						color = color1;
						checkMouse = false;
						DrawPassWord();
						status = Down;
						return;
					}
			}
			else
				if ((int)x == 13) //phim enter
				{
					XoaKhoangTrangCuoi(text);
					color = color1;
					checkMouse = false;
					DrawPassWord();
					status = Enter;
					return;
				}
				else
					if ((int)x == 9) //phim tab
					{
						XoaKhoangTrangCuoi(text);
						color = color1;
						checkMouse = false;
						DrawPassWord();
						status = Down;
						return;
					}
					else
						if (x == 8 && lengthCurrent > 0) //phim xoa
						{
							text.erase(lengthCurrent - 1, 1);
						}
						else
							if (lengthCurrent >= length)
							{

							}
							else
								if (x > 47 && x < 58 || x > 64 && x < 91) //so vs chu hoa
								{
									text += (char)x;
								}
								else
									if (x == 32)
									{
										if (text.length() != 0 && text[lengthCurrent - 1] != 32) //kiem tra nhap dau cach
										{
											text += (char)x;
										}
									}
									else
										if (x > 96 && x < 123) //chử thường
										{
											x -= 32;
											text += x;
										}
			DrawPassWord();
		}
	}
	XoaKhoangTrangCuoi(text);
	color = color1;
	checkMouse = false;
	DrawPassWord();
	status = None;
}

void TextBox::Draw()
{
	DrawFrame();
	OutTextLeft();
}

void TextBox::DrawPassWord()
{
	DrawFrame();
	OutPassWord();
}



TextBox::TextBox()
{
	text[0] = '\0';
	status = None;
}

TextBox::TextBox(int X1, int Y1, int X2, int Y2, int Color1, int Color2, char Text[30], int CharSize, int Font, int FrameSize,int FrameColor, int Length)
{
	x1 = X1; y1 = Y1;
	x2 = X2; y2 = Y2;
	color1 = Color1; color2 = Color2; color = color1;
	/*strcpy_s(text, Text)*/text[0]='\0'; charSize = CharSize; length = Length;
	font = Font;
	frameSize = FrameSize; frameColor = FrameColor;
	checkMouse = false;
	status = None;
	
}

TextBox::~TextBox()
{
}
