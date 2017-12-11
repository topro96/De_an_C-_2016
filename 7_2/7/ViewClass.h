#pragma once
#include "TeacherScreen.h"
#include <thread>

using namespace std;

void PrintNoteStudent(const int x) //0 da xoa, 1 da luu, 2 da them
{
	settextstyle(1, 0,1);
	setcolor(0);
	setbkcolor(0);
	outtextxy(1150, 580, "------------");

	setcolor(7);
	setbkcolor(0);
	if (x == 0)
	{
		setcolor(4);
		outtextxy(1150, 580, "Da xoa!");
	}
	if (x == 1)
		outtextxy(1150, 580, "Da luu!");
	if (x == 2)
		outtextxy(1150, 580, "Da them!");
}

//0 hỏi lưu, 1 hỏi xóa
int DoYouWantTo(const int x)
{
	if (x == 0)
		initwindow(300, 200, "Do you want to save?", 500, 300);
	else
		initwindow(300, 200, "Are you sure?", 500, 300);

	Button btnYes;
	btnYes.Init(30, 60, 100, 120,0, 7, 8, "YES", 1, 1, 1, 2,10);
	btnYes.DrawBetween();
	Button btnNo;
	btnNo.Init(200, 60, 270, 120, 0, 7, 8, "No", 1, 1, 1, 4, 10);
	btnNo.DrawBetween();
	int mouseX, mouseY;
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (btnYes.CheckMouseClick(mouseX, mouseY))
			{
				closegraph(-1);
				return 1;
			}
			if (btnNo.CheckMouseClick(mouseX, mouseY))
			{
				closegraph(-1);
				return 0;
			}
		}

		btnYes.CheckMouseMove(0);
		btnNo.CheckMouseMove(0);
	}

}

int AddAStudent(Data *&dataBase, Lop *lop)
{
	int mouseX = -1, mouseY = -1;
	initwindow(600, 500, "Add a student", 0, 0, 0, 0);

	settextstyle(0, 0, 2);
	outtextxy(60, 105, "ID");
	settextstyle(0, 0, 0);
	outtextxy(0, 160, "First Name");
	outtextxy(0, 220, "Last Name");
	settextstyle(0, 0, 2);
	outtextxy(45, 280, "Sex");

	Button btnNam(110, 270, 170, 310, 5, 6, "Nam", 0, 0, 1, 7);
	btnNam.DrawBetween();
	Button btnNu(230, 270, 290, 310, 5, 6, "Nu", 0, 0, 1, 7);
	btnNu.DrawBetween();
	Button btnKhac(350, 270, 410, 310, 5, 6, "Khac", 0, 0, 1, 7);
	btnKhac.DrawBetween();

	TextBox txtArrayAdd[3]; //0 la Id, 1 la ho, 2 la ten

	txtArrayAdd[0].Init(110, 90, 500, 130,0, 5, 6, "", 0, 0, 1, 7, 20); //id
	txtArrayAdd[1].Init(110, 150, 500, 190,0, 5, 6, "", 0, 0, 1, 7, 40); //ho
	txtArrayAdd[2].Init(110, 210, 500, 250,0, 5, 6, "", 0, 0, 1, 7, 40); //ten

	for (int i = 0; i < 3; i++)
		txtArrayAdd[i].Draw();


	Button btnAdd(250, 330, 350, 380, 5, 2, "Add", 3, 1, 1, 6);
	btnAdd.DrawBetween();

	Button btnCancel(480, 440, 595, 496, 8, 4, "Cancel", 2, 1, 1, 2);
	btnCancel.DrawBetween();

	int flag = 0;
	txtArrayAdd[0].Input(mouseX, mouseY);
	int sex;
	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (btnNam.CheckMouseClick(mouseX, mouseY))
			{
				sex = 0;
				btnNam.Selected(0);
				btnNu.UnSelected(0);
				btnKhac.UnSelected(0);
			}
			else
				if (btnNu.CheckMouseClick(mouseX, mouseY))
				{
					sex = 1;
					btnNu.Selected(0);
					btnNam.UnSelected(0);
					btnKhac.UnSelected(0);
				}
				else
					if (btnKhac.CheckMouseClick(mouseX, mouseY))
					{
						sex = 3;
						btnKhac.Selected(0);
						btnNam.UnSelected(0);
						btnNu.UnSelected(0);
					}
					else
						if (btnCancel.CheckMouseClick(mouseX, mouseY))
						{
							closegraph(-1);
							return 0;
						}
						else
							if (btnAdd.CheckMouseClick(mouseX, mouseY) == 1) //kiem tra nhan log in
							{
								int check = 0;
								for (int i = 0; i < 3; i++)
								{
									if (txtArrayAdd[i].getText()[0] == '\0')
									{
										txtArrayAdd[i].Input(mouseX, mouseY);
										check = 1;
										break;
									}

								}
								if (check == 0)
								{
									if (dataBase->CheckNewStudent(txtArrayAdd[0].getText()) == true) //kiem tra ma sinh vien vua them co trung hay khong
									{
										SinhVien *newSV = new SinhVien;
										newSV->setMaSV(txtArrayAdd[0].getText());
										newSV->setHo(txtArrayAdd[1].getText());
										newSV->setTen(txtArrayAdd[2].getText());
										newSV->setPhai(sex);
										lop->InsertLastSinhVien(newSV);
										closegraph(-1);
										return 1;
									}
									else
									{
										setbkcolor(0);
										setcolor(7);
										settextstyle(0, 0, 0);

										outtextxy(200, 450, "                           ");
										outtextxy(200, 450, "ID hoc sinh da bi trung!");
									}
								}
							}
		}
		for (int i = 0; i < 3; i++)
		{
			if (txtArrayAdd[i].getStatus() == Enter || txtArrayAdd[i].getStatus() == Down)
			{
				txtArrayAdd[i].setStatus(None);
				if (i == 2)
					i = 0;
				else
					i++;
				txtArrayAdd[i].Input(mouseX, mouseY);
				break;
			}
			else
				if (txtArrayAdd[i].getStatus() == Up)
				{
					txtArrayAdd[i].setStatus(None);
					if (i == 0)
						i = 2;
					else
						i--;
					txtArrayAdd[i].Input(mouseX, mouseY);
					break;
				}
		}


		for (int i = 0; i < 3; i++)
		{
			if (txtArrayAdd[i].CheckMouseClick(mouseX, mouseY))
				txtArrayAdd[i].Input(mouseX, mouseY);
		}


	}
		

		
	
}

