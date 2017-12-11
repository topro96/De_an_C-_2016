#include "Lop.h"

bool Lop::CheckIDSV(string x)
{
	for (SinhVien *i = firstSV; i != NULL; i = i->pRight)
	{
		if (i->getMaSV() == x)
			return false;
	}
	return true;
}

void Lop::InsertFirstSV(SinhVien *newSinhVien)
{
	if (firstSV == NULL)
	{
		firstSV = lastSV = newSinhVien;
	}
	else
	{
		newSinhVien->pRight = firstSV;
		firstSV->pLeft = newSinhVien;
		firstSV = newSinhVien;
	}
	soSV++;
}

//them vao sau
void Lop::InsertRightSinhVien(SinhVien *p, SinhVien *newSinhVien)
{
	if (p != NULL)
	{
		newSinhVien->pRight = p->pRight;
		p->pRight->pLeft = newSinhVien;
		p->pRight = newSinhVien;
		newSinhVien->pLeft = p;
	}
	soSV++;
}

void Lop::InsertLeftSinhVien(SinhVien *p, SinhVien *newSinhVien)
{
	if (p == firstSV)
		InsertFirstSV(newSinhVien);
	else
	{
		p->pLeft->pRight = newSinhVien;
		newSinhVien->pLeft = p->pLeft;
		newSinhVien->pRight = p;
		p->pLeft = newSinhVien;
	}
	soSV++;
}

void Lop::InsertLastSinhVien(SinhVien *newSinhVien)
{
	if (lastSV == NULL)
		firstSV = lastSV = newSinhVien;
	else
	{
		lastSV->pRight = newSinhVien;
		newSinhVien->pLeft = lastSV;
		lastSV = newSinhVien;
	}
	soSV++;
}

void Lop::DeleteFirst()
{
	if (firstSV != NULL)
	{
		SinhVien *p = firstSV;
		if (firstSV->pRight != NULL)
		{
			firstSV = firstSV->pRight;
			firstSV->pLeft = NULL;
		}
		else
			firstSV = lastSV = NULL;
		delete p;
	}
}

void Lop::DeleteSinhVien(SinhVien *pSV)
{
	if (pSV != NULL)
	{
		if (pSV == firstSV) //xoa dau hoac co duy nhat 1 Node
			DeleteFirst();
		else
		if (pSV == lastSV)  //xoa cuoi
			DeleteLast(); 
		else                //xoa giua
		{
			pSV->pLeft->pRight = pSV->pRight;
			pSV->pRight->pLeft = pSV->pLeft;
			delete pSV;
		}
		soSV--;
	}
}

void Lop::DeleteLast()
{
	if (lastSV != NULL)
	{
		SinhVien *p = lastSV;
		if (lastSV->pLeft !=NULL)
		{
			lastSV = lastSV->pLeft;
			lastSV->pRight = NULL;
		}
		else
			lastSV = NULL;
		delete p;
	}
}



void Lop::OutputFStream(ofstream & f)
{
	f << maLop << endl;
	f << tenLop << endl;
}

int Lop::InputFStream(ifstream & f)
{
	if (!getline(f, maLop))
	return 0;
	getline(f, tenLop);
	return 1;
}

void Lop::Clear()
{
	SinhVien *p;
	while (firstSV != NULL)
	{
		p = firstSV;
		firstSV = firstSV->pRight;
		p->Clear();
		delete p;
	}
	lastSV = NULL;
}

