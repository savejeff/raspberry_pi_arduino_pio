#pragma once

#include <string>

#define _STRING_VARIANTE 1


#if _STRING_VARIANTE == 0

typedef std::string String;

#elif _STRING_VARIANTE == 1




typedef std::string __FlashStringHelper;
//typedef String __FlashStringHelper;
#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
//#define F(string_literal) (FPSTR(PSTR(string_literal)))

/*
#ifndef F
//Define macro for strings stored in flash.
#define F(str) (str)
#endif  // F
*/






class String : public std::string 
{
protected:

	inline const char *buffer() const { return c_str(); }

	inline const size_t len() const { return length(); }

public:

	/****************************** Constructors *************************************/
	
	using std::string::string;

	String()
	: std::string()
	{
		
	}
	
	String(std::string s)
	: std::string(s)
	{
		
	}

	/*
	String(char c)
	: std::string("" + c)
	{

	}
	*/

	/*
	String(const char* data, int _len)
	: std::string("")
	{
		for(int i = 0; i < _len; i++)
			*this += data[i];
	}
	*/

	String(const uint8_t* data, int _len)
	: std::string("")
	{
		for(int i = 0; i < _len; i++)
			*this += (char) data[i];
	}

	explicit String(char c);
	explicit String(unsigned char, unsigned char base = 10);
	explicit String(int, unsigned char base = 10);
	explicit String(unsigned int, unsigned char base = 10);
	explicit String(long, unsigned char base = 10);
	explicit String(unsigned long, unsigned char base = 10);
	explicit String(float, unsigned int decimalPlaces = 2);
	explicit String(double, unsigned int decimalPlaces = 2);
	explicit String(long long, unsigned char base = 10);
	explicit String(unsigned long long, unsigned char base = 10);


	/***************************** Operator **************************************/

	using std::string::operator=;

	String operator+(const int v);
	String operator+(const uint16_t v);
	


	/****************************** equals *************************************/

	bool equals(const String& s)
	{
		return *this == s;
	}
	unsigned char equalsIgnoreCase(const String &s) const;



	/****************************** substring *************************************/

	//operator std::string() { return std::string(this->c_str(), this->length()); }

	String substring(unsigned int beginIndex) const {
		return substr(beginIndex);
	};
	
	// endIndex is exklusiv 
	String substring(unsigned int beginIndex, unsigned int endIndex) const {
		return substr(beginIndex, endIndex - beginIndex);
	};


	/****************************** starts/ends with *************************************/

	unsigned char startsWith(const String &prefix) const;
	unsigned char startsWith(const char *prefix) const {
		return this->startsWith(String(prefix));
	}
	// unsigned char startsWith(const __FlashStringHelper *prefix) const {
	// 	return this->startsWith(String(prefix));
	// }
	unsigned char startsWith(const String &prefix, unsigned int offset) const;
	unsigned char endsWith(const String &suffix) const;
	unsigned char endsWith(const char *suffix) const {
		return this->endsWith(String(suffix));
	}
	// unsigned char endsWith(const __FlashStringHelper * suffix) const {
	// 	return this->endsWith(String(suffix));
	// }


	/**************** search *************************/

	// Alternative:
	// https://www.cplusplus.com/reference/string/string/find/
	//int index_sep = line.find(SEPERATOR);
	
	int indexOf(char ch) const;
	int indexOf(char ch, unsigned int fromIndex) const;
	int indexOf(const String &str) const;
	int indexOf(const String &str, unsigned int fromIndex) const;

	int lastIndexOf(char ch) const;
	int lastIndexOf(char ch, unsigned int fromIndex) const;
	int lastIndexOf(const String &str) const;
	int lastIndexOf(const String &str, unsigned int fromIndex) const;



	void replace(char find, char replace);
	void replace(const String &find, const String &replace);
	void replace(const char *find, const String &replace) {
		this->replace(String(find), replace);
	}
	void replace(const char *find, const char *replace) {
		this->replace(String(find), String(replace));
	}


	/************ concat ********************/

	// returns true on success, false on failure (in which case, the string
	// is left unchanged).  if the argument is null or invalid, the
	// concatenation is considered unsuccessful.
	unsigned char concat(const String &str);
	unsigned char concat(const char *cstr);
	unsigned char concat(const char *cstr, unsigned int length);
	unsigned char concat(const uint8_t *cstr, unsigned int length) {return concat((const char*)cstr, length);}
	unsigned char concat(char c);
	unsigned char concat(unsigned char c);
	unsigned char concat(int num);
	unsigned char concat(unsigned int num);
	unsigned char concat(long num);
	unsigned char concat(unsigned long num);
	unsigned char concat(float num);
	unsigned char concat(double num);
	unsigned char concat(long long num);
	unsigned char concat(unsigned long long num);
	unsigned char concat(const __FlashStringHelper * str);


	
	void remove(unsigned int index); // remove everything from index to end of string
	void remove(unsigned int index, unsigned int count); // remove characters string from index a total of count characters
	
	void trim();

	char charAt(unsigned int index) const {
		return at(index);
	}

	/***************** misc **********************/

	void toLowerCase(void);
	void toUpperCase(void);

	// parsing/conversion
	long toInt(void) const;
};






class StringSumHelper: public String {
	public:
		StringSumHelper(const String &s) :
				String(s) {
		}
		StringSumHelper(const char *p) :
				String(p) {
		}
		StringSumHelper(char c) :
				String(c) {
		}
		StringSumHelper(unsigned char num) :
				String(num) {
		}
		StringSumHelper(int num) :
				String(num) {
		}
		StringSumHelper(unsigned int num) :
				String(num) {
		}
		StringSumHelper(long num) :
				String(num) {
		}
		StringSumHelper(unsigned long num) :
				String(num) {
		}
		StringSumHelper(float num) :
				String(num) {
		}
		StringSumHelper(double num) :
				String(num) {
		}
		/*
		StringSumHelper(long long num) :
				String(num) {
		}
		StringSumHelper(unsigned long long num) :
				String(num) {
		}
		*/
};





#else 


#endif 