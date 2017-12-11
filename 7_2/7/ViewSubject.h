#pragma once

#pragma once
#include "TeacherScreen.h"
#include <thread>

using namespace std;


void PrintQuestionList(MonHoc monHoc, Button arrayButton[10][2], int nCauHoi)
{
	for (int i = 0; i < 10; i++)
	{
		arrayButton[i][0].DrawLeft();
		arrayButton[i][1].DrawLeft();
	}

	int pageCurrent = nCauHoi / 10 + 1;
	string x = to_string(pageCurrent);
	int pageTotal;
	if (monHoc.getSoCauHoi() % 10 == 0)
		pageTotal = monHoc.getSoCauHoi() / 10;
	else
		pageTotal = monHoc.getSoCauHoi() / 10 + 1;

	string y = to_string(pageTotal);
	x += "/";
	x += y;
	setcolor(7);
	setbkcolor(0);
	outtextxy(530, 640, _strdup(x.c_str()));
}

void LoadIndexFromTreeToArray(note<CauHoi> *root, MyArray *&myArray)
{
	if (root!=NULL)
	{
		LoadIndexFromTreeToArray(root->_left,myArray);
		myArray->Insert(root->_key);
		LoadIndexFromTreeToArray(root->_right, myArray);
	}
}

void LoadDataFormTreeToButton(AVL<CauHoi> *tree, MyArray *&myArray, Button arrayButton[10][2], int nCauHoi,int &intdexCurrent)
{
	intdexCurrent = 0; //số hàng xuất được trong 9 hàng trên màn hình
	int value = myArray->index - nCauHoi;

	if (value >= 10) //lấy chỉ số xuất
		value = 10;
	
	string id; //lay id
	string content; //lay noi dung
	note<CauHoi> *p;
	int x; //lay chi so trong indexarray

	while (intdexCurrent < value)
	{
		x =myArray->myArray[nCauHoi + intdexCurrent];
		p = tree->Search(x, tree->_root);
		if (p != NULL)
		{
			arrayButton[intdexCurrent][0].setText(to_string(p->_data->getID()));
			string noiDung = p->_data->getNoiDung();
			noiDung += "...";
			arrayButton[intdexCurrent][1].setText(noiDung);
		}
		intdexCurrent++;
	}

	while (value < 10)
	{
		arrayButton[value][0].setText("");
		arrayButton[value][1].setText("");
		value++;
	}

}

void DrawFrameSubjects(int height, int width)
{
	
	outtextxy(height / 2 - 100, 10, ""); //hien thi ten lop hoc
	//khung chinh
	setcolor(9);
	setlinestyle(0, 1, 3);
	rectangle(2, 70, height - 15, width - 15);

	setcolor(10);
	setlinestyle(0, 1, 0);
	line(50, 70, 50, width - 80); //duong chua STT
	line(200, 70, 200, width - 80); //duong chua ID

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
	setbkcolor(0);

	settextstyle(0, 0, 3);
	outtextxy(17, 83, "#");
	outtextxy(100, 83, "ID");
	settextstyle(0, 0, 2);
	
	outtextxy(600, 90, "Content");
	char stt[2]; stt[1] = '\0';
	for (int i = 0; i < 10; i++)
	{
		stt[0] = (char)i + 48;
		outtextxy(15, 135 + i * 50, stt);
	}


}

