/////////////////////////////////////////////////////////////////////
//Copyright © 2013-2015 Ivan Perez
//Author: Ivan Perez
//Linkedin: http://es.linkedin.com/in/ivanperezduran
//Portfolio: http://ivanportfolio.tk/
/////////////////////////////////////////////////////////////////////

#include "String.h"
#include <iostream>

String::String()
{
	length = 0;
	pString = new char[1];
	pString[0] = L'\0';
}




String::String(const char * pOtherString)
{
	size_t auxL = GetLengthString(pOtherString);
	length = auxL;

	pString = new char[length + 1];

	for (size_t i = 0; i<auxL; i++)
	{
		pString[i] = pOtherString[i];
	}

	pString[length] = L'\0';
}

String::String(const String& pOtherString)
{
	length = pOtherString.length;
	if (length == 0)
	{
		pString = new char[1];
		pString[0] = L'\0';
	}
	else
	{
		pString = new char[length + 1];
		for (size_t i = 0; i<length; i++)
		{
			pString[i] = pOtherString.pString[i];
		}
		pString[length] = L'\0';
	}
}

String::~String()
{
	delete[] pString;
	pString = 0;
}


size_t  String::GetLengthString(const char *  pOtherString) const
{
	size_t otherLength = 0;

	while (pOtherString[otherLength] != L'\0')
	{
		otherLength++;
	}

	return otherLength;
}


char * String::GetString()
{
	char * newString = new char[length + 1];

	for (int i = 0; i< length; i++)
	{
		newString[i] = pString[i];
	}
	newString[length] = L'\0';

	return newString;

}

char * String::Substring(size_t startIndex) const
{
	if (length <= startIndex)
	{
		return 0;
	}
	else
	{
		size_t fixedSubstringLenght = length - startIndex;
		char * substring = new char[fixedSubstringLenght + 1];

		for (size_t index = startIndex; index < length; index++)
		{
			substring[index - startIndex] = pString[index];
		}
		substring[fixedSubstringLenght] = L'\0';
		return substring;
	}
}

char * String::Substring(size_t startIndex, size_t substringLength) const
{
	if (length <= startIndex )
	{
		return 0;
	}
	else
	{
		if (startIndex + substringLength < length)
		{
			char * substring = new char[substringLength + 1];

			for (size_t index = startIndex; index < startIndex + substringLength; index++)
			{
				substring[index - startIndex] = pString[index];
			}
			substring[substringLength] = L'\0';

			return substring;
		}
		else
		{
			return Substring(startIndex);
		}
	}
}


size_t String::IndexOf(const char *  otherString) const
{
	size_t otherLength = GetLengthString(otherString);

	if (otherLength == 0 || length < otherLength)
	{
		return -1;
	}
	else
	{
		bool stringFounded = false;

		size_t startIndexString = 0;

		for (startIndexString = 0; startIndexString < length; startIndexString++)
		{
			if (length - startIndexString < otherLength)
			{
				return -1;
			}
			else if (otherString[0] == pString[startIndexString])
			{
				for (size_t indexOther = startIndexString; indexOther <= otherLength; indexOther++)
				{
					if (otherString[indexOther - startIndexString] == pString[indexOther])
					{
						if (indexOther == otherLength)
						{
							stringFounded = true;
							break;
						}
					}
					else
					{
						break;
					}
				}
				if (stringFounded)
				{
					break;
				}
			}
		}
		
		return startIndexString;
	}
}

void String::Replace(const char &  oldChar, const char &  newChar)
{
	for (size_t index = 0; index<length; index++)
	{
		if (pString[index] == oldChar)
		{

			pString[index] = newChar;
		}
	}
}

char& String::operator [](size_t index)
{
	if (length == 0)
	{
		char character = L'';
		return character;
	}

	if (index < length)
	{
		return pString[index];
	}
	else
	{
		char character = L'';
		return character;
	}
}

const char & String::operator [] (size_t index) const
{
	return pString[index];
}


String& String::operator =(const String &otherString)
{
	length = otherString.length;

	if (length == 0)
	{
		delete[] pString;

		pString = new char[1];
		pString[0] = L'\0';
	}
	else if (*pString != *otherString.pString)
	{
		delete[] pString;
		pString = new char[length];
		for (size_t i = 0; i<length; i++)
		{
			pString[i] = otherString.pString[i];
		}
		pString[length] = L'\0';
	}

	return (*this);
}

String& String::operator +(const String & otherString)
{
	return String(*this) += otherString;
}

String& String::operator +=(const String & otherString)
{
	char * oldString = new char[length];
	for (int i = 0; i < length; i++)
	{
		oldString[i] = pString[i];
	}

	size_t oldLength = length;
	length = otherString.length + length;

	delete[] pString;

	pString = new char[length + 1];


	for (int i = 0; i < length; i++)
	{
		pString[i] = oldString[i];
	}
	delete[] oldString;

	for (int i = 0; i<otherString.length; i++)
	{
		pString[i + oldLength] = otherString.pString[i];
	}

	pString[length] = L'\0';
	return *this;
}

bool String::operator == (const char * otherString) const
{
	size_t newLength = GetLengthString(otherString);
	
	bool isEqual = true;

	if (newLength == length)
	{
		for (size_t i = 0; i < newLength; i++)
		{
			if (otherString[i] != pString[i])
			{
				isEqual = false;
				break;
			}
		}
	}
	else
	{
		isEqual = false;
	}

	return isEqual;
}

bool String::operator != (const char * otherString) const
{

	if (pString == otherString)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void String::Print()
{
	std::cout << std::endl;
	for (int i = 0; i< length; i++)
	{
		std::wcout << pString[i];
	}
	std::cout << std::endl;
}
