#pragma once
#include "Scanner.h"

class DiemThi
{
private:
	string maMonHoc;
	char diem[6]; //toi da la  10.00

public:

	DiemThi *pLeft;
	DiemThi *pRight;

	void OutputFStream(ofstream &f);


	void InputFStream(ifstream &f);

	DiemThi()
	{
		pLeft = pRight = NULL;
		diem[0] = '-1';
	}

	DiemThi(string MaMon, char *Diem)
	{
		maMonHoc = MaMon;
		if (strlen(Diem) <= 5) //kiem tra co set duoc hay khong
			strcpy_s(diem, Diem);
		else
			diem[0] = '-1';
		pLeft = pRight = NULL;
	}

	

	char *getDiem() //theo kieu so thuc
	{
		return diem;
	}

	int setDiem(char *Diem)
	{
		if (strlen(Diem) <= 5) //kiem tra co set duoc hay khong
		{
			strcpy_s(diem, Diem);
			return 1;
		}
		else
			return 0;
	}

	string getMaMonHoc()
	{
		return maMonHoc;
	}

	void setMaMonHoc(string MaMonHoc)
	{
		MaMonHoc = MaMonHoc;
	}

};
