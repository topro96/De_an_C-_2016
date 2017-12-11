#pragma once
#include <iostream>
#include "Scanner.h"
#include <string>
using namespace std;



class CauHoi
{
	int ID;
	string noiDung;
	string answer[4]; //4 dap an abcd
	int dapAn;
public:
	
	void OutputFStream(ofstream &f);//ghi vao file

	//doc file
	int InputFStream(ifstream &f);

	int getID() { return ID; }
	void setID(int x) { ID = x; }

	string getNoiDung() { return noiDung; }
	void setNoiDung(string x) { noiDung = x; }

	string *getAnswer() { return answer; }
	void setAnswer(string a, string b, string c, string d)
	{
			answer[0] =a;
			answer[1] = b;
			answer[2] = c;
			answer[3] = d;
	}

	int getDapAn() { return dapAn; }
	
	void setDapAn(int x) 
	{
		dapAn = x;
	}

	CauHoi();
	~CauHoi();
};

