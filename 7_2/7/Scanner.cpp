#include "Scanner.h"


void XoaKhoangTrang(string &a)
{
	if (a.length() > 0)
		while (a[a.length() - 1] == 32) //xoa dau  " " sau cung
		{
			a.erase(a.length() - 1);
		}
}

int Scanner::LayDuLieu(string &a, ifstream & f)
{
	string x;
	a = "";
	while (!f.eof())
	{
		f >> x;
		if (x[0] == 124) //file vẫn còn
		{
			XoaKhoangTrang(a);
			return 1;
		}
		if (x[0] == 35) //gặp dấu #
		{
			XoaKhoangTrang(a);
			return 0;
		}
		a += x;
		a += " ";
	}
	return 0;
}





