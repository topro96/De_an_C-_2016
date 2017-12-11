#include "Pages.h"



Pages::Pages()
{
}


Pages::~Pages()
{
}

Pages::Pages(int X1, int Y1, int X2, int Y2, int color1, int color2, int bkColor, int frameSize, int frameColor, int le)
{
	_clicked = -1;
	_le = le;
	_n = 0;
	_p = 0;
	_bkColor = bkColor;
	drawBk = 0;
	_page = 0;
	x1 = X1; y1 = Y1; x2 = X2; y2 = Y2;
	_frameColor = frameColor;
	_frameSize = frameSize;
	_next = new Button(x2-20,y2-20,x2,y2,color1,color2,">",0,0,frameSize,frameColor);
	_pre = new Button(x2 - 40, y2 - 20, x2-20, y2, color1, color2, "<", 0, 0, frameSize, frameColor);
}

void Pages::DrawFrame()
{
	setfillstyle(1, _bkColor); //to mau cho hinh chu nhat
	bar(x1, y1, x2, y2); //hinh chu nhat
	setcolor(_frameColor);
	setlinestyle(0, 0, _frameSize);
	rectangle(x1, y1, x2, y2); //khung hình chử nhật

}

 void Pages::Add(pItem * item, int group) {
	int y_1, y_2;
	if (_n != 0)
		y_1 = _lItem[_n - 1]._item->Y2();
	else
		y_1 = y1 + _le;

	y_2 = y_1 + item->Height();
	_lItem[_n++].Add(group, item);
	if (!_lPage[_p].Add(item, y_1, y_2, _lPage[_p]._start, y2 - y1 - _le * 2)) {
		y_1 = y1 + _le;
		_p++;
		_lPage[_p].Init(_lPage[_p - 1]._end + 1, y_1, y2 - y1 - _le * 2, item);
	}
	s << _p << '/' << _p;
	s>>_numPage;
	s.clear();
}

  void Pages::Show() {

	 if (drawBk == 0)
	 {
		 DrawFrame();
		 drawBk = 1;
	 }
	 for (int i = _lPage[_page]._start; i <= _lPage[_page]._end; i++)
	 {
		 if (i >= 0)
			 _lItem[i]._item->Draw();
	 }
	 if (_p>0)
	 {
		 ShowNumPage();
		 _next->Draw();
		 _pre->Draw();
	 }	
 }

  int Pages::Click(int x, int y, int stop) {

	  if (_p > 0) {
		  if (_next->CheckMouseClick(x, y))
			  if (_page < _p)
			  {
				  _page++;
				  drawBk = 0;
				  Show();
			  }
		  if (_pre->CheckMouseClick(x, y))
			  if (_page > 0) {
				  _page--;
				  drawBk = 0;
				  Show();
			  }
	  }
	  if (stop > 0)
		  for (int i = _lPage[_page]._start; i <= _lPage[_page]._end; i++)
		  {
			  if (_lItem[i]._group > 0)
				  if (_lItem[i]._item->CheckMouseClick(x, y))
				  {
					  _clicked = i;
					  _lItem[i]._item->Status(CLICKED);
					  _lItem[i]._item->Draw();
					  for (int j = 0; j < _n; j++)
					  {
						  if (_lItem[j]._item->Status() == CLICKED&&j != i&&_lItem[j]._group == _lItem[i]._group)
						  {
							  _lItem[j]._item->Status(NONE);
							  if (j >= _lPage[_page]._start&&j <= _lPage[_page]._end)
								  _lItem[j]._item->Draw();
						  }
					  }

					  return i;
				  }
		  }

	  return -1;
  }

    bool Pages::GoTo(int i) {
	   for (int j = 0; j <= _p; j++)
	   {
		   if (i >= _lPage[j]._start&&i <= _lPage[j]._end) {
			   int temp = _page;
			   _page = j;
			   if (_page != temp)
				   drawBk = 0;
			   Show();
			   return true;
		   }
	   }
	   return false;
   }

	void Pages::MouseMove(int stop) {
		/*if (stop > 0)
			for (int i = _lPage[_page]._start; i <= _lPage[_page]._end; i++) {
				if (_lItem[i]._group > 0)
					_lItem[i]._item->CheckMouseMove(0);

			}*/
		/*else
		{
			if (stop == 0) {
				Show();
				stop = -1;
			}
		}*/

		if (_p > 0) {
			_next->CheckMouseMove(0);
			_pre->CheckMouseMove(0);
		}
	}

	  void Pages::Active(int i) {
		 if (_clicked != -1)
		 {
			 if (_lItem[_clicked]._group == _lItem[i]._group) {
				 _lItem[_clicked]._item->Status(NONE);
			 }

		 }
		 _lItem[i]._item->Status(CLICKED);
		 _clicked = i;
	 }