void DrawFrameStudent(Lop lop, int height, int width)
{
	char nameClass[40];
	strcpy_s(nameClass, _strdup(lop.getMaLop().c_str()));
	outtextxy(height / 2 - 100, 10, nameClass); //hien thi ten lop hoc

												//khung chinh
	setcolor(9);
	setlinestyle(0, 1, 3);
	rectangle(2, 70, height - 15, width - 15);


	setcolor(10);
	setlinestyle(0, 1, 0);
	line(50, 70, 50, width - 80); //duong chua STT
	line(200, 70, 200, width - 80); //duong chua ID
	line(300, 70, 300, width - 80); //duong chua first name
	line(450, 70, 450, width - 80); //duong chua last name
									//chua cac diem mn hoc
	line(500, 70, 500, width - 80);
	line(600, 70, 600, width - 80);
	line(700, 70, 700, width - 80);
	line(800, 70, 800, width - 80);
	line(900, 70, 900, width - 80);
	line(1000, 70, 1000, width - 80);

	setlinestyle(1, 1, 2); //duong thang ngfan cach student va subject
	setcolor(7);
	line(550, 630, 550, 670);

	setcolor(10);
	setlinestyle(0, 1, 1);
	line(2, 120, 1100, 120);
	setlinestyle(0, 1, 2);
	line(2, width - 80, 1100, width - 80); //duong chan duoi

	setlinestyle(0, 1, 2);
	line(1100, 70, 1100, width - 15);  //duong thang tool

									   //cac duong chan ngang
	setcolor(7);
	setlinestyle(2, 1, 1);
	for (int i = 1; i<10; i++)
		line(2, 120 + 50 * i, 1100, 120 + 50 * i);

	setcolor(9);
	settextstyle(0, 0, 0);
	outtextxy(450, 640, "Student");
	outtextxy(590, 640, "Subject");

	settextstyle(0, 0, 3);
	outtextxy(17, 83, "#");
	outtextxy(100, 83, "ID");
	settextstyle(0, 0, 2);
	outtextxy(220, 80, "First");
	outtextxy(220, 100, "Name");
	outtextxy(310, 90, "Last Name");
	outtextxy(455, 90, "Sex");
	char stt[2]; stt[1] = '\0';
	for (int i = 0; i < 10; i++)
	{
		stt[0] = (char)i + 48;
		outtextxy(15, 135 + i * 50, stt);
	}


}

