#pragma once
#include "Pages.h"
#include "graphics.h"
#include <iostream>
#include "CauHoi.h"
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include "TextBox.h"
#include "DataStructure.h"
#include "SinhVien.h"
#include "MonHoc.h"


struct Q
{
	CauHoi *_cauhoi;
	int _cauHoiSo;
	void setCauHoi(CauHoi *cauhoi, int causo) {
		_cauhoi = cauhoi;
		_cauHoiSo = causo;
	}
	pItem *_c[6];
	char so[5];
	stringstream ss;
	void CreatePageItem(int x1, int x2, int color, int colorActive, int colorQ, int bkColor1, int bkColor2, int charSizeQ = 0, int fontQ = 0, int charSize = 0, int font = 0) {
		ss << _cauHoiSo << ".";
		ss >> so;
		_c[0] = new pItem(x1, 0, x2, 0, colorQ, colorQ, bkColor1, bkColor2, so + _cauhoi->getNoiDung(), charSizeQ, fontQ);
		_c[1] = new pItem(x1, 0, x2, 0, color, colorActive, bkColor1, bkColor2, "A." + _cauhoi->getAnswer()[0], charSize, font);
		_c[2] = new pItem(x1, 0, x2, 0, color, colorActive, bkColor1, bkColor2, "B." + _cauhoi->getAnswer()[1], charSize, font);
		_c[3] = new pItem(x1, 0, x2, 0, color, colorActive, bkColor1, bkColor2, "C." + _cauhoi->getAnswer()[2], charSize, font);
		_c[4] = new pItem(x1, 0, x2, 0, color, colorActive, bkColor1, bkColor2, "D." + _cauhoi->getAnswer()[3], charSize, font);
		_c[5] = new pItem(x1, 0, x2, 0, color, colorActive, bkColor1, bkColor2, " ", charSize, font);
	}
	bool KTDapAn() {
		for (int i = 1; i <= 4; i++)
		{
			if (_c[i]->Status() == CLICKED)
				if (i == _cauhoi->getDapAn() + 1)
					return true;
		}
		return false;
	}
	char TraLoi() {
		for (int i = 1; i < 5; i++)
		{
			if (_c[i]->Status() == CLICKED)
				return i + 96;
		}
		return 0;
	}
	void Tick() {
		_c[_cauhoi->getDapAn() + 1]->Tick(true);
	}
};

void Timer(int s, int x, int y, int &startTimer, int &stopEven) {
	while (true)
	{
		Sleep(100);
		if (startTimer == 1) {
			int start = clock();
			int end = start + s*CLOCKS_PER_SEC;
			int current = 0;
			int c = 0;
			stringstream ss;
			string t;
			ss << s / 60 << ":" << s % 60;
			ss >> t;
			ss.clear();
			outtextxy(x, y, &t[0]);
			while (current < end&&startTimer)
			{
				c = current;
				current = clock();
				if (c / CLOCKS_PER_SEC != current / CLOCKS_PER_SEC) {
					ss << (end / CLOCKS_PER_SEC - current / CLOCKS_PER_SEC) / 60 << ":" << (end / CLOCKS_PER_SEC - current / CLOCKS_PER_SEC) % 60;
					ss >> t;
					ss.clear();
					t += "   ";
					settextstyle(0, 0, 0);
					setcolor(BLACK);
					setbkcolor(7);
					outtextxy(x, y, &t[0]);
				}
				Sleep(100);
			}
			if (stopEven > 0)
				stopEven = 0;
			break;
		}
	}
}
int stop = 1, startTimer = 0;
void StartTimer(int t, int w) {

	Timer(t, w + 5, 10, startTimer, stop);
}
RECT GetResolution() {
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	return desktop;
}

void TTSV(int x1, int y1, int x2, int y2, string s) {
	bar(x1, y1, x2, y2); //hinh chu nhat
	rectangle(x1, y1, x2, y2); //khung hình chử nhật
	outtextxy(x1 + 10, y1 + 10, &s[0]);
}

int ShowTTSV(SinhVien sv, MonHoc mh, int width, int height) {

	int testScreen = initwindow(width, height, "");
	string str;
	setfillstyle(1, 7); //to mau cho hinh chu nhat
	setcolor(0);
	setlinestyle(0, 0, 1);
	setbkcolor(7);
	int w = (width - 110) / 3;
	str = "Môn: " + mh.getTenMonHoc();
	TTSV(0, 0, w, 30, str);

	str = "Tên: " + sv.getHo() + " " + sv.getTen();
	TTSV(w, 0, 2 * w, 30, str);


	str = "Mã SV: " + sv.getMaSV();
	TTSV(2 * w, 0, 3 * w, 30, str);

	str.clear();
	TTSV(w * 3, 0, width, 30, str);
	return testScreen;
}

