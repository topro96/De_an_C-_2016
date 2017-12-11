#pragma once
#include "pItem.h"
#include <sstream>
using namespace std;
#define MAX 500
struct pageItem {
	int _group;
	pItem *_item;
	void Add(int group, pItem *item) {
		_group = group;
		_item = item;
	}
};
struct page {
	int _start, _end,_currentHeight;
	page() {
		_start = -1;
		_end = -1;
		_currentHeight = 0;
	}
	
	bool Add(pItem *item,int y1,int y2,int start,int heightPx) {
		if (start==-1)
		{
			_start = 0;
		}
		else
			_start = start;
		if (_currentHeight+item->Height()>heightPx)
		{
			return false;
		}
		else 
		{
			_end++;
			_currentHeight += item->Height();
			item->Y1(y1);
			item->Y2(y2);
			return true;
		}
	}
	void Init(int start, int y,int height, pItem* item) {
		_start = start;
		_end = start - 1;
		item->Y1(y);
		item->Y2(y + item->Height());
		Add(item,y, y + item->Height(), _start, height);
	}
};

class Pages
{
	int x1, y1, x2, y2;
	int _n;//so item
	int _p;//so page
	int _page;//page hien tai
	Button *_next, *_pre;
	int _le;//canh le
	int _frameSize, _frameColor;
	int _bkColor; int drawBk;
	int _clicked;
	stringstream s;
	string _numPage;
public:
	Pages();
	~Pages();
	page _lPage[MAX];
	pageItem _lItem[MAX];
	Pages(int X1, int Y1, int X2, int Y2,int color1,int color2,int bkColor, int frameSize, int frameColor, int le = 30);
	void ShowNumPage() {
		settextstyle(0, 0, 0);
		setcolor(_frameColor);
		s << _page + 1 << "/" << _p + 1;
		string str;
		s >> str;
		s.clear();
		OutStringXY(x1 + _le, y2 - 18, str);
	}

	void DrawFrame();
	void Add(pItem *item, int group);
	void Show();
	int Click(int x, int y, int stop);
	bool GoTo(int i);
	void MouseMove(int stop);
	void Active(int i);
};

