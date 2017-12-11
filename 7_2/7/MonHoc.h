#pragma once
#include "Scanner.h"
#include "CauHoi.h"
#include "DataStructure.h"

class MonHoc
{
	string maMonHoc;
	string tenMonHoc;
	int soCauHoi; //so cau hoi hien co
public:

	AVL <CauHoi> *treeCauHoi;

	int InsertQuestion(CauHoi *p); //insert cau hoi cua mon nay

	void DeleteQuestion(int key);

	CauHoi *Search(int key);

	void OutputFStream(ofstream &f);

	int InputFStream(ifstream &f);

	int getSoCauHoi() { return soCauHoi; }

	//soCauHoi++;
	void setSoCauHoi()
	{
		soCauHoi++;
	}

	void Clear()
	{
		treeCauHoi->DeleteTree(treeCauHoi->_root);
		delete treeCauHoi;
	}

	string getMaMonHoc()
	{
		return maMonHoc;
	}

	void setMaMonHoc(string x)
	{
		maMonHoc = x;
	}

	string getTenMonHoc()
	{
		return tenMonHoc;
	}

	void setTenMonHoc(string x)
	{
		tenMonHoc = x;
	}

	MonHoc()
	{
		soCauHoi = 0;
		treeCauHoi = new AVL <CauHoi>;
		
	}

	MonHoc(MonHoc *x)
	{
		maMonHoc = x->getMaMonHoc();
		tenMonHoc = x->getTenMonHoc();
	}
};

