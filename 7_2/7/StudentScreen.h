#pragma once
#include "DataBase.h"
#include "DataBase.h"
#include "TextBox.h"
#include "Test.h"

string ChangePassWord(string oldPass)
{
	initwindow(500, 300, "", 10, 100);
	

	setbkcolor(0);
	setcolor(7);
	settextstyle(0, 0, 0);
	outtextxy(10, 40, "Mat khau hien tai:");

	outtextxy(30, 110, "Mat khau moi:");

	outtextxy(10, 180, "Nhap lai mat khau:");

	TextBox txtPassHienTai;
	txtPassHienTai.Init(200, 30, 400, 70, 0, 7, 9, "", 0, 0, 0, 7, 18);
	txtPassHienTai.Draw();

	TextBox txtPassMoi1;
	txtPassMoi1.Init(200, 100, 400, 140, 0, 7, 9, "", 0, 0, 0, 7, 18);
	txtPassMoi1.Draw();

	TextBox txtPassMoi2;
	txtPassMoi2.Init(200, 170, 400, 210, 0, 7, 9, "", 0, 0, 0, 7, 18);
	txtPassMoi2.Draw();

	Button btnCancel(430, 250, 495, 295, 6, 7, "Cancel", 0, 0, 1, 7);
	btnCancel.Draw();

	Button btnChange(200, 240, 270, 290, 5, 9, "Change", 0, 0, 0, 7);
	btnChange.Draw();

	int mouseX, mouseY;
	mouseX = mouseY = -1;

	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (btnCancel.CheckMouseClick(mouseX, mouseY))
			{
				closegraph(-1);
				return "";
			}
			else
				if (txtPassHienTai.CheckMouseClick(mouseX, mouseY))
					txtPassHienTai.InputPassWord(mouseX, mouseY);
				else
					if (txtPassMoi1.CheckMouseClick(mouseX, mouseY))
					{
						txtPassMoi1.InputPassWord(mouseX, mouseY);
					}
					else
						if(txtPassMoi2.CheckMouseClick(mouseX, mouseY))
						{
							txtPassMoi2.InputPassWord(mouseX, mouseY);
						}
						else
							if (btnChange.CheckMouseClick(mouseX, mouseY))
							{
								if (txtPassHienTai.getText() == oldPass && txtPassMoi1.getText() == txtPassMoi2.getText())
								{
									closegraph(-1);
									return txtPassMoi1.getText();
								}
								else
								{
									setbkcolor(0);
									setcolor(4);
									settextstyle(0, 0, 0);
									if (txtPassHienTai.getText() != oldPass)
									{
										outtextxy(420, 43, "X");
									}
									if (txtPassMoi1.getText() != txtPassMoi2.getText())
									{
										outtextxy(420, 113, "X");
										outtextxy(420, 183, "X");
									}
								}
							}
		}
	}

	return "";
	getch();
	closegraph(-1);
}

void StudentScreen(Data *&dataBase, SinhVien *&sinhVien, Lop &lopHoc)
{

	int studentScreen = initwindow(800, 400, "", 0, 0);

	TextBox txtMonThi;
	TextBox txtPhutPhi;
	TextBox txtSoCauHoi;

	MyArray *myArray = new MyArray;

	setbkcolor(0);
	setcolor(7);
	settextstyle(0, 0, 0);
	outtextxy(100, 40, "Mon thi:");

	outtextxy(90, 110, "Phut thi:");

	outtextxy(70, 180, "So cau hoi:");

	txtMonThi.Init(200, 30, 500, 70, 0, 7, 9, "", 0, 0, 0, 7, 40);
	txtMonThi.Draw();

	txtPhutPhi.Init(200, 100, 300, 140, 0, 7, 9, "", 0, 0, 0, 7, 40);
	txtPhutPhi.Draw();

	txtSoCauHoi.Init(200, 170, 300, 210, 0, 7, 9, "", 0, 0, 0, 7, 40);
	txtSoCauHoi.Draw();

	Button btnThi(350, 270, 450, 310, 5, 6, "Thi", 1, 1, 1, 7);
	btnThi.DrawBetween();

	Button btnExit(695, 355, 795, 395, 9, 4, "Exit", 1, 1, 1, 7);
	btnExit.DrawBetween();

	Button btnChangePass(10, 355, 150, 395, 9, 4, "Change Pass", 0, 0, 1, 7);
	btnChangePass.DrawBetween();

	int mouseX, mouseY;
	mouseX = mouseY = -1;



	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (txtMonThi.CheckMouseClick(mouseX, mouseY))
				txtMonThi.Input(mouseX, mouseY);
			else
				if (txtPhutPhi.CheckMouseClick(mouseX, mouseY))
					txtPhutPhi.InputNumber(mouseX, mouseY, 4);
				else
					if (txtSoCauHoi.CheckMouseClick(mouseX, mouseY))
						txtSoCauHoi.InputNumber(mouseX, mouseY, 3);
					else
						if (btnExit.CheckMouseClick(mouseX, mouseY))
						{
							closegraph(-1);
							return;
						}
						else
							if (btnThi.CheckMouseClick(mouseX, mouseY))
							{
								MonHoc *monThi = dataBase->SearchMon(txtMonThi.getText());
								int soCauHoi = atoi(_strdup(txtSoCauHoi.getText().c_str()));
								int phutThi = atoi(_strdup(txtPhutPhi.getText().c_str()));
								
								if (monThi != NULL)
								{
									string str = "Co ";
									if (soCauHoi <= monThi->getSoCauHoi() && monThi->getSoCauHoi() > 0)
									{
										myArray->Remake();
										LoadIndexFromTreeToArray(monThi->treeCauHoi->_root, myArray); //load câu hỏi hiện có vào myArray
										int temp;
										int *arrayQuestion = new int[soCauHoi + 1];
										for (int i = 0; i < soCauHoi; i++)
										{
											temp = myArray->getRandSelected();
											arrayQuestion[i] = myArray->myArray[temp]; //lấy 1 câu bất kì
											myArray->Delete(temp); //loại
										}
										
											float diem = Test(arrayQuestion, soCauHoi, *sinhVien, *monThi, phutThi * 60);
											sinhVien->AddDiem(diem, monThi->getMaMonHoc());
											dataBase->SavaDataStudent(&lopHoc);
										
										closegraph(-1);
										return;
									}
									else //so cau hoi khong du de thi
									{
										setbkcolor(0);
										setcolor(7);
										settextstyle(0, 0, 0);
										str += to_string(monThi->getSoCauHoi());
										str += " cau hoi!";
										outtextxy(200, 350, "                           ");
										outtextxy(200, 350,_strdup(str.c_str()) );
										
									}
								}
								else //mon thi khong ton tai
								{
									setbkcolor(0);
									setcolor(7);
									settextstyle(0, 0, 0);
									outtextxy(200, 350, "                           ");
									outtextxy(200, 350, "Mon hoc khong dung!");
								}
							}
							else
								if (btnChangePass.CheckMouseClick(mouseX, mouseY))
								{
									string newPass = ChangePassWord(sinhVien->getPassWord());
									setcurrentwindow(studentScreen);
									if (newPass != "")
									{
										sinhVien->setPassWord(newPass);
									}
									dataBase->SavaDataStudent(&lopHoc);
								}
		}
	}

}
