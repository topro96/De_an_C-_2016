#pragma once
#include "ViewClass.h"
#include "ViewSubject.h"


void LoadDataClass(Lop *DsLop, int nLop, TextBox txtArray[10][2], int nCurrent, int &indexCurrentClass)
{
	indexCurrentClass = 0;

	int value = nLop - nCurrent;
	if (value >= 10)
		value = 10;

	int j = nCurrent; //danh sach lop hien tai duox cuat

	while (indexCurrentClass < value)
	{
		txtArray[indexCurrentClass][0].setText(_strdup(DsLop[j].getMaLop().c_str()));
		txtArray[indexCurrentClass][1].setText(_strdup(DsLop[j].getTenLop().c_str()));
		indexCurrentClass++;
		j++;
	}

	while (value < 10)
	{
		txtArray[value][0].setText("");
		txtArray[value][1].setText("");
		value++;
	}
}

void LoadDataSubjects(MonHoc *DsMon, int nMon, TextBox txtArray[10][2], int nCurrent, int &indexCurrentSubject)
{
	indexCurrentSubject = 0;

	int value = nMon - nCurrent;
	if (value >= 10)
		value = 10;
	
	int j = nCurrent; //danh sach lop hien tai duox cuat

	while (indexCurrentSubject < value)
	{
		txtArray[indexCurrentSubject][0].setText(_strdup(DsMon[j].getMaMonHoc().c_str()));
		txtArray[indexCurrentSubject][1].setText(_strdup(DsMon[j].getTenMonHoc().c_str()));
		indexCurrentSubject++;
		j++;
	}

	while (value < 10)
	{
		txtArray[value][0].setText("");
		txtArray[value][1].setText("");
		value++;
	}
}

void PrintListClass(Lop *DsLop, int nLop, TextBox txtArray[10][2], int nCurrent, int indexCurrentClass)
{
	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 2; j++)
		txtArray[i][j].Draw();

	///////////////////xuat so sv hien co
	char total[20];
	setfillstyle(1, 0);

	setbkcolor(0);
	int j = nCurrent;
	for (int i = 0; i < 10; i++, j++)
	{
		bar(605, 125 + 40 * i, 745, 118 + 40 * (i + 1));
		if (i < indexCurrentClass)
		{
			_itoa_s(DsLop[j].getSoSV(), total, 10);
			outtextxy(650, 130 + 40 * i, total);
		}
		else
			outtextxy(650, 130 + 40 * i, "");
	}

	int pageCurrent = nCurrent / 10 + 1;
	string x = to_string(pageCurrent);
	int pageTotal;
	if (nLop % 10 == 0)
		pageTotal = nLop / 10;
	else
		pageTotal = nLop / 10 + 1;

	string y = to_string(pageTotal);
	x += "/";
	x += y;
	outtextxy(330, 555, _strdup(x.c_str()));

}

void PrintListSubjects(MonHoc *DsMon, int nMon, TextBox txtArray[10][2], int nCurrent, int indexCurrentSubjects)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 2; j++)
			txtArray[i][j].Draw();


	setfillstyle(1, 0);
	setbkcolor(0);

	int j = nCurrent;
	for (int i = 0; i < 10; i++, j++)
	{
		bar(605, 125 + 40 * i, 745, 118 + 40 * (i + 1));
		if (i < indexCurrentSubjects)
		{
			outtextxy(650, 130 + 40 * i,_strdup(to_string(DsMon[i].getSoCauHoi()).c_str()));
		}
		else
			outtextxy(650, 130 + 40 * i, "");
	}

	
	int pageCurrent = nCurrent / 10 + 1;
	string x = to_string(pageCurrent);

	int pageTotal;
	if (nMon % 10 == 0)
		pageTotal = nMon / 10;
	else
		pageTotal = nMon / 10 + 1;
	
	string y = to_string(pageTotal);
	x += "/";
	x += y;
	outtextxy(330, 555, _strdup(x.c_str()));

}