void InitListStudent(TextBox txtArray[10][10]) //khoi tao cho danh sach sinh vien
{
	//khoi tao Id
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][0].Init(52, 122 + (50 * i), 198, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][0].Draw();
	}
	//khoi tao first
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][1].Init(202, 122 + (50 * i), 298, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][1].Draw();
	}

	//khoi tao last
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][2].Init(302, 122 + (50 * i), 448, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 30);
		txtArray[i][2].Draw();
	}

	//khoi tao gioi tinh
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][3].Init(452, 122 + (50 * i), 498, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 5);
		txtArray[i][3].Draw();
	}

	//khoi tao mon hoc thu 1
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][4].Init(502, 122 + (50 * i), 598, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][4].Draw();
	}

	//khoi tao mon hoc thu 2
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][5].Init(602, 122 + (50 * i), 698, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][5].Draw();
	}

	//khoi tao mon hoc thu 3
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][6].Init(702, 122 + (50 * i), 798, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][6].Draw();
	}

	//khoi tao mon hoc thu 4
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][7].Init(802, 122 + (50 * i), 898, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][7].Draw();
	}

	//khoi tao mon hoc thu 5
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][8].Init(902, 122 + (50 * i), 998, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][8].Draw();
	}

	//khoi tao mon hoc thu 6
	for (int i = 0; i < 10; i++)
	{
		txtArray[i][9].Init(1002, 122 + (50 * i), 1098, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		txtArray[i][9].Draw();
	}
}

void LoadDataStudent(Lop lop, SinhVien *current, TextBox txtArray[10][10], MonHoc *DsMon, int nMon, int &indexStudent, int nSubject, int &indexSubject)
{
	indexStudent = 0;
	indexSubject = 0;
	SinhVien *pTemp = current;
	while (pTemp != NULL && indexStudent < 10)
	{
		txtArray[indexStudent][0].setText(_strdup(pTemp->getMaSV().c_str()));
		txtArray[indexStudent][1].setText(_strdup(pTemp->getTen().c_str()));
		txtArray[indexStudent][2].setText(_strdup(pTemp->getHo().c_str()));
		if (pTemp->getPhai() == 0)
			txtArray[indexStudent][3].setText("Nam");// gioi tinh
		else
			if (pTemp->getPhai() == 1)
				txtArray[indexStudent][3].setText("Nu");// gioi tinh
			else
				txtArray[indexStudent][3].setText("Khac");// gioi tinh

		int i = 0;
		while (i < 6)
		{
			if (nSubject + i < nMon)
			{
				for (int u = 0; nSubject + u < nMon && u < 6; u++) //lấy một môn trên thanh tiêu đề kiểm tra với linkList Diem thi
				{
					bool check = false; //kiem tra xem co thi mon do chua
					DiemThi *p = pTemp->firstDiemThi;
					while (p != NULL)
					{
						if (p->getMaMonHoc() == DsMon[nSubject + u].getMaMonHoc())
						{
							txtArray[indexStudent][4 + u].setText(p->getDiem());
							check = true;
							break;
						}

						p = p->pRight;
					}
					if (check == false)
						txtArray[indexStudent][4 + u].setText("Not yet");
				}

			}
			else
			{
				txtArray[indexStudent][4 + i].setText("");
			}
			i++;
		}

		pTemp = pTemp->pRight;
		indexStudent++;
	}

	for (int i = indexStudent; i < 10; i++)
		for (int j = 0; j < 10; j++)
			txtArray[i][j].setText("");

}

