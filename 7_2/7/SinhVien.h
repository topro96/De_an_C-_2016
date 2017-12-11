#pragma once
#include "DiemThi.h"



class SinhVien
{
private:
	string maSV; //ma so sinh vien
	string ho; //họ
	string ten; //tên
	string passWord;
	int phai; //giới tính 0 nam , 1 nu, khac
			 

public:
	SinhVien *pLeft;
	SinhVien *pRight;

	DiemThi *firstDiemThi;  //con trỏ tới môn học đã thi
	DiemThi *lastDiemThi; //


	//ghi vao file
	void OutputFStream(ofstream &f);

	//doc file
	void InputFStream(ifstream &f);
	
	void InsertFirstDiem(DiemThi *newDiemThi);

	void InsertRightDiem(DiemThi *p, DiemThi *newDiemThi); //them nut newDIem thi vao SAU node p

	void InsertLeftDiem(DiemThi *p, DiemThi *newDiemThi); //them node new vao TRUOC node p

	void InsertLastDiem(DiemThi *newDiemThi); //them vao cuoi danh sach

	void AddDiem(float diem, string maMon)
	{
		DiemThi *p = firstDiemThi;
		char number[6];
		sprintf_s(number, "%.2f", diem);
		while (p!=NULL)
		{
			if (p->getMaMonHoc() == maMon)
			{
				
				p->setDiem(number);
				return;
			}
			p = p->pRight;
		}

		p = new DiemThi(maMon,number);

		InsertLastDiem(p);
	}

	void DeleteFirst(); //xoa dau

	void DeleteDiem(DiemThi *pDiem);

	void DeleteLast(); //xoa cuoi

	DiemThi *SearchDiem(string MSMH); //tim diem bang ma so mon hoc

	void Clear();

	string getMaSV()
	{
		return maSV;
	}

	void setMaSV(string x)
	{
		maSV = x;
	}

	string getHo()
	{
		return ho;
	}

	void setHo(string x)
	{
		ho = x;
	}


	string getTen()
	{
		return ten;
	}

	void setTen(string x)
	{
		ten = x;
	}


	string getPassWord()
	{
		return passWord;
	}

	void setPassWord(string x)
	{
		passWord = x;
	}

	int getPhai()
	{
		return phai;
	}

	void setPhai(int x)
	{
		phai = x;
	}

	SinhVien()
	{
		pLeft = pRight = NULL;
		firstDiemThi = NULL;
		passWord = "123"; //password mac dinh
		phai = 3;
	}

	SinhVien(SinhVien &x)
	{
		pLeft = pRight = NULL;
		firstDiemThi = NULL;
		maSV = x.getMaSV();
		ho = x.getHo();
		ten = x.getTen();
		passWord = x.getPassWord();
	}
};

