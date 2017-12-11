#pragma once
#include "Lop.h"
#include "MonHoc.h"

#define MaxLopHoc  100
#define MaxMonHoc  50

class Data {
private:
	Lop *danhSachLopHoc;
	int nLopHoc; //số lớp hiện tại

	MonHoc *danhSachMonHoc;
	int nMonHoc; //số môn học hiện tại

	string arrayClassOld[100]; //chứa mã lớp để đối chiếu với Dât củ mà xóa File
	int nClassOld; //chua so lop luc load

	string arraySubjectOld[100]; //chứa mã mon để đối chiếu với Dât củ mà xóa File
	int nSubjectsOld; //chua so mon luc load

public:
	//load tất cả dữ liệu từ file
	void LoadData()
	{
		Scanner scan;
		//load lop hoc
		ifstream fLopHoc;
		fLopHoc.open("DanhSachLop.txt", ios::in);
		if (fLopHoc.is_open())
		{
			if (!scan.FileIsEmpty(fLopHoc))
				while (!fLopHoc.eof())
					if (danhSachLopHoc[nLopHoc].InputFStream(fLopHoc))
						nLopHoc++;
		}
		fLopHoc.close();

		//load sinh vien
		for (int i = 0; i < nLopHoc; i++)
		{
			ifstream fSinhVien;
			string x = danhSachLopHoc[i].getMaLop();
			x += ".txt"; //noi them vao x
			fSinhVien.open(x, ios::in);
			if (fSinhVien.is_open())
			{
				if (scan.FileIsEmpty(fSinhVien) == false)
					while (!fSinhVien.eof())
					{
						SinhVien *p = new SinhVien;
						p->InputFStream(fSinhVien);
						danhSachLopHoc[i].InsertLastSinhVien(p);
					}
			}
			fSinhVien.close();
		}

		//load mon hoc
		ifstream fMonHoc;
		fMonHoc.open("DanhSachMon.txt", ios::in);
		if (fMonHoc.is_open())
		{
			if (!scan.FileIsEmpty(fMonHoc))
				while (!fMonHoc.eof())
					if (danhSachMonHoc[nMonHoc].InputFStream(fMonHoc))
						nMonHoc++;
		}
		fMonHoc.close();

		//load cau hoi
		for (int i = 0; i < nMonHoc; i++)
		{
			ifstream fCauHoi;
			string x = danhSachMonHoc[i].getMaMonHoc();
			x += ".txt";
			fCauHoi.open(x, ios::in);
			if (fCauHoi.is_open())
			{
				if (scan.FileIsEmpty(fCauHoi) == false)
					while (!fCauHoi.eof())
					{
						CauHoi *p = new CauHoi;
						if (p->InputFStream(fCauHoi))
						{
							danhSachMonHoc[i].InsertQuestion(p);
						}
						else
							delete p;
					}
			}
			fCauHoi.close();
		}


	}

	void SaveDataClass()
	{
		ofstream fLopHoc;
		fLopHoc.open("DanhSachLop.txt", ios::out);

		//luu danh sach lop
		if (!fLopHoc.is_open())
		{
			fLopHoc.open("DanhSachLop.txt", ios::app);
		}
		for (int i = 0; i < nLopHoc; i++)
		{
			danhSachLopHoc[i].OutputFStream(fLopHoc);
		}
		fLopHoc.close();

	}

	void SaveDataMonHoc()
	{
		//lưu danh sách môn học
		ofstream fMonHoc;
		fMonHoc.open("DanhSachMon.txt", ios::out);

		if (!fMonHoc.is_open())
		{
			fMonHoc.open("DanhSachMon.txt", ios::app);
		}

		for (int i = 0; i < nMonHoc; i++)
		{
			danhSachMonHoc[i].OutputFStream(fMonHoc);
		}
		fMonHoc.close();
	}


