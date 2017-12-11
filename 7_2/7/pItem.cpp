#include "pItem.h"



pItem::pItem()
{
}
pItem::pItem(int X1, int Y1, int X2, int Y2, int Color1, int Color2,int bkColor1,int bkColor2, string str, int CharSize, int Font)
	:Button(X1,Y1,X2,Y2,Color1,Color2,"", CharSize, Font,0,0)
{
	_bkColor1 = bkColor1;
	_bkColor2 = bkColor2;
	_status = NONE;
	_width = x2 - x1;
	_height = 0;
	Init(str);
	y2 = y1 + _height;
	_height = y2 - y1;
}

pItem::~pItem()
{
}

 void pItem::Draw(int color) {
	int oldcolor = getcolor();
	setcolor(color);
	OutText(x1, y1);
	setcolor(oldcolor);
}

 void pItem::Draw() {
	
	 if (_status == 1) {
		 setbkcolor(_bkColor2);
		 Draw(color2);
		 setbkcolor(_bkColor1);
	 }
	 else {
		 setbkcolor(_bkColor1);
		 Draw(color1);
	 }
	 DrawTick();
 }

void pItem::Init(string s) {
	  settextstyle(font, 0, charSize);
	  int a = textwidth(&s[0]);
	  string temp;
	  if (a <= _width)
	  {
		  _height += textheight(&s[0]);
		  _outText.push_back(s);
	  }
	  else
	  {
		  int i,j;
		  for (i = 0; i < s.size(); i++)
		  {
			  temp.push_back(s[i]);
			  if (textwidth(&temp[0]) >= _width&&s[i + 1] != ' ')
			  {
				  j = i;
				  while (s[j]!=' '&&j>0)
					  j--;

				  if (j>0)
				  {
					  for(int k=j;k<=i;k++)
						  temp.pop_back();
					  s.erase(0, j);
				  }
				  else {
					  temp.pop_back();
					  s.erase(0, i);
				  }
				  _outText.push_back(temp);
				  _height += textheight(&temp[0]);
				  break;
			  }
		  }
		  Init(s);
	  }
  }

void pItem::OutText(int x, int y) {
	textsettingstype old;
	gettextsettings(&old);
	settextstyle(font, 0, charSize);
	for (vector<string>::iterator it = _outText.begin(); it != _outText.end(); it++) {
		OutStringXY(x, y, *it);
		y += 17;
	}
	settextstyle(old.font, old.direction, old.charsize);
}

void pItem::Selected(const int fontOutText)
{
	checkMouse = true;
	if (fontOutText == 0)
	{
		setbkcolor(_bkColor2);
		Draw(color2);
	}
}

void OutStringXY(int x, int y, string str) {
	outtextxy(x, y, &str[0]);
}
