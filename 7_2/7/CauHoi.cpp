#include "CauHoi.h"



void CauHoi::OutputFStream(ofstream & f)
{
	f << ID << endl;
	f << noiDung << endl;
	for (int i = 0; i < 4; i++)
		f << answer[i] << endl;
	f << dapAn << endl;
}

int CauHoi::InputFStream(ifstream & f)
{
		if (!(f >> ID))
		return 0;
		f.ignore();
		getline(f, noiDung);
		for (int i = 0; i < 4; i++)
			getline(f, answer[i]);
		f >> dapAn;
		return 1;
}

CauHoi::CauHoi()
{
}


CauHoi::~CauHoi()
{
}