//them 1 cau hoi cho mon hoc
int AddCauHoi(MonHoc &monHoc, MyArray *&myArray)
{
	int mouseX = -1, mouseY = -1;
	initwindow(700, 600, "Add a question", 0, 0, 0, 0);
	
	int id = myArray->getRandFree();
	 
	Button btnID;
	btnID.Init(110 , 30, 300, 70,0, 5, 6, "", 0, 0, 1, 7, 20);
	btnID.setText(to_string(id));
	btnID.DrawBetween();

	setbkcolor(0);
	setcolor(7);
	settextstyle(0, 0, 2);
	outtextxy(60, 45, "ID:");

	Button btnRoll;
	btnRoll.Init(350, 30, 450, 70,0, 5, 6, "Roll", 1, 1, 1, 7, 20);
	btnRoll.DrawBetween();

	setbkcolor(0);
	settextstyle(0, 0, 0);
	outtextxy(20, 140, "Content:");
	TextBox txtArray[5]; //0 la noi dung, con lai la cau tra loi

	txtArray[0].Init(110, 100, 600, 200,0, 5, 6, "", 0, 0, 1, 7, 40);
	txtArray[0].Draw();
	for (int i = 1; i < 5; i++)
	{
		txtArray[i].Init(110, 170 + 60 * i, 600, 210 + 60 * i,0, 7, 9, "", 0, 0, 1, 7, 40);
		txtArray[i].Draw();
	}
		

	Button btnArrayAnswer[4]; //0-3 la abcd
	string x = "A";
	for (int i = 0; i < 4; i++)
	{
		btnArrayAnswer[i].Init(10, 230 + 60 * i, 80, 270 + 60 * i,7, 5, 6, x, 0, 0, 1, 7, 40);
		x[0] += 1;
		btnArrayAnswer[i].DrawBetween();
	}


	setbkcolor(0);
	settextstyle(0, 0, 0);
	outtextxy(20, 480, "Result:");
	Button btnDapAn;
	btnDapAn.Init(110, 470, 180, 510,0, 7, 9, "", 0, 0, 1, 7, 40);
	btnDapAn.DrawBetween();

	Button	btnAdd;
	btnAdd.Init(300, 470, 400, 530, 5, 6,7, "Add", 1, 1, 1, 7, 40);
	btnAdd.DrawBetween();

	Button btnCancel;
	btnCancel.Init(600, 540, 690, 590,0, 5, 4, "Cancel", 0, 0, 1, 7, 20);
	btnCancel.DrawBetween();

	while (true)
	{

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			//Cancel
			if (btnCancel.CheckMouseClick(mouseX, mouseY) == 1)
			{
				closegraph(-1);
				return 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (txtArray[i].CheckMouseClick(mouseX, mouseY) == 1)
					txtArray[i].Input(mouseX, mouseY);
			}

			for (int i = 0; i < 4; i++)
			{
				if (btnArrayAnswer[i].CheckMouseClick(mouseX, mouseY) == 1)
				{
					btnDapAn.setText(btnArrayAnswer[i].getText());
					btnDapAn.DrawBetween();
				}
			}

			if (btnRoll.CheckMouseClick(mouseX, mouseY))
			{
				id = myArray->getRandFree();
				btnID.setText(to_string(myArray->myArray[id]));
				btnID.DrawBetween();
			}

			if (btnAdd.CheckMouseClick(mouseX, mouseY) == 1)
			{
				int check = true;
				for (int i = 0; i < 5; i++)
				{
					if (txtArray[i].CheckEmpty() == 1)
					{
						check = false;
						break;
					}
				}
				if (btnDapAn.CheckEmpty() == 1)
					check = false;

				if (check == true)
				{
					CauHoi *p = new CauHoi();
					p->setID(myArray->myArray[id]);
					p->setNoiDung(txtArray[0].getText());
					p->setAnswer(txtArray[1].getText(), txtArray[2].getText(), txtArray[3].getText(), txtArray[4].getText());
					int dapAn = (int)(btnDapAn.getText()[0] - 65);
					p->setDapAn(dapAn);

					monHoc.InsertQuestion(p); //thêm câu hỏi vào cây
					myArray->Insert(id); //thêm id vào phần đã chọn
					closegraph(-1);
					return 1;
				}
			}
		}
	}
	closegraph(-1);
	return 1;
}

