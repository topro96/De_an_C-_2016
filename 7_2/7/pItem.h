#pragma once
#include "Button.h"
#include <vector>
void OutStringXY(int x, int y, string str);
enum status
{
	NONE, CLICKED
};
class pItem:public Button
{
	int _width, _height;
	int _status;
	int _bkColor1,_bkColor2;
	vector<string> _outText;
	bool _tick;
public:
	pItem();
	pItem(int X1, int Y1, int X2, int Y2, int Color1, int Color2, int bkColor1, int bkColor2, string str, int CharSize=0, int Font=0);
	~pItem();
	
	int Height() { return _height; }
	void Tick(bool tick) { _tick = tick; }
	bool Tick() { return _tick; }
	void Draw(int color);
	void Draw();
	void DrawTick() {
		if (_tick == 1) {
			setlinestyle(0, 0, 2);
			line(x1-2, y1+1, x1 + 3, y1+1);
			line(x1-2, y1+1, x1-2 , y1 + 6);
		}
	}
	void Init(string s);
	void OutText(int x, int y);
	int Status() const { return _status; }
	void Status(int val) { _status = val; }
	void Selected(const int fontOutText);

	void ChangeOutTextStr( string s) {
		_outText.clear();
		Init(s);
	}
	string OutTextStr() {
		string temp;
		for (int i = 0; i < _outText.size(); i++)
		{
			temp += _outText[i];
		}
		return temp;
	}


	void Y2(int val) { y2 = val; }
	int Y2() { return y2; }
	void Y1(int val) { y1 = val; }
	int Y1() { return y1; }
	void X2(int val) { x2 = val; }
	int X2() { return x2; }
	void X1(int val) { x1 = val; }
	int X1() { return x1; }
};