float ThongBaoKQ(int wDesktop, int hDesktop, Q * q, int n)
{
	int screenKQ = initwindow(250, 150, "", wDesktop / 2 - 100, hDesktop / 2 - 100);

	setbkcolor(11);
	cleardevice();
	settextstyle(0, 0, 0);
	setcolor(0);

	int socaudung = 0;
	for (int i = 0; i < n; i++)
	{
		if (q[i].KTDapAn())
			socaudung++;
	}
	stringstream ss;
	string s;
	float kq;
	ss.precision(2);
	ss << "Correct answers: " << socaudung << "/" << n;
	getline(ss, s);
	outtextxy(20, 50, &s[0]);
	ss.clear();
	kq = (float)socaudung / n * 10;
	ss << "Scores: " << kq;
	getline(ss, s);
	outtextxy(20, 70, &s[0]);


	Button btnOK(110, 120, 140, 140, 7, 10, "OK", 0, 0, 0, 0);
	btnOK.DrawBetween();

	int x, y;
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (btnOK.CheckMouseClick(x, y))
				break;
		}
	}
	closegraph(screenKQ);
	return kq;
}

float Test(int * idCauHoi, int n, SinhVien sv, MonHoc mh, int t) {
	//TaoCauHoi();
	int kq = 0;
	RECT r = GetResolution();
	int width = r.right;
	int height = r.bottom;
	int pWidth = (width - 110) / 3 * 3;
	int testScreen = ShowTTSV(sv, mh, width, height);
	startTimer = 1;
	thread timer(StartTimer, t, pWidth + 5);
	timer.detach();


	Button btnSend;
	btnSend.Init(pWidth, height - 60, width, height,0, 11, 7, "Nạp", 0, 0, 0, BLACK,10);
	btnSend.DrawBetween();
	Button btnExit(width - 31, 0, width - 5, 30, 11, 12, "X", 0, 0, 0, 0);
	btnExit.DrawBetween();
	//CauHoi ch[SOCAUHOI];
	Q* q = new Q[n];

	Pages p(0, 30, pWidth, height, WHITE, BLACK, WHITE, 0, BLUE);

	Pages dapAn(pWidth, 30, width, height - 60, WHITE, BLACK, WHITE, 0, BLUE);
	pItem * item;
	stringstream ss;
	string c;


	//ifstream inf("cauhoi.txt");
	for (int i = 0; i < n; i++)
	{
		//ch[i].InputFStream(inf);
		q[i].setCauHoi(mh.treeCauHoi->Search(idCauHoi[i], mh.treeCauHoi->_root)->_data, i + 1);
		q[i].CreatePageItem(20, pWidth - 20, 3, BLUE, GREEN, WHITE, 10, 1, 1);


		p.Add(q[i]._c[0], 0);
		for (int j = 1; j < 5; j++)
		{
			p.Add(q[i]._c[j], q[i]._cauHoiSo);
		}
		p.Add(q[i]._c[5], 0);

		//DAP AN
		ss << i + 1 << ".?";
		ss >> c;
		c.push_back(' ');
		ss.clear();
		item = new pItem(pWidth + 20, 0, width, 0, 8, BLUE, WHITE, 10, c);
		dapAn.Add(item, 1);
	}



	dapAn.Show();
	p.Show();

	int x, y;
	int dapan, cauhoi, a;
	string strDapAn;

	while (true)
	{
		Sleep(50);
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);

			a = p.Click(x, y, stop);
			cauhoi = p._lItem[a]._group;

			if (cauhoi > 0) {
				strDapAn = dapAn._lItem[cauhoi - 1]._item->OutTextStr();
				strDapAn.pop_back();
				strDapAn.pop_back();
				strDapAn.push_back(q[cauhoi - 1].TraLoi());
				strDapAn.push_back(' ');
				dapAn._lItem[cauhoi - 1]._item->ChangeOutTextStr(strDapAn);
				dapAn.Active(cauhoi - 1);
				dapAn.GoTo(cauhoi - 1);
			}
			dapan = dapAn.Click(x, y, 1);
			if (dapan >= 0) {
				if (dapan == 0)
					p.GoTo(0);
				else
					p.GoTo(dapan * 6 - 1);
			}
			if (btnSend.CheckMouseClick(x, y)) {
				stop = -1;
				startTimer = 0;
				for (int i = 0; i < n; i++)
				{
					q[i].Tick();
				}
				p.Show();

				kq = ThongBaoKQ(width, height, q, n);
				setcurrentwindow(testScreen);

			}
			if (btnExit.CheckMouseClick(x, y)) {
				closegraph(testScreen);
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		p.MouseMove(stop);
		dapAn.MouseMove(1);
		btnSend.CheckMouseMove(0);

		if (stop == 0)
		{
			for (int i = 0; i < n; i++)
			{
				q[i].Tick();
			}
			p.Show();
			stop = -1;
			kq = ThongBaoKQ(width, height, q, n);
			setcurrentwindow(testScreen);
		}
	}

	getchar();
	closegraph(testScreen);
	return kq;
}