void PrintListStudent(Lop lop, int nCurrentStudent, MonHoc *DsMon, int nMon, TextBox txtArray[10][10], int nSubjects, int indexSubjects)
{
	setbkcolor(0);
	settextstyle(0, 0, 0);
	setcolor(YELLOW);
	int i = 0;
	while (i < 6) //xuat tieu de cua mon hoc
	{
		if (nSubjects + i < nMon)
			outtextxy(505 + 100 * i, 90, _strdup(DsMon[nSubjects + i].getMaMonHoc().c_str()));
		else
			outtextxy(505 + 100 * i, 90, "         "); //cho phep 9 ky tu ma mon hoc
		i++;
	}

	for (i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			txtArray[i][j].Draw();

	//hien so trang hien tai tong so trang

	setcolor(7);
	int pageCurrent = nCurrentStudent / 10 + 1;
	string x = to_string(pageCurrent);
	int pageTotal;
	if (lop.getSoSV() % 10 == 0)
		pageTotal = lop.getSoSV() / 10;
	else
		pageTotal = lop.getSoSV() / 10 + 1;

	string y = to_string(pageTotal);
	x += "/";
	x += y;
	outtextxy(230, 640, _strdup(x.c_str()));

	pageCurrent = nSubjects/6 + 1;
	x = to_string(pageCurrent);

	if (nMon % 10 == 0)
		pageTotal = nMon / 6;
	else
		pageTotal = nMon / 6 + 1;

	y = to_string(pageTotal);

	x += "/";
	x += y;

	outtextxy(840, 640, _strdup(x.c_str()));

}

void ChangeStudent(MonHoc *DsMon, int nMon, TextBox &txtChange,int indexRow, int indexColumn, int nSubjects, SinhVien *current)
{
	SinhVien *pTemp = current;
	for (int i = 0; i < indexRow; i++)
	{
		pTemp = pTemp->pRight;
	}

	if (indexColumn == 0)
		pTemp->setMaSV(txtChange.getText());
	else
		if (indexColumn == 1)
			pTemp->setTen(txtChange.getText());
		else
			if (indexColumn == 2)
				pTemp->setHo(txtChange.getText());
			else
				if (indexColumn == 3)
				{
					//set Sex
				}
				else //tu 4 den 10 tao 1 vung nho diem  thi
				{
					char tempID[40];
					strcpy_s(tempID, _strdup(DsMon[nSubjects + indexColumn - 4].getMaMonHoc().c_str()));
					
					DiemThi *i = pTemp->SearchDiem(tempID); //tim xem da thi hay chua

					if (i != NULL) //da co diem
					{
						if (txtChange.getText()[0] == '\0')
						{
							pTemp->DeleteDiem(i);
							txtChange.setText("Not yet");
						}
						else
							i->setDiem(_strdup(txtChange.getText().c_str()));
					}
					else //chua co diem
					{
						if (txtChange.getText()[0] == '\0')
							txtChange.setText("Not yet");
						else
						{
							DiemThi *pDiem = new DiemThi(tempID, _strdup(txtChange.getText().c_str()));
							pTemp->InsertLastDiem(pDiem);
						}
					}
				}
}

void DeleteStudent(SinhVien *&current,Lop &lop, int indexRow)
{
	SinhVien *p = current;

	for (int i = 0; i < indexRow && p!=NULL; i++)
		p = p->pRight;

	if (p == NULL)
		return;

	if (p == current)
	{
		if (current->pRight != NULL)
			current = current->pRight;
		else
			if (current->pLeft != NULL)
			{
				for (int i = 0; i < 10; i++)
					current = current->pLeft;
			}
			else
				current = NULL;
	}
	lop.DeleteSinhVien(p);
}

void ViewClass(Data *&dataBase, int index) //index lớp được chọn để xem
{
	int height = 1300;
	int width = 700;
	int StudentScreen = initwindow(height, width, "");

	Lop *lop = &dataBase->getDanhSachLop()[index];

	DrawFrameStudent(*lop, height, width);

	Button btnAdd(1140, 100, 1250, 140, 5, 6, "Add", 1, 1, 2, 7);
	btnAdd.DrawBetween();

	Button btnChange(1140, 180, 1250, 220, 5, 6, "Change", 1, 1, 2, 7);
	btnChange.DrawBetween();

	Button btnDelete(1140, 260, 1250, 300, 5, 6, "Delete", 1, 1, 2, 7);
	btnDelete.DrawBetween();

	Button btnSave(1140, 340, 1250, 380, 5, 6, "Save", 1, 1, 2, 7);
	btnSave.DrawBetween();

	Button btnClose(1180, 630, 1280, 680, 2, 4, "Close", 1, 1, 2, 7);
	btnClose.DrawBetween();

	Button btnNextStudent(300, 630, 400, 670, 2, 3, "Next", 1, 1, 2, 7);
	btnNextStudent.DrawBetween();

	Button btnBackStudent(100, 630, 200, 670, 2, 3, "Back", 1, 1, 2, 7);
	btnBackStudent.DrawBetween();


	Button btnNextSubject(900, 630, 1000, 670, 2, 3, "Next", 1, 1, 2, 7);
	btnNextSubject.DrawBetween(); 

	Button btnBackSubject(700, 630, 800, 670, 2, 3, "Back", 1, 1, 2, 7);
	btnBackSubject.DrawBetween();

	TextBox txtArray[10][10]; //0 ID, 1 firstname, 2 Last name, 3 Sex, 4 - 10 Subjects
	InitListStudent(txtArray);


	SinhVien *current = dataBase->getDanhSachLop()[index].firstSV; //danh dau vi tri 0, 10,20
	int nCurrentStudent = 0; //danh dau vi tri 0, 10,20
	int indexStudent = 0; //số hàng có thể xuất đc

	int nSubjects = 0; //danh dau chi so de xuat danh sach mon hoc 0, 6, 12
	int indexSubjects = 0; //số cột có thể xuất đc

	int mouseX = -1;
	int mouseY = -1;

	int indexRow = -1; //kiem tra hang 
	int indexColumn = -1; //kiem tra cot

	int tempMon; //chênh lệch môn hiện tại và tổng số môn
	int checkChange = 0; //kiem tra xem da thay doi gi trong danh sach chua

	int ask;

	LoadDataStudent(*lop, current, txtArray, dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexSubjects);
	PrintListStudent(*lop,nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);

	

	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			//btn Add duoc nhan
			if (btnAdd.CheckMouseClick(mouseX, mouseY))
			{
				int x = AddAStudent(dataBase,lop);
				setcurrentwindow(StudentScreen);
				if (x == 1)
				{
					if (lop->getSoSV() % 10 == 0)
						nCurrentStudent = lop->getSoSV() - 10;
					else
						nCurrentStudent = lop->getSoSV() / 10 * 10;

					int n = lop->getSoSV() - nCurrentStudent;
					current = lop->lastSV;
					while (n-- > 1)
						current = current->pLeft;

					LoadDataStudent(*lop, current, txtArray,dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexStudent);
					PrintListStudent(*lop, nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);
					PrintNoteStudent(2);
					checkChange = 1;
				}
				
			}
			else
			//close duoc nhan
			if (btnClose.CheckMouseClick(mouseX, mouseY))
			{
				if (checkChange == 1)
				{
					ask = DoYouWantTo(0);
					setcurrentwindow(StudentScreen);
					if (ask == 1)
					{
						setcurrentwindow(StudentScreen);
						dataBase->SavaDataStudent(lop);
					}
					else
						dataBase->LoadData();
				}
				closegraph(-1);
				return;
			}
			else
			//nut Change duoc nhan
			if (btnChange.CheckMouseClick(mouseX, mouseY) && indexRow != -1)
			{
				if (indexColumn == 0) //id
				{
					string temp = txtArray[indexRow][indexColumn].getText();
					while (true)
					{

						txtArray[indexRow][indexColumn].Input(mouseX, mouseY);
						if ((dataBase->CheckNewStudent(txtArray[indexRow][indexColumn].getText()) || txtArray[indexRow][indexColumn].getText() == temp) && !txtArray[indexRow][indexColumn].CheckEmpty())
							break;
					}

				}
				else
				if (indexColumn < 3) //id, first name, last name
				{
					do {
						txtArray[indexRow][indexColumn].Input(mouseX, mouseY);
					} while (txtArray[indexRow][indexColumn].getText()[0] == '\0');
				}
				else
					if (indexColumn > 3)
					{
						float f1;
						bool checkDiem = false; //neu o do de trong la xoa di o do, xem nhu chua thi
						do {
							txtArray[indexRow][indexColumn].InputNumber(mouseX, mouseY, 5);
							if (txtArray[indexRow][indexColumn].getText()[0] == '\0') //de trong la xoa di, coi nhu chua thi
							{
								checkDiem = true;
								break;
							}
								f1 = strtof(_strdup(txtArray[indexRow][indexColumn].getText().c_str()), NULL);
						} while (f1 >10);

						if(checkDiem ==true) //de trong la xoa di, coi nhu chua thi
							txtArray[indexRow][indexColumn].setText("");
						else
						{
							char number[6];
							sprintf_s(number, "%.2f", f1);
							txtArray[indexRow][indexColumn].setText(number);
						}
					
					}
				
					ChangeStudent(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray[indexRow][indexColumn], indexRow, indexColumn, nSubjects, current);
					txtArray[indexRow][indexColumn].Draw();

				checkChange = 1;
			}
			else
			//nut Save duoc nhan
			if (btnSave.CheckMouseClick(mouseX, mouseY))
			{
				dataBase->SavaDataStudent(lop);
				checkChange = 0;
				PrintNoteStudent(1);
			}
			else//btn DELETE duo nhan
			if (indexRow != -1 && btnDelete.CheckMouseClick(mouseX, mouseY))
			{	
				if (lop->getSoSV() > 0)
				{
					for (int i = 0; i < tempMon; i++) //danh dau 1 day
						txtArray[indexRow][i].Selected(1);

					ask = DoYouWantTo(1);
					setcurrentwindow(StudentScreen);
					if (ask == 1)
					{
						DeleteStudent(current, *lop, indexRow);

						if (lop->getSoSV() == nCurrentStudent && lop->getSoSV() > 0)
							nCurrentStudent -= 10;

						LoadDataStudent(*lop, current, txtArray, dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexSubjects);
						PrintListStudent(*lop, nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);
					}
					for (int i = 0; i < tempMon; i++) //bo danh dau hang vua chon
						txtArray[indexRow][i].UnSelected(1);
				}
				if (ask == 1)
				{
					PrintNoteStudent(0);
					checkChange = 1;
				}
			}
			else
				if (btnBackStudent.CheckMouseClick(mouseX, mouseY))
				{
 					if (nCurrentStudent > 0)
					{
						for (int i = 0; i < 10; i++)
							current = current->pLeft;
						nCurrentStudent -= 10;
						LoadDataStudent(*lop, current, txtArray, dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexSubjects);
						PrintListStudent(*lop, nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);
					}
				}
				else
					if (btnNextStudent.CheckMouseClick(mouseX, mouseY))
					{
						if (nCurrentStudent + 10 < lop->getSoSV())
						{
							nCurrentStudent += 10;
							for (int i = 0; i < 10; i++)
								current = current->pRight;
							LoadDataStudent(*lop, current, txtArray, dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexSubjects);
							PrintListStudent(*lop, nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);
						}
					}
					else
						if (btnBackSubject.CheckMouseClick(mouseX, mouseY))
						{
							if (nSubjects > 0)
							{
								nSubjects -= 6;
								LoadDataStudent(*lop, current, txtArray, dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexSubjects);
								PrintListStudent(*lop, nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);
							}
						}
						else
							if (btnNextSubject.CheckMouseClick(mouseX, mouseY))
							{
								if (nSubjects + 6 < dataBase->getSoMon())
								{
									nSubjects += 6;
									LoadDataStudent(*lop, current, txtArray, dataBase->getDanhSachMon(), dataBase->getSoMon(), indexStudent, nSubjects, indexSubjects);
									PrintListStudent(*lop, nCurrentStudent, dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nSubjects, indexSubjects);
								}
							}

							indexRow = indexColumn = -1;
		}

		//kiem tra co nhan vao danh sach hay khong
		if (dataBase->getSoMon() - nSubjects > 6)
			tempMon = 10;
		else
			tempMon = dataBase->getSoMon() - nSubjects + 4;
		for (int i = 0; i < indexStudent; i++)
		{
			for (int j = 0; j < tempMon; j++)
			{
				if (txtArray[i][j].CheckMouseClick(mouseX, mouseY))
				{
					if (!txtArray[i][j].getCheckMouse()) //neu xuat r thi khoi xuat
						txtArray[i][j].Selected(1);
						indexRow = i; //hang duoc chon
						indexColumn = j; //cot duoc chon
				}
				else
					txtArray[i][j].CheckMouseMove(1);
			}
		}

		if (indexRow >= indexStudent) //kich ngoai danh sach thi gan index = -1
		{
			for (int i = 0; i < tempMon; i++) //bo danh dau hang vua chon
				txtArray[indexRow][i].UnSelected(1);
			indexColumn = -1;
			indexRow = -1;
		}

		//tao hieu ung cho dep thoi 
		btnAdd.CheckMouseMove(0);
		btnChange.CheckMouseMove(0);
		btnDelete.CheckMouseMove(0);
		btnSave.CheckMouseMove(0);
		btnClose.CheckMouseMove(0);
		btnBackStudent.CheckMouseMove(0);
		btnNextStudent.CheckMouseMove(0);
		btnBackSubject.CheckMouseMove(0);
		btnNextSubject.CheckMouseMove(0);

	}
}
