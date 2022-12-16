#include "WString.h"

#include <cstring>
#include <cstdlib> 
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "lowlevelfuncs.h"


#include <stdarg.h>

// monolit function
static String s_printf(const char* format, ...) //__attribute__((format(printf, 1, 2)))
{
	char loc_buf[64];
	char* temp = loc_buf;
	va_list arg;
	va_list copy;
	va_start(arg, format);
	va_copy(copy, arg);
	int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
	va_end(copy);
	if (len < 0) {
		va_end(arg);
		return "";
	};
	if (len >= sizeof(loc_buf)) {
		temp = (char*)malloc(len + 1);
		if (temp == NULL) {
			va_end(arg);
			return "";
		}
		len = vsnprintf(temp, len + 1, format, arg);
	}
	va_end(arg);
	
	String s = String(temp);
	
	if (temp != loc_buf) {
		free(temp);
	}
	return s;
}



/****************************** Constructors *************************************/


String::String(char c) {
    char buf[] = { c, '\0' };
    *this = String(buf);
}

String::String(unsigned char value, unsigned char base) {
    char buf[1 + 8 * sizeof(unsigned char)];
    utoa(value, buf, base);
    *this = String(buf);
}

String::String(int value, unsigned char base) {
    
    char buf[2 + 8 * sizeof(int)];
    if (base == 10) {
        sprintf(buf, "%d", value);
    } else {
        itoa(value, buf, base);
    }
    *this = String(buf);
}

String::String(unsigned int value, unsigned char base) {
    
    char buf[1 + 8 * sizeof(unsigned int)];
    utoa(value, buf, base);
    *this = String(buf);
}

String::String(long value, unsigned char base) {
    
    char buf[2 + 8 * sizeof(long)];
    if (base==10) {
        sprintf(buf, "%ld", value);
    } else {
        ltoa(value, buf, base);
    }
    *this = String(buf);
}

String::String(unsigned long value, unsigned char base) {
    
    char buf[1 + 8 * sizeof(unsigned long)];
    ultoa(value, buf, base);
    //ltoa(value, buf, base); // dirty fix -> should work for all but the biggest values
    *this = String(buf);
}

String::String(float value, unsigned int decimalPlaces) {
    
    char *buf = (char*)malloc(decimalPlaces + 42);
    if (buf) {
        *this = String(dtostrf(value, (decimalPlaces + 2), decimalPlaces, buf));
        free(buf);
    } else {
        *this = String("nan");
        printf("String::String(float value, unsigned int decimalPlaces): No enought memory for the operation.");
    }
}

String::String(double value, unsigned int decimalPlaces) {
    
    char *buf = (char*)malloc(decimalPlaces + 312);
    if (buf) {
        *this = dtostrf(value, (decimalPlaces + 2), decimalPlaces, buf);
        free(buf);
    } else {
        *this = "nan";
        printf("String::String(double value, unsigned int decimalPlaces): No enought memory for the operation.");
    }
}



String::String(long long value, unsigned char base) {
    
    char buf[2 + 8 * sizeof(long long)];
    if (base==10) {
        sprintf(buf, "%lld", value);   // NOT SURE - NewLib Nano ... does it support %lld? 
    } else {
        lltoa(value, buf, base);
    }
    *this = String(buf);
}

String::String(unsigned long long value, unsigned char base) {
    
    char buf[1 + 8 * sizeof(unsigned long long)];
    ulltoa(value, buf, base);
    *this = String(buf);
}




/***************************** Operator **************************************/




String String::operator+(const int v) {
	return *this + s_printf("%d", v);
}


String String::operator+(const uint16_t v) {
	return *this + s_printf("%u", v);
}




/***************************** equals **************************************/

unsigned char String::equalsIgnoreCase(const String &s2) const {

	if(this == &s2) // already equal
		return 1;
	if(len() != s2.len()) // make sure same length
		return 0;
	if(len() == 0) // empty string are equal
		return 1;
	
	const char *p1 = buffer();
	const char *p2 = s2.buffer();
	while(*p1) {
		if(tolower(*p1++) != tolower(*p2++))
			return 0;
	}
	return 1;

}


/***************************** start/ends with **************************************/


unsigned char String::startsWith(const String &s2) const {
	if(length() < s2.length())
		return 0;
	return startsWith(s2, 0);
}

unsigned char String::startsWith(const String &s2, unsigned int offset) const {
	if(offset > (unsigned)(length() - s2.length()) || !c_str() || !s2.c_str())
		return 0;
	return strncmp(&c_str()[offset], s2.c_str(), s2.length()) == 0;
}

unsigned char String::endsWith(const String &s2) const {
	if(length() < s2.length() || !c_str() || !s2.c_str())
		return 0;
	return strcmp(&c_str()[length() - s2.length()], s2.c_str()) == 0;
}



// /*********************************************/
// /*  Search                                   */
// /*********************************************/

int String::indexOf(char c) const {
	return indexOf(c, 0);
}

int String::indexOf(char ch, unsigned int fromIndex) const {
	if(fromIndex >= length())
		return -1;
	const char* temp = strchr(c_str() + fromIndex, ch);
	if(temp == NULL)
		return -1;
	return temp - c_str();
}

