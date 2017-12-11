#pragma once
#include "DataBase.h"
#include "TextBox.h"
#include "TeacherScreen.h"
#include "StudentScreen.h"
#include "DataStructure.h"
#include "Test.h"
using namespace std;


//giao vien dang nhap
int GiaoVienLogin(string ID, string passWord)
{
	fstream f;
	f.open("GiaoVien.txt", ios::in);
	if (!f.is_open() || f.fail())
	{
		cout << "Chua co giao vien!";
		return 0;
	}
	string i;
	string j;
	while (!f.eof())
	{
		f >> i;
		f >> j;
		if (i == ID && j == passWord)
		{
			return 1;
		}
	}
	return 0;
}

SinhVien *SinhVienLogin(Lop *DSLop, int nLop, string ID, string passWord, Lop &lopX)
{
	for (int i = 0; i < nLop; i++)
	{
		for (SinhVien *p = DSLop[i].firstSV; p != NULL; p = p->pRight)
		{
			if (p->getMaSV() == ID && p->getPassWord() == passWord)
			{
				lopX = DSLop[i];
				return p;
			}
		}
	}
	return NULL;
}

void LoginScreen(Data *&dataBase)
{
	int loginScreen = initwindow(600, 400, "", 0, 0);
	settextstyle(0, 0, 2);
	outtextxy(100, 100, "ID:");
	TextBox txtID(170, 85, 500, 125, 5, 6, "", 1, 1, 1, 7, 20);
	txtID.Draw();
	outtextxy(80, 150, "Pass:");
	TextBox txtPass(170, 140, 500, 180, 5, 6, "", 1, 1, 1, 7, 20);
	txtPass.DrawPassWord();

	Button btnLogIn(275, 220, 380, 260, 5, 6, "Log In", 1, 1, 1, 7);
	btnLogIn.DrawBetween();

	int mouseX, mouseY;
	mouseX = -1; mouseY = -1;

	int dem = 0;
	SinhVien *sinhVien;
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (txtID.CheckMouseClick(mouseX, mouseY) || txtPass.getStatus() != None)
			{
				txtID.Input(mouseX, mouseY);
				txtPass.setStatus(None);
			}
			else
				if (txtPass.CheckMouseClick(mouseX, mouseY) || txtID.getStatus() != None)
				{
					txtPass.InputPassWord(mouseX, mouseY);
					txtID.setStatus(None);
				}
		}

		if (txtID.CheckEmpty()) //id trong
			txtID.Input(mouseX, mouseY);
		else
			if (txtPass.CheckEmpty()) //pass trong
				txtPass.InputPassWord(mouseX, mouseY);
			else
			{
				if (btnLogIn.CheckMouseClick(mouseX, mouseY) == 1 || txtPass.getStatus() == Enter) //kiem tra nhan log in
				{
					Lop lopX;
					sinhVien = SinhVienLogin(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtID.getText(), txtPass.getText(), lopX);
					if (sinhVien != NULL) //sinh vien dang nhap thanh cong
					{
						closegraph(-1);
						StudentScreen(dataBase, sinhVien, lopX);
						break;
					}
					else
					{
						if (GiaoVienLogin(txtID.getText(), txtPass.getText()) == 1)
						{
							closegraph(-1);
							TeacherScreen(dataBase);
							break;
						}
						else
						{
							dem++;
							setbkcolor(0);
							settextstyle(0, 0, 0);
							setcolor(4);
							outtextxy(150, 300, "ID hoac Pass khong dung!");
						}
					}
				}

			}
	}
	closegraph(-2);
}

int main()
{

	Data *dataBase = new Data;
	dataBase->LoadData();
	dataBase->LayMaCacLop();
	dataBase->LayMaCacMon();
	FreeConsole();

	LoginScreen(dataBase);

	dataBase->FreeAllPointer(); //giải phóng gần hết toàn bộ con trỏ :v
	delete dataBase;
	return 0;
}