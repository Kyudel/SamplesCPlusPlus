/////////////////////////////////////////////////////////////////////
//Copyright © 2013-2015 Ivan Perez
//Author: Ivan Perez
//Linkedin: http://es.linkedin.com/in/ivanperezduran
//Portfolio: http://ivanportfolio.tk/
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "String.h"

using namespace std;

int main () 
{
	String sTest01 = String("TestTest01");

	cout << "Test 01:";
	sTest01.Print();

	String sTest02 = String("Test02");
	sTest01 += sTest02;
	cout << endl << "Test 02:";
	sTest01.Print();

	sTest01.Replace('t', 'd');
	sTest01.Replace('T', 'D');

	cout << endl << "Test 03:" ;
	sTest01.Print();


	String sTest03 = sTest01.Substring(2, 6);

	cout << endl << "Test 04:";
	sTest03.Print();
	String sTest04 = sTest01.Substring(4);

	cout << endl << "Test 05:";
	sTest04.Print();

	String sTest05 = "A";

	if (sTest05 == "A")
	{
		cout << endl << "Test 06:" << endl;
		cout << sTest05.GetString() << " and A are equal." << endl;
	}

	if (sTest05 != "B")
	{
		cout << endl << "Test 07:" << endl;
		cout << sTest05.GetString() << " and B are different." << endl;
	}

	String sTest06 = "abcde";

	cout << endl << "Test 08:" << endl;
	cout << "Index of tTest: " << sTest06.IndexOf("cd") << endl;

	cout << endl;

	system("pause");

  return 0;
}