void DrawFrameTeacherScreen()
{
	//khung chinh
	setcolor(9);
	setlinestyle(0, 1, 3);
	rectangle(2, 2, 750, 585);

	//khung chua tool
	setcolor(11);
	setlinestyle(1, 1, 2);
	rectangle(755, 2, 985, 460);

	//dung thang ngan danh sach lop button class..
	setcolor(9);
	setlinestyle(0, 1, 3);
	line(2, 65, 750, 65);


	//duong ke ngang cua danh sach
	setcolor(9);
	setlinestyle(1, 1, 0);
	for (int i = 0; i < 11; i++)
		line(4, 120 + 40 * i, 750, 120 + 40 * i);

	//duong ke doc
	setcolor(RED);
	setlinestyle(0, 1, 2);
	line(60, 65, 60, 520); //stt
	line(250, 65, 250, 520); //id
	line(600, 65, 600, 520); //name

							 //cac text tiêu đề như STT, ID...
	setcolor(WHITE);
	settextstyle(0, 0, 3);
	outtextxy(22, 80, "#");
	outtextxy(120, 80, "ID");
	outtextxy(360, 80, "Name");
	outtextxy(620, 80, "Total");

	//xuat STT
	char stt[2]; stt[1] = '\0';
	for (int i = 0; i < 10; i++)
	{

		stt[0] = (char)i + 48;
		outtextxy(20, 130 + 40 * i, stt);
	}
}

int Add(Data *&dataBase, int flag)
{
	int mouseX = -1, mouseY = -1;
	initwindow(600, 400, "Add a class", 0, 0, 0, 0);

	settextstyle(0, 0, 2);
	outtextxy(45, 105, "ID:");
	outtextxy(20, 160, "Name:");

	TextBox txtID(100, 90, 500, 130, 5, 6, "", 0, 0, 1, 7, 20);
	txtID.Draw();
	TextBox txtName(100, 150, 500, 190, 5, 6, "", 0, 0, 1, 7, 40);
	txtName.Draw();

	Button btnAdd(250, 220, 350, 280, 5, 2, "Add", 3, 1, 1, 6);
	btnAdd.DrawBetween();

	Button btnCancel(480, 340, 595, 396, 8, 4, "Cancel", 2, 1, 1, 2);
	btnCancel.DrawBetween();


	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
		}

		if (txtID.CheckMouseClick(mouseX, mouseY) || txtName.getStatus() != None)
		{
			txtID.Input(mouseX, mouseY);
			txtName.setStatus(None);
		}
		else
			if (txtName.CheckMouseClick(mouseX, mouseY) || txtID.getStatus() != None)
			{
				txtName.Input(mouseX, mouseY);
				txtID.setStatus(None);
			}

		if (btnAdd.CheckMouseClick(mouseX, mouseY) == 1) //kiem tra nhan log in
		{
			if (txtID.getText()[0] == '\0') //id trong
				txtID.Input(mouseX, mouseY);
			else
				if (txtName.getText()[0] == '\0') //pass trong
					txtName.Input(mouseX, mouseY);
				else
				{
					if (flag == 0)
					{
						if (dataBase->CheckNewClass(txtID.getText()))
						{
							dataBase->AddClass(txtID.getText(), txtName.getText());
							closegraph(-1);
							return 1;
						}
						else
						{
							setbkcolor(0);
							setcolor(7);
							settextstyle(0, 0, 0);
							
							outtextxy(200, 350, "                           ");
							outtextxy(200, 350, "ID lop hoc da bi trung!");
						}
					}
					else
					{
						if (dataBase->CheckNewSubject(txtID.getText()))
						{
							dataBase->AddSubject(txtID.getText(), txtName.getText());
							closegraph(-1);
							return 1;
						}
						else
						{
							setbkcolor(0);
							setcolor(7);
							settextstyle(0, 0, 0);

							outtextxy(200, 350, "                           ");
							outtextxy(200, 350, "ID mon hoc da bi trung!");
						}
					}
					
					
				}
		}

		if (txtID.getText()[0] == '\0') //id trong
			txtID.Input(mouseX, mouseY);
		else
			if (txtName.getText()[0] == '\0') //pass trong
				txtName.Input(mouseX, mouseY);

		if (btnCancel.CheckMouseClick(mouseX, mouseY))
		{
			closegraph(-1);
			return 0;
		}

	}
	
}

//0 da xoa, 1 da luu, 2 da them
void PrintNoteTeacher(const int x)
{
	
	settextstyle(0, 0, 0);
	setcolor(0);
	setbkcolor(0);
    
	outtextxy(830, 500, "         ");
	setcolor(7);
	setbkcolor(0);
	if (x == 0)
		outtextxy(830, 500, "Da xoa!");
	if (x == 1)
		outtextxy(830, 500, "Da luu!");
	if (x == 2)
		outtextxy(830, 500, "Da them!");

	if (x == -1)
		outtextxy(830, 500, "         ");

}