	void SavaDataStudent(Lop *lop)
	{
		//luu danh sach sinh vien cua lop
		SinhVien *p = lop->firstSV;
		if (p != NULL)
		{
			ofstream fSinhVien;
			string x = lop->getMaLop(); //sao chep ma lop sang x
			x += ".txt"; //noi them vao x
			fSinhVien.open(x, ios::out);
			if (!fSinhVien.is_open()) //neu tap tin ko mo duoc thi tao moi
				fSinhVien.open(x, ios::app);
			//ghi sv p vao file nhung chua lai phan tu cuoi
			while (p->pRight != NULL)
			{
				p->OutputFStream(fSinhVien);
				fSinhVien << " #" << endl;
				p = p->pRight;
			}
			p->OutputFStream(fSinhVien);
			fSinhVien << " #";
			fSinhVien.close();
		}
	}

	void SaveDeQui(note<CauHoi> *root, ofstream &f)
	{
		if (root != NULL)
		{
			root->_data->OutputFStream(f);
			SaveDeQui(root->_left, f);
			SaveDeQui(root->_right, f);
		}
	}

	void SaveDataCauHoi(MonHoc *monHoc)
	{
		if (monHoc->treeCauHoi->_root != NULL)
		{
			ofstream f;
			string x = monHoc->getMaMonHoc(); //sao chep ma lop sang x
			x += ".txt"; //noi them vao x
			f.open(x, ios::out);
			if (!f.is_open()) //neu tap tin ko mo duoc thi tao moi
				f.open(x, ios::app);

			SaveDeQui(monHoc->treeCauHoi->_root, f);
			f.close();
		}
	}

	//them 1 class
	int AddClass(string maLop, string tenLop)
	{
		if (nLopHoc < MaxLopHoc)
		{
			danhSachLopHoc[nLopHoc].setMaLop(maLop);
			danhSachLopHoc[nLopHoc].setTenLop(tenLop);
			nLopHoc++;
			return 1; //them thanh cong
		}
		return 0;
	}

	int AddSubject(string maMon, string tenMon)
	{
		if (nMonHoc < MaxMonHoc)
		{
			danhSachMonHoc[nMonHoc].setMaMonHoc(maMon);
			danhSachMonHoc[nMonHoc].setTenMonHoc(tenMon);
			nMonHoc++;
			return 1;
		}
		return 0;
	}

	int CheckNewClass(string id)
	{
		for (int i = 0; i < nLopHoc; i++)
		{
			if (danhSachLopHoc[i].getMaLop() == id) //kiểm tra từng lớp
				return 0;
		}
		return 1;
	}

	int CheckNewSubject(string id)
	{
		for (int i = 0; i < nMonHoc; i++)
		{
			if (danhSachMonHoc[i].getMaMonHoc() == id) //kiểm tra từng lớp
				return 0;
		}
		return 1;
	}

	MonHoc *SearchMon(string id)
	{
		for (int i = 0; i < nMonHoc; i++)
		{
			if (danhSachMonHoc[i].getMaMonHoc() == id) //kiểm tra từng lớp
				return &danhSachMonHoc[i];
		}
		return NULL;
	}

	//kiem tra xem id sinh vien vua them co trung voi toan truogn hay khong
	int CheckNewStudent(string id)
	{
		for (int i = 0; i < nLopHoc; i++)
		{
			if (danhSachLopHoc[i].CheckIDSV(id) == false) //kiểm tra từng lớp
				return 0;
		}
		return 1;
	}

	int DeleteClass(int index)
	{
		if (index >= nLopHoc)
			return 0;

		for (int i = index; i < nLopHoc - 1; i++)
		{
			swap(danhSachLopHoc[i], danhSachLopHoc[i + 1]);
		}
		nLopHoc--;
		danhSachLopHoc[nLopHoc].Clear(); //giải phóng toàn bộ con trỏ sinh viên và điểm thi
		return 1; //xoa thanh cong
	}

