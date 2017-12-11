#include "SinhVien.h"



void SinhVien::InputFStream(ifstream &f)
{
	Scanner scan;
	string value;
	scan.LayDuLieu(maSV, f);

	scan.LayDuLieu(ten, f);

	scan.LayDuLieu(ho, f);

	string Phai;
	scan.LayDuLieu(Phai, f);

	phai = atoi(Phai.c_str());

	int check = scan.LayDuLieu(passWord, f); //kiem tra xem het dong hay chua
		
	if (check == 1)
	{
		//lay diem thi
		string MaMon;
		string Diem;
		while (check == 1)
		{
			scan.LayDuLieu(MaMon, f);
			check = scan.LayDuLieu(Diem, f);

			DiemThi *diemThi = new DiemThi(MaMon, _strdup(Diem.c_str()));
			InsertFirstDiem(diemThi);
			MaMon = "";
			Diem = "";
		}
	}
}

void SinhVien::InsertFirstDiem(DiemThi * newDiemThi)
{
	if (firstDiemThi == NULL)
	{
		firstDiemThi = lastDiemThi = newDiemThi;
	}
	else
	{
		newDiemThi->pRight = firstDiemThi;
		firstDiemThi->pLeft = newDiemThi;
		firstDiemThi = newDiemThi;
	}
	
}

//them vao sau
void SinhVien::InsertRightDiem(DiemThi * p, DiemThi * newDiemThi)
{
	if (p != NULL)
	{
		newDiemThi->pRight = p->pRight;
		p->pRight->pLeft = newDiemThi;
		p->pRight = newDiemThi;
		newDiemThi->pLeft = p;
	}

}

void SinhVien::InsertLeftDiem(DiemThi * p, DiemThi * newDiemThi)
{
	if (p == firstDiemThi)
		InsertFirstDiem(newDiemThi);
	else
	{
		p->pLeft->pRight = newDiemThi;
		newDiemThi->pLeft = p->pLeft;
		newDiemThi->pRight = p;
		p->pLeft = newDiemThi;
	}
}

void SinhVien::InsertLastDiem(DiemThi * newDiemThi)
{
	if (lastDiemThi == NULL)
		firstDiemThi = lastDiemThi = newDiemThi;
	else
	{
		lastDiemThi->pRight = newDiemThi;
		newDiemThi->pLeft = lastDiemThi;
		lastDiemThi = newDiemThi;
	}
}


void SinhVien::DeleteFirst()
{
	if (firstDiemThi != NULL)
	{
		DiemThi *p = firstDiemThi;
		if (firstDiemThi->pRight != NULL)
		{
			firstDiemThi = firstDiemThi->pRight;
			firstDiemThi->pLeft = NULL;
		}
		else
			firstDiemThi = lastDiemThi = NULL;
		delete p;
	}
}

void SinhVien::DeleteDiem(DiemThi *pDiem)
{
	if (pDiem != NULL)
	{
		if (pDiem == firstDiemThi) //xoa dau hoac co duy nhat 1 Node
			DeleteFirst();
		else
			if (pDiem == lastDiemThi)  //xoa cuoi
				DeleteLast();
			else                //xoa giua
			{

				if (pDiem->pRight != NULL && pDiem->pLeft != NULL)
				{
					pDiem->pLeft->pRight = pDiem->pRight;
					pDiem->pRight->pLeft = pDiem->pLeft;
					delete pDiem;
				}
			}
	}
}

void SinhVien::DeleteLast()
{
	if (lastDiemThi != NULL)
	{
		DiemThi *p = lastDiemThi;
		if (lastDiemThi->pLeft != NULL)
		{
			lastDiemThi = lastDiemThi->pLeft;
			lastDiemThi->pRight = NULL;
		}
		else
			lastDiemThi = NULL;
		delete p;
	}
}

DiemThi * SinhVien::SearchDiem(string MSMH)
{

	for (DiemThi *i = firstDiemThi; i != NULL; i = i->pRight)
	{
		if (i->getMaMonHoc() == MSMH)
			return i;
	}
	return NULL;
}

void SinhVien::Clear()
{
	DiemThi *p;
	while (firstDiemThi!=NULL)
	{
		p = firstDiemThi;
		firstDiemThi = firstDiemThi->pRight;
		delete p;
	}
	lastDiemThi = NULL;
}

void SinhVien::OutputFStream(ofstream &f)
{
	f << maSV << " | ";
	f << ten << " | ";
	f << ho << " | ";

	f << phai << " | ";

	f << passWord;
	//luu diem
	DiemThi *p = firstDiemThi;
	while (p != NULL)
	{
		f << " | ";
		p->OutputFStream(f);
		p = p->pRight;
	}
}