void TeacherScreen(Data *&dataBase)
{
	int teacherScreen = initwindow(1000, 600, "TeacherScreen", 0, 0);

	//setbkcolor(9); cleardevice();
	DrawFrameTeacherScreen();

	//Cac Button va TextBox
	Button btnClass(230, 15, 330, 55, 5, 6, "Class", 2, 1, 2, 7);
	btnClass.DrawBetween();

	Button btnSubjects(340, 15, 480, 55, 5, 6, "Subjects", 2, 1, 2, 7);
	btnSubjects.DrawBetween();


	TextBox txtFind(760, 20, 980, 60, 2, 3, "", 0, 0, 1, 16, 20); //txt tìm kiếm
	txtFind.Draw();

	Button btnFind(800, 70, 950, 100, 2, 3, "Find", 1, 1, 2, 7); //button tim kiem
	btnFind.DrawBetween();

	Button btnAdd(800, 150, 950, 180, 2, 3, "Add", 1, 1, 2, 7); //button add
	btnAdd.DrawBetween();

	Button btnView(800, 200, 950, 230, 2, 3, "View", 1, 1, 2, 7); //button view
	btnView.DrawBetween();

	Button btnChange(800, 250, 950, 280, 2, 3, "Change", 1, 1, 2, 7); //button change
	btnChange.DrawBetween();

	Button btnDelete(800, 330, 950, 360, 2, 4, "Delete", 1, 1, 2, 7); //button delete
	btnDelete.DrawBetween();

	Button btnSave(800, 420, 950, 450, 2, 14, "Save", 1, 1, 2, 7); //button save
	btnSave.DrawBetween();

	Button btnExit(900, 550, 990, 590, 2, 4, "Exit", 1, 1, 2, 7); //button save
	btnExit.DrawBetween();

	Button btnBack(200, 550, 300, 580, 5, 6, "Back", 1, 1, 2, 7); //nut chuyen trang
	btnBack.DrawBetween();

	Button btnNext(400, 550, 500, 580, 5, 6, "Next", 1, 1, 2, 7); //nut chuyen trang
	btnNext.DrawBetween();

	TextBox txtArray[10][2];

	
	for (int i = 0; i < 10; i++) //khoi tao cho ID
		txtArray[i][0].Init(62, 125 + 40 * i, 245, 118 + 40 * (i + 1),7, 0, 8, "", 0, 0, 0, 0, 20);

	
	for (int i = 0; i < 10; i++) //khoi tao cho name
		txtArray[i][1].Init(255, 125 + 40 * i, 595, 118 + 40 * (i + 1), 7,0, 8, "", 0, 0, 0, 0, 40);


	int nCurrentClass = 0; //danh dau chi so de xuat danh sach lop hoc 0, 10, 20,
	int nCurrentSubjects = 0;// mon hoc

	int mouseX = -1;
	int mouseY = -1;

	int indexColumn = -1; //kiem tra hang 
	int indexRow = -1; //kiem tra cot

	int indexCurrentClass = 0; //so hang textbox hien co cua 1 trang
	int indexCurrentSubjects = 0; //so hang textbox hien co cua 1 trang

	int flag = 0; //kiem tra xem dang o class hay subjects
	int checkChangeClass = 0; //kiem tra xem da thay doi gi trong danh sach lop hoc chua chua
	int checkChangeSubject = 0;
	int ask;
	int value;

	LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
	PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
	btnClass.Selected(0);

	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			if (btnClass.CheckMouseClick(mouseX, mouseY) == 1 && flag != 0) //xem click btnclass hay ko
			{
				flag = 0;
				btnClass.Selected(0);
				LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
				PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
			}

			if (btnSubjects.CheckMouseClick(mouseX, mouseY) == 1 && flag != 1)
			{
				flag = 1;
				btnSubjects.Selected(0);
				LoadDataSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
				PrintListSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
			}

			//btn Add duoc nhan
			if (btnAdd.CheckMouseClick(mouseX, mouseY))
			{
				if (flag == 0)
				{
					int x = Add(dataBase, 0);
					setcurrentwindow(teacherScreen);
					
					if (x == 1) //them thanh cong
					{
						if (dataBase->getSoLop() % 10 == 0)
							nCurrentClass = dataBase->getSoLop() - 10;
						else
							nCurrentClass = dataBase->getSoLop() / 10 * 10;
						
						LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
						PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
						checkChangeClass = 1;
					}
				}
				else
				{
					int x =	Add(dataBase,1);
					setcurrentwindow(teacherScreen);
					if (x == 1)
					{
						if (dataBase->getSoMon() % 10 == 0)
							nCurrentSubjects = dataBase->getSoMon() - 10;
						else
							nCurrentSubjects = dataBase->getSoMon() / 10 * 10;
						LoadDataSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
						PrintListSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
						checkChangeSubject = 1;
					}
				}
				
			}
			else//exit duoc nhan
			if (btnExit.CheckMouseClick(mouseX, mouseY))
			{
				if (checkChangeClass || checkChangeSubject)
				{
					if (DoYouWantTo(0) == 1)
					{
						dataBase->XoaCacLopRac();
						dataBase->XoaCacMonRac();
						dataBase->SaveDataClass();
						dataBase->SaveDataMonHoc();
					}
				}
				closegraph(-1);
				return;
			}
			else//btn tim kiem duoc nhan
			if (txtFind.CheckMouseClick(mouseX, mouseY)) //nhan de nhap thong tin can tim kiem
			{
				txtFind.Input(mouseX, mouseY);
			}
			else
			if (btnChange.CheckMouseClick(mouseX, mouseY) && indexRow != -1)
			{
				if (flag == 0)
				{
					if (indexColumn == 0) //kiểm tra id
					{
						string temp = txtArray[indexRow][0].getText();
						while (true)
						{
							txtArray[indexRow][0].Input(mouseX, mouseY);
							if ((temp == txtArray[indexRow][0].getText() || dataBase->CheckNewClass(txtArray[indexRow][0].getText())) && !txtArray[indexRow][0].CheckEmpty())
								break;
						}
						dataBase->getDanhSachLop()[nCurrentClass + indexRow].setMaLop(txtArray[indexRow][0].getText());
					}
					else
					{
						while (true)
						{
							txtArray[indexRow][1].Input(mouseX, mouseY);
							if (txtArray[indexRow][1].CheckEmpty() == false)
								break;
						}
						dataBase->getDanhSachLop()[nCurrentClass + indexRow].setTenLop(txtArray[indexRow][1].getText());
					}
					checkChangeClass = 1;
				}
				else
				{
					if (indexColumn == 0) //kiểm tra id
					{
						string temp = txtArray[indexRow][0].getText();
						while (true)
						{
							txtArray[indexRow][0].Input(mouseX, mouseY);
							if ((temp == txtArray[indexRow][0].getText() || dataBase->CheckNewSubject(txtArray[indexRow][0].getText())) && !txtArray[indexRow][0].CheckEmpty())
								break;
						}
						dataBase->getDanhSachMon()[nCurrentSubjects + indexRow].setMaMonHoc(txtArray[indexRow][0].getText());
					}
					else
					{
						while (true)
						{
							txtArray[indexRow][1].Input(mouseX, mouseY);
							if (txtArray[indexRow][1].CheckEmpty() == false)
								break;
						}
						dataBase->getDanhSachMon()[nCurrentSubjects + indexRow].setTenMonHoc(txtArray[indexRow][1].getText());
					}
				}
				checkChangeSubject = 1;
			}
			else//nut Save duoc nhan
			if (btnSave.CheckMouseClick(mouseX, mouseY))
			{
				if (flag == 0)
				{
					dataBase->XoaCacLopRac();
					dataBase->SaveDataClass();
					dataBase->LayMaCacLop();
					checkChangeClass = 0;
				}
				else
				{
					dataBase->XoaCacMonRac();
					dataBase->SaveDataMonHoc();
					dataBase->LayMaCacMon();
					checkChangeSubject = 0;
				}
				PrintNoteTeacher(1);
			}
			else
			//btn DELETE duo nhan
			if (indexRow != -1 && btnDelete.CheckMouseClick(mouseX, mouseY))
			{
				txtArray[indexRow][0].Selected(1);
				txtArray[indexRow][1].Selected(1);
				ask = DoYouWantTo(1);
				setcurrentwindow(teacherScreen);
				if (ask == 1)
				{
					if (flag == 0)
					{
						if (nCurrentClass + indexRow < dataBase->getSoLop())
						{
							dataBase->DeleteClass(nCurrentClass + indexRow);

							if (dataBase->getSoLop() == nCurrentClass && dataBase->getSoLop() > 0)
								nCurrentClass -= 10;

							LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
							PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
							checkChangeClass = 1;
						}
					}
					else
					{
						
						if (nCurrentSubjects + indexRow < dataBase->getSoMon())
						{
							//string maMon = dataBase->getDanhSachMon()[nCurrentSubjects + indexRow].getMaMonHoc();
							dataBase->DeleteSubject(nCurrentSubjects + indexRow);
							//dataBase->CleanClear(maMon);
							if (dataBase->getSoMon() == nCurrentSubjects && dataBase->getSoMon() > 0)
								nCurrentSubjects -= 10;

							LoadDataSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
							PrintListSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
							checkChangeSubject = 1;
						}
					}
					
					PrintNoteTeacher(0);
				}
				txtArray[indexRow][0].UnSelected(1);
				txtArray[indexRow][1].UnSelected(1);
			}
			else//btn next
			if (btnNext.CheckMouseClick(mouseX, mouseY))
			{
				if (flag == 0)
				{
					if (nCurrentClass + 10 < dataBase->getSoLop())
					{
						nCurrentClass += 10;
						LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
						PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
						
					}
				}
				else
				{
					if (nCurrentSubjects + 10 < dataBase->getSoMon())
					{
						nCurrentSubjects += 10;
						LoadDataSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
						PrintListSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
					}
				}
			}
			else//btn back
			if (btnBack.CheckMouseClick(mouseX, mouseY))
			{
				if (flag == 0)
				{
					if (nCurrentClass > 0)
					{
						nCurrentClass -= 10;
						LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
						PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
					}
				}
				else
				{
					if (nCurrentSubjects > 0)
					{
						nCurrentSubjects -= 10;
						LoadDataSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
						PrintListSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
					}
				}
			}
			else//nut view duoc nhan
			if (btnView.CheckMouseClick(mouseX, mouseY) && indexRow != -1)
			{
				if (flag == 0)
				{
					dataBase->SaveDataClass();
					HWND window = FindWindow(NULL, "TeacherScreen");
					ShowWindow(window, SW_HIDE); //an teacher screen

					ViewClass(dataBase, nCurrentClass + indexRow);

					ShowWindow(window, SW_SHOW);
					setcurrentwindow(teacherScreen);
					
					LoadDataClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
					PrintListClass(dataBase->getDanhSachLop(), dataBase->getSoLop(), txtArray, nCurrentClass, indexCurrentClass);
				}
				else
				{
					dataBase->SaveDataMonHoc();
					HWND window = FindWindow(NULL, "TeacherScreen");
					ShowWindow(window, SW_HIDE); //an teacher screen
					ViewSubject( dataBase, nCurrentSubjects + indexRow);
					ShowWindow(window, SW_SHOW);
					setcurrentwindow(teacherScreen);
					LoadDataSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
					PrintListSubjects(dataBase->getDanhSachMon(), dataBase->getSoMon(), txtArray, nCurrentSubjects, indexCurrentSubjects);
				}
			}

			indexColumn = indexRow = -1;
		}
		if (flag != 0)
			btnClass.CheckMouseMove(0); //0 la xuat chinh giua, 1 va trai
		else
			btnSubjects.CheckMouseMove(0);

		
		//kiem tra co nhan vao danh sach hay khong
		if (flag == 0)
			value = indexCurrentClass;
		else
			value = indexCurrentSubjects ;
		for (int i = 0; i < value; i++)
			for (int j = 0; j < 2; j++)
			{
				if (txtArray[i][j].CheckMouseClick(mouseX, mouseY))
				{
					if (!txtArray[i][j].getCheckMouse())
						txtArray[i][j].Selected(1);
					indexRow = i;
					indexColumn = j;
				}
				else
					txtArray[i][j].CheckMouseMove(1);
			}
		
		if (flag == 0)
		{
			if (indexRow >= indexCurrentClass)
			{
				txtArray[indexRow][0].UnSelected(1);
					txtArray[indexRow][1].UnSelected(1);
					indexColumn = -1;
					indexRow = -1;
			}
		}
		else
		{
			if (indexRow >= indexCurrentSubjects)
			{
				txtArray[indexRow][0].UnSelected(1);
				txtArray[indexRow][1].UnSelected(1);
				indexColumn = -1;
				indexRow = -1;
			}
		}


		//tao hieu ung cho dep thoi
		btnAdd.CheckMouseMove(0);
		btnFind.CheckMouseMove(0);
		btnChange.CheckMouseMove(0);
		btnDelete.CheckMouseMove(0);
		btnView.CheckMouseMove(0);
		btnSave.CheckMouseMove(0);
		txtFind.CheckMouseMove(1);
		btnExit.CheckMouseMove(0);
		btnNext.CheckMouseMove(0);
		btnBack.CheckMouseMove(0);

	}
	closegraph(-1);
}