	int DeleteSubject(int index)
	{
		if (index >= nMonHoc)
			return 0;

		for (int i = index; i < nMonHoc - 1; i++)
		{
			swap(danhSachMonHoc[i], danhSachMonHoc[i + 1]);
		}
		nMonHoc--;
		danhSachMonHoc[nMonHoc].treeCauHoi->DeleteTree(danhSachMonHoc[nMonHoc].treeCauHoi->_root); //giải phóng toàn bộ câu hỏi
		return 1; //xoa thanh cong
	}

	 ////lay mã lớp để đối chiếu với Dât củ mà xóa File
	void LayMaCacLop()
	{
		nClassOld = nLopHoc;
		for (int i = 0; i < nClassOld; i++)
		{
			arrayClassOld[i] = danhSachLopHoc[i].getMaLop();
		}
	}

	void LayMaCacMon()
	{
		nSubjectsOld = nMonHoc;
		for (int i = 0; i < nSubjectsOld; i++)
		{
			arraySubjectOld[i] = danhSachMonHoc[i].getMaMonHoc();
		}
	}

	//xoa cac lop rac
	void XoaCacLopRac()
	{
		string x;
		bool check; //dat co hieu
		for (int i = 0; i < nClassOld; i++)
		{
			check = false;
			for (int j = 0; j < nLopHoc; j++)
			{
				if (arrayClassOld[i] == danhSachLopHoc[j].getMaLop())
				{
					check = true;
					break;
				}
			}
			if (check == false)
			{
				x = arrayClassOld[i] + ".txt";
				DeleteFile(_strdup(x.c_str()));
			}
		}

	}

	void XoaCacMonRac()
	{
		bool check; //dat co hieu
		string x;
		for (int i = 0; i < nSubjectsOld; i++)
		{
			check = false;
			for (int j = 0; j < nMonHoc; j++)
			{
				if (arraySubjectOld[i] == danhSachMonHoc[j].getMaMonHoc())
				{
					check = true;
					break;
				}
			}
			if (check == false)
			{
				x = arraySubjectOld[i] + ".txt";
				DeleteFile(_strdup(x.c_str()));
			}
		}

	}

	void FreeAllPointer()
	{
		for (int i = 0; i < nLopHoc; i++)
			danhSachLopHoc[i].Clear();

		for (int i = 0; i < nMonHoc; i++)
			danhSachMonHoc[i].Clear();

		delete [] danhSachLopHoc;
		delete[] danhSachMonHoc;
	}
	
	//void CleanClear(string maMon) //Xóa các con trỏ chứa điểm 1 môn khi xóa môn học đó
	//{
	//	SinhVien *pSinhVien;
	//	for (int i = 0; i < nLopHoc; i++)
	//	{
	//		 pSinhVien = danhSachLopHoc[i].firstSV;
	//		while (pSinhVien!=NULL)
	//		{
	//			DiemThi *pDiemThi = pSinhVien->firstDiemThi;
	//			while (pDiemThi!=NULL)
	//			{
	//				if (pDiemThi->getMaMonHoc() == maMon)
	//				{
	//					pSinhVien->DeleteDiem(pDiemThi);
	//					break;
	//				}
	//				pDiemThi = pDiemThi->pRight;
	//			}
	//			pSinhVien = pSinhVien->pRight;
	//		}
	//	}
	//}

	Lop *getDanhSachLop()
	{
		return danhSachLopHoc;
	}

	int getSoLop()
	{
		return nLopHoc;
	}

	MonHoc *getDanhSachMon()
	{
		return danhSachMonHoc;
	}

	int getSoMon()
	{
		return nMonHoc;
	}

	Data()
	{
		nLopHoc = 0;
		nMonHoc = 0;
		danhSachLopHoc = new Lop[MaxLopHoc];
		danhSachMonHoc = new MonHoc[MaxMonHoc];
	}

};