int String::indexOf(const String &s2) const {
	return indexOf(s2, 0);
}

int String::indexOf(const String &s2, unsigned int fromIndex) const {
	if(fromIndex >= length())
		return -1;
	const char *found = strstr(c_str() + fromIndex, s2.c_str());
	if(found == NULL)
		return -1;
	return found - c_str();
}


int String::lastIndexOf(char theChar) const {
	return find_last_of(theChar);
}

int String::lastIndexOf(char ch, unsigned int fromIndex) const {
	return find_last_of(ch, fromIndex);
}

int String::lastIndexOf(const String &s2) const {
	return find_last_of(s2);
}

int String::lastIndexOf(const String &s2, unsigned int fromIndex) const {
	return find_last_of(s2, fromIndex);
}


// /*********************************************/
// /*            Replace                        */
// https://stackoverflow.com/a/22402498/1683382
// https://stackoverflow.com/a/3418285/1683382
// /*********************************************/



void String::replace(char find, char replace) {
	if(!buffer())
		return;
	std::replace(begin(), end(), find, replace);
}

void String::replace(const String& str_from, const String& str_to) {
	size_t start_pos = 0;
    while((start_pos = find(str_from, start_pos)) != std::string::npos) {
        std::string::replace(start_pos, str_from.length(), str_to);
        start_pos += str_to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

// *********************************************
//   concat                                   
// https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/concat/
// *********************************************

unsigned char String::concat(const String &s) {
	*this += s;
	return 1;
}

unsigned char String::concat(const char *cstr, unsigned int length) {
    *this += String(cstr, length);
	return 1;
}

unsigned char String::concat(const char *cstr) {
    if(!cstr)
        return 0;
    return concat(cstr, strlen(cstr));
}

unsigned char String::concat(char c) {
    char buf[] = { c, '\0' };
    return concat(buf, 1);
}

unsigned char String::concat(unsigned char num) {
    char buf[1 + 3 * sizeof(unsigned char)];
    return concat(buf, sprintf(buf, "%d", num));
}

unsigned char String::concat(int num) {
    char buf[2 + 3 * sizeof(int)];
    return concat(buf, sprintf(buf, "%d", num));
}

unsigned char String::concat(unsigned int num) {
    char buf[1 + 3 * sizeof(unsigned int)];
    //utoa(num, buf, 10);
    //return concat(buf, strlen(buf));

	return concat(buf, sprintf(buf, "%u", num));
}

unsigned char String::concat(long num) {
    char buf[2 + 3 * sizeof(long)];
    return concat(buf, sprintf(buf, "%ld", num));
}

unsigned char String::concat(unsigned long num) {
    char buf[1 + 3 * sizeof(unsigned long)];
    //ultoa(num, buf, 10);
	//return concat(buf, strlen(buf));
	
	return concat(buf, sprintf(buf, "%lu", num));
    
}

unsigned char String::concat(float num) {
    char buf[20];
    char* string = dtostrf(num, 4, 2, buf);
    return concat(string, strlen(string));
}

unsigned char String::concat(double num) {
    char buf[20];
    char* string = dtostrf(num, 4, 2, buf);
    return concat(string, strlen(string));
}

unsigned char String::concat(long long num) {
    char buf[2 + 3 * sizeof(long long)];
    return concat(buf, sprintf(buf, "%lld", num));
}

unsigned char String::concat(unsigned long long num) {
    char buf[1 + 3 * sizeof(unsigned long long)];
    return concat(buf, sprintf(buf, "%llu", num));
}

unsigned char String::concat(const __FlashStringHelper * str) {
	*this += *str;
    return 1;
}



// /*********************************************/
// /*  trim                                     */
// https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/trim/
// /*********************************************/


// https://stackoverflow.com/a/216883/1683382

void String::trim() {
	String s = *this; //TODO improve

#if 0
	uint16_t i_start = 0;
	uint16_t i_end = s.length();
	
	for(;i_start < s.length(); i_start)
	{
		char c = s[i_start];
		if(!(
			c == ' '
			|| c == '\t'
			|| c == '\r'
			//TODO add rest from https://en.wikipedia.org/wiki/Whitespace_character
			))
			break;
	}

	for(;i_end > i_start; i_end--)
	{
		char c = s[i_end - 1];
		if(!(
			c == ' '
			|| c == '\t'
			|| c == '\r'
			//TODO add rest from https://en.wikipedia.org/wiki/Whitespace_character
			))
			break;
	}

	s = s.substring(i_start, i_end);
	
#else 

	boost::trim(s);

#endif 
	*this = s;
}


/**************************** remove **************************************/


void String::remove(unsigned int index) {
    *this = this->substring(0, index);
}

void String::remove(unsigned int index, unsigned int count) {
	*this = this->substring(0, index) + this->substring(index + count);
}



/**************************** misc **************************************/



void String::toLowerCase(void) {
	if(!buffer())
		return;
	for(char *p = (char*) buffer(); *p; p++) {
		*p = tolower(*p);
	}
}

void String::toUpperCase(void) {
	if(!buffer())
		return;
	for(char *p = (char*) buffer(); *p; p++) {
		*p = toupper(*p);
	}
}


long String::toInt(void) const {
	if (buffer())
		return atol(buffer());
	return 0;
}