int ChangeCauHoi(MonHoc &monHoc, MyArray *&myArray,int nCauHoi, int indexRow)
{
	int mouseX = -1, mouseY = -1;
	initwindow(700, 600, "Change a question", 0, 0, 0, 0);

	CauHoi *p = monHoc.Search(myArray->myArray[nCauHoi + indexRow]);
	if (p == NULL)
		return 0;

	int id = p->getID();
	Button btnID;
	btnID.Init(110, 30, 300, 70, 0, 5, 6, "", 0, 0, 1, 7, 20);
	btnID.setText(to_string(id));
	btnID.DrawBetween();


	setbkcolor(0);
	setcolor(7);
	settextstyle(0, 0, 2);
	outtextxy(60, 45, "ID:");

	setbkcolor(0);
	settextstyle(0, 0, 0);
	outtextxy(20, 140, "Content:");
	TextBox txtArray[5]; //0 la noi dung, con lai la cau tra loi

	txtArray[0].Init(110, 100, 600, 200, 0, 5, 6, p->getNoiDung(), 0, 0, 1, 7, 40);
	txtArray[0].Draw();
	for (int i = 1; i < 5; i++)
		txtArray[i].Init(110, 170 + 60 * i, 600, 210 + 60 * i, 0, 7, 9, "", 0, 0, 1, 7, 40);
	
	txtArray[1].setText(p->getAnswer()[0]); //dap an a
	txtArray[2].setText(p->getAnswer()[1]); //dap an a
	txtArray[3].setText(p->getAnswer()[2]); //dap an a
	txtArray[4].setText(p->getAnswer()[3]); //dap an a

	for (int i = 1; i < 5; i++)
		txtArray[i].Draw();

	Button btnArrayAnswer[4]; //0-3 la abcd
	string x = "A";
	for (int i = 0; i < 4; i++)
	{
		btnArrayAnswer[i].Init(10, 230 + 60 * i, 80, 270 + 60 * i, 7, 5, 6, x, 0, 0, 1, 7, 40);
		x[0] += 1;
		btnArrayAnswer[i].DrawBetween();
	}


	setbkcolor(0);
	settextstyle(0, 0, 0);
	outtextxy(20, 480, "Result:");
	Button btnDapAn;
	
	string dapAn[4] = { "A","B","C","D" };

	btnDapAn.Init(110, 470, 180, 510, 0, 7, 9, dapAn[p->getDapAn()] ,0, 0, 1, 7, 40);
	btnDapAn.DrawBetween();

	Button	btnChange;
	btnChange.Init(300, 470, 400, 530, 5, 6, 7, "Change", 1, 1, 1, 7, 40);
	btnChange.DrawBetween();

	Button btnCancel;
	btnCancel.Init(600, 540, 690, 590, 0, 5, 4, "Cancel", 0, 0, 1, 7, 20);
	btnCancel.DrawBetween();

	while (true)
	{

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			//Cancel
			if (btnCancel.CheckMouseClick(mouseX, mouseY) == 1)
			{
				closegraph(-1);
				return 0;
			}

			for (int i = 0; i < 5; i++)
			{
				if (txtArray[i].CheckMouseClick(mouseX, mouseY) == 1)
					txtArray[i].Input(mouseX, mouseY);
			}

			for (int i = 0; i < 4; i++)
			{
				if (btnArrayAnswer[i].CheckMouseClick(mouseX, mouseY) == 1)
				{
					btnDapAn.setText(btnArrayAnswer[i].getText());
					btnDapAn.DrawBetween();
				}
			}

			if (btnChange.CheckMouseClick(mouseX, mouseY) == 1)
			{
				int check = true;
				for (int i = 0; i < 5; i++)
				{
					if (txtArray[i].CheckEmpty() == 1)
					{
						check = false;
						break;
					}
				}
				if (btnDapAn.CheckEmpty() == 1)
					check = false;

				if (check == true)
				{
					p->setNoiDung(txtArray[0].getText());
					p->setAnswer(txtArray[1].getText(), txtArray[2].getText(), txtArray[3].getText(), txtArray[4].getText());
					int dapAn = (int)(btnDapAn.getText()[0] - 65);
					p->setDapAn(dapAn);
					closegraph(-1);
					return 1;
				}
			}
		}
	}
	closegraph(-1);
	return 0;
}

