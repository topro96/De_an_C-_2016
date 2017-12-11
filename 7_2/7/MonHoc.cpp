#include "MonHoc.h"

int MonHoc::InsertQuestion(CauHoi * p)
{
	int x = 0;
	if (p != NULL)
	{
		x = treeCauHoi->Insert(treeCauHoi->_root, p, p->getID());
		if (x == 1)
			soCauHoi++;
	}
	return x;
}

void MonHoc::DeleteQuestion(int key)
{	
	treeCauHoi->DeleteNode(treeCauHoi->_root, key);
	soCauHoi--;
}

CauHoi *MonHoc::Search(int key)
{
	note <CauHoi> *p = treeCauHoi->Search(key, treeCauHoi->_root);
	if (p != NULL)
	{
		return p->_data;
	}
	return NULL;
}

void MonHoc::OutputFStream(ofstream & f)
{
	f << maMonHoc << endl;
	f << tenMonHoc << endl;
}

int MonHoc::InputFStream(ifstream & f)
{
	if (!getline(f, maMonHoc))
	return 0;
	getline(f, tenMonHoc);
	return 1;
}
