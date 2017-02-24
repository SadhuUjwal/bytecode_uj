#include "stdafx.h"
#include "Byte.h"
#include <tchar.h>

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#define to2complement

using namespace std;

int Byte::read(istream & In){// read from input file //

	char Inp;

	In.get(Inp);
	

	for (int i = 0; i < BYTESIZE; ++i)
	{
		if (Inp == '0' || Inp == '1')

			byte[i] = Inp;

		else
		{
			error = true;

			break;
		}

		In.get(Inp);
		
	}


	return !In.eof() || !In.fail();
}
Byte Byte::to2sComplement()

{
	Byte ADD;
	int cary = 1;

	for (int i = BYTESIZE - 1; i >= 0; i--)
	{
		ADD.byte[i] = (byte[i] - '0') ? '0' : '1';
		int v = (ADD.byte[i] - '0') + cary;
		ADD.byte[i] = (v % 2) + '0';
		cary = v / 2;

	}
	return ADD;

}




ostream& operator << (ostream & O, const Byte& b)// to write in file

{
	

	for (int i = 0; i < Byte::BYTESIZE; ++i)
	{
		O << b.byte[i];
		
	}

	return O;
}

Byte  operator + (const Byte& b1, const Byte& b2)// for sum( b1+b2)
{
	Byte ADD = b1;
	return ADD = ADD + b2;
}

int Byte::toInteger(){// binary to integer

#ifndef to2complement

	int uj = byte[0] - '0';
	

	for (int i = 2; i < BYTESIZE; ++i)
	{
		uj = uj * 2 + (byte[i] - '0');
		
	}
#else

	int uj = byte[1] - '0';
	

	for (int i = 2; i < BYTESIZE; ++i)
	{
		uj = uj * 2 + (byte[i] - '0');
		
	}

	return -((byte[0] - '0') * 128) + uj;
#endif
}
const char * Byte::getErrorMessage() const
{
	return errorMessage;
}

bool Byte::hasError() const
{

	return error;
}
Byte Byte::add(Byte NX)// for adding 

{
	int x[BYTESIZE + 1];
	memset(x, 0, sizeof(int)*(BYTESIZE + 1));
	x[BYTESIZE] = 0;
	Byte addn;


	for (int i = BYTESIZE - 1; i >= 0; i--)
	{
		int Vnumber = ((byte[i] - '0') + (NX.byte[i] - '0') + x[i + 1]);
		addn.byte[i] = Vnumber % 2 + '0';
		x[i] = Vnumber / 2;

	}
	return addn;

}

Byte::Byte(char *R)
{
	int String_L = strlen(R);

	memset(byte, '0', sizeof(char)*BYTESIZE);
	int Count1 = 0;
	if (String_L > BYTESIZE)
	{
		error = true;

	}

	else if (String_L  < BYTESIZE)
	{
		Count1 = BYTESIZE - String_L;

	}

	

	for (int i = 0; i < BYTESIZE; ++i)
	{
		if (R[i] == '0' || R[i] == '1')
			byte[i + Count1] = R[i];
		else
		{
			error = true;

		}
		
	}


}

Byte Byte::biasTo2sComplement()

{
	Byte ADD = *this;
	ADD.byte[0] = (byte[0] - '0') ? '0' : '1';
	return ADD;
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Program Starting ...\n";

	Byte b1, b2, b3;
	char * comp = "2\'s complement ";
	char * bias = "biased notation";

	cout << "Opening Files ...\n";

	ifstream in("byte.in", ios::in);
	ofstream out("summ.out", ios::out);

	cout << "Files Opened Successfully ...\n";


	while (b1.read(in) && b2.read(in))
	{
		b3 = b1.add(b2.biasTo2sComplement());
		cout << "   " << b1 << "\t" << comp << "\t" << std::right << std::setw(8) << b1.toInteger() << endl;
		cout << "+  " << b3 << "\t" << bias << "\t" << std::right << std::setw(8) << b2.biasTo2sComplement().toInteger() << endl;
		cout << "-----------\t\t\t" << std::right << std::setw(8) << "----" << endl;
		cout << "   " << b3 << "\t" << comp << "\t" << std::right << std::setw(8) << b3.toInteger() << endl << endl;
	}

}