//Trả về 1 nếu thay đổi và 0...
int ViewSubject(Data *&dataBase, int index)
{
	int height = 1300;
	int width = 700;
	int SubjectScreen = initwindow(height, width, "");

	Button btnAdd(1140, 100, 1250, 140, 5, 6, "Add", 1, 1, 2, 7);
 	btnAdd.DrawBetween();

	Button btnView(1140, 180, 1250, 220, 5, 6, "View", 1, 1, 2, 7);
	btnView.DrawBetween();

	Button btnDelete(1140, 260, 1250, 300, 5, 6, "Delete", 1, 1, 2, 7);
	btnDelete.DrawBetween();

	Button btnSave(1140, 340, 1250, 380, 5, 6, "Save", 1, 1, 2, 7);
	btnSave.DrawBetween();

	Button btnClose(1180, 630, 1280, 680, 2, 4, "Close", 1, 1, 2, 7);
	btnClose.DrawBetween();

	Button btnNext(600, 630, 700, 670, 2, 3, "Next", 1, 1, 2, 7);
	btnNext.DrawBetween();

	Button btnBack(400, 630, 500, 670, 2, 3, "Back", 1, 1, 2, 7);
	btnBack.DrawBetween();

	DrawFrameSubjects(height, width);

	Button btnArray[10][2];

	for (int i = 0; i < 10; i++)
	{
		btnArray[i][0].Init(52, 122 + (50 * i), 198, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 20);
		btnArray[i][1].Init(202, 122 + (50 * i), 1098, 168 + (50 * i),7, 0, 8, "", 0, 0, 0, 0, 100);
		btnArray[i][0].DrawBetween();
		btnArray[i][1].DrawBetween();
	}

	
	MyArray *myArray = new MyArray;

	int mouseX = -1;
	int mouseY = -1;
	int checkScreen = 0; //
	int checkChange = 0;//kiem tra xem thay doi de luu
	int nCauHoi = 0;//lấy mốc để xuất 0,10, 20
	int indexCurrent; //số hàng có thể xuất trong 9 hàng
	int indexRow = -1; //lưu lại hàng được chọn

	MonHoc *monHoc = &dataBase->getDanhSachMon()[index];

	LoadIndexFromTreeToArray(monHoc->treeCauHoi->_root, myArray);

	LoadDataFormTreeToButton(monHoc->treeCauHoi, myArray, btnArray, nCauHoi, indexCurrent);

	PrintQuestionList(*monHoc, btnArray, nCauHoi);

	while (true)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

			//them 1 cau hoi
			if (btnAdd.CheckMouseClick(mouseX, mouseY) == 1)
			{
				int x = AddCauHoi(*monHoc, myArray);

				setcurrentwindow(SubjectScreen);
				if (x == 1)
				{
					if (monHoc->getSoCauHoi() % 10 == 0)
						nCauHoi = monHoc->getSoCauHoi() - 10;
					else
						nCauHoi = monHoc->getSoCauHoi() / 10 * 10;
					
					LoadDataFormTreeToButton(monHoc->treeCauHoi, myArray, btnArray, nCauHoi, indexCurrent);
					PrintQuestionList(*monHoc, btnArray, nCauHoi);
					checkChange = 1;
				}

			}
			else //Close
				if (btnClose.CheckMouseClick(mouseX, mouseY))
				{
					if (checkChange)
					{
						int x = DoYouWantTo(0);
						setcurrentwindow(SubjectScreen);
						if (x == 1)
							dataBase->SaveDataCauHoi(monHoc);
						else
							dataBase->LoadData();

						checkScreen = x;
					}
					closegraph(-1);
					return checkScreen;
				}
				else //luu
					if (btnSave.CheckMouseClick(mouseX, mouseY))
					{
						dataBase->SaveDataCauHoi(monHoc);
						checkScreen = 1;
						checkChange = 0;
					}
					else //btn Next duoc nhan
						if (btnNext.CheckMouseClick(mouseX, mouseY))
						{
							if (nCauHoi + 10 < monHoc->getSoCauHoi())
							{
								nCauHoi += 10;
								LoadDataFormTreeToButton(monHoc->treeCauHoi, myArray, btnArray, nCauHoi, indexCurrent);
								PrintQuestionList(*monHoc, btnArray, nCauHoi);
							}
						}
						else//btn Back duoc nhan
							if (btnBack.CheckMouseClick(mouseX, mouseY))
							{
								if (nCauHoi > 0)
								{
									nCauHoi -= 10;
									LoadDataFormTreeToButton(monHoc->treeCauHoi, myArray, btnArray, nCauHoi, indexCurrent);
									PrintQuestionList(*monHoc, btnArray, nCauHoi);
								}
							}
							else //xem chi tiết và change
								if (btnView.CheckMouseClick(mouseX, mouseY) && indexRow != -1)
								{
									int x = ChangeCauHoi(*monHoc, myArray, nCauHoi, indexRow);
									setcurrentwindow(SubjectScreen);
									if (x == 1)
									{
										LoadDataFormTreeToButton(monHoc->treeCauHoi, myArray, btnArray, nCauHoi, indexCurrent);
										PrintQuestionList(*monHoc, btnArray, nCauHoi);
										checkChange = 1;
									}
								}
								else //Xoa
									if (btnDelete.CheckMouseClick(mouseX, mouseY) && indexRow != -1)
									{
										int key = myArray->myArray[nCauHoi + indexRow];
										myArray->Delete(nCauHoi + indexRow);
										monHoc->DeleteQuestion(key);

										if (monHoc->getSoCauHoi() == nCauHoi && monHoc->getSoCauHoi() > 0)
											nCauHoi -= 10;

										LoadDataFormTreeToButton(monHoc->treeCauHoi, myArray, btnArray, nCauHoi, indexCurrent);
										PrintQuestionList(*monHoc, btnArray, nCauHoi);
										checkChange = 1;

										btnArray[indexRow][0].UnSelected(1);
										btnArray[indexRow][1].UnSelected(1);
									}
			 indexRow = -1;
		}

		for (int i = 0; i < indexCurrent; i++)
		{
			if (btnArray[i][0].CheckMouseClick(mouseX, mouseY) || btnArray[i][1].CheckMouseClick(mouseX, mouseY))
			{
				if (!btnArray[i][0].getCheckMouse() || !btnArray[i][1].getCheckMouse()) //neu xuat r thi khoi xuat
				{
					btnArray[i][0].Selected(1);
					btnArray[i][1].Selected(1);
				}
				indexRow = i; //hang duoc chon
			}
			else
			{
				btnArray[i][0].CheckMouseMove(1);
				btnArray[i][1].CheckMouseMove(1);
			}
		}

		if (indexRow >= indexCurrent) //kich ngoai danh sach thi gan index = -1
		{
			btnArray[indexRow][0].UnSelected(1);
			btnArray[indexRow][1].UnSelected(1);
			indexRow  =  -1;
		}
	}

	closegraph(-1);
	return checkScreen;
}
