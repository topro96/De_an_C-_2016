#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include "graphics.h"

using namespace std;


class Scanner
{

public:

	bool FileIsEmpty(ifstream &f)
	{
		return f.peek() == std::ifstream::traits_type::eof();
	}

	int LayDuLieu(string &a, ifstream &f); //return 1 khi dòng đó vẫn còn, 0 khi hết

};

