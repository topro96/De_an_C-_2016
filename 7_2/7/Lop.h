#pragma once
#include "Scanner.h"
#include "SinhVien.h"
#include "Console.h"

class Lop
{
	string maLop;
	string tenLop;
	int soSV; //so sv lop do dang co

public:

	SinhVien *firstSV; //danh sách các sinh viên
	SinhVien *lastSV;

	bool CheckIDSV(string x); //kiem tra id sv vua them co trung hay khong

	void InsertFirstSV(SinhVien *newSinhVien);

	void InsertRightSinhVien(SinhVien *p, SinhVien *newSinhVien); //them nut newDIem thi vao SAU node p

	void InsertLeftSinhVien(SinhVien *p, SinhVien *newSinhVien); //them node new vao TRUOC node p

	void InsertLastSinhVien(SinhVien *newSinhVien); //them vao cuoi danh sach

	void DeleteFirst(); //xoa dau

	void DeleteSinhVien(SinhVien *pSV); 

	void DeleteLast(); //xoa cuoi

	void OutputFStream(ofstream &f);

	int InputFStream(ifstream &f);

	void Clear(); //xoa toan bo lop hoc
	
	string getMaLop()
	{
		return maLop;
	}

	void setMaLop(string x)
	{
		maLop = x;
	}

	string getTenLop()
	{
		return tenLop;
	}

	void setTenLop(string x)
	{
		tenLop = x;
	}

	int getSoSV()
	{
		return soSV;
	}

	void setSoSV(int x)
	{
		soSV = x;
	}

	Lop()
	{
		firstSV = lastSV = NULL;
		soSV = 0;
	}

	~Lop()
	{

	}

};

