/////////////////////////////////////////////////////////////////////
//Copyright © 2013-2015 Ivan Perez
//Author: Ivan Perez
//Linkedin: http://es.linkedin.com/in/ivanperezduran
//Portfolio: http://ivanportfolio.tk/
/////////////////////////////////////////////////////////////////////

#ifndef STRING
#define STRING

/** The String class represents character strings. The class String includes methods to give functionality.*/
class String
{
private:
	/** Array of chars of the string. */
	char * pString;

	/** The count number of chars*/
	size_t length;

private:

	/**
	* Return the count number of chars in a string.
	* @param pOtherString - string
	* @return the count number of chars
	*/
	size_t GetLengthString(const char *  pOtherString) const;

public:

	/** Constructor by default. */
	String();

	/**
	* Constructor.
	* @param pOtherString - string
	*/
	String(const char * pOtherString);

	/** Copy constructor. */
	String(const String& otherString);

	/** Destructor. */
	~String();

	/** Gets the array of chars of the string. */
	char * GetString();

	/** Gets the number of characters in the current string. */
	inline const unsigned int Length() const
	{
		return length;
	}

	/**
	* Retrieves a substring from this instance. The substring starts at a specified position.
	* @param startIndex - specified position where the sbustring starts
	* @return the count number of chars
	*/
	char * Substring(size_t startIndex) const;

	/**
	* Retrieves a substring from this instance. The substring starts at a specified position and has a specified length.
	* @param startIndex - specified position where the sbustring starts
	* @param length - specified length of the string
	* @return the count number of chars
	*/
	char * Substring(size_t startIndex, size_t substringLength) const;

	/**
	* Reports the index of the first occurrence of the specified string in this instance.
	* @param otherString - specified string
	* @return the index of the first character of the specufied string
	*/
	size_t IndexOf(const char *  otherString) const;

	/**
	* Returns a new string in which all ocurrences of a specified character in this instance are replaced with another specified character.
	* @param oldChar - old character
	* @param newChar - new character
	* @return a string with the new character replaced with the other character
	*/
	void Replace(const char &  oldChar, const char &  newChar);

public:
	/**
	* Gets the character at a specified character position in the current string and is assigned another value.
	* @param index - a character position in the current string
	* @return a character in the specified position
	*/
	char& operator [](size_t index);

	/**
	* Gets the character at a specified character position in the current string.
	* @param index - a character position in the current string
	* @return a character in the specified position
	*/
	const char & operator [] (size_t index) const;

	/**
	* Assigns a new value to the string, replacing its current contents.
	* @param otherString - the new string
	* @return the string assigned
	*/
	String& operator =(const String &otherString);

	/**
	* Returns a new string concatenated with the current string and the specified string.
	* @param otherString - specified string
	* @return a concatenated string
	*/
	String& operator +(const String & otherString);

	/**
	* Returns a new string concatenated with the current string and the specified string.
	* @param otherString - specified string
	* @return a concatenated string
	*/
	String& operator +=(const String & otherString);

	/**
	* Determines whether this instance of string and a specified string have the same value.
	* @param otherString - specified string
	* @return true if both strings have the same value
	*/
	bool operator == (const char *  otherString) const;

	/**
	* Determines whether this instance of string and a specified string have a different value.
	* @param otherString - specified string
	* @return true if both strings have a different value
	*/
	bool operator != (const char *  other) const;

public:

	/** Prints the string. */
	void Print();
};


#endif