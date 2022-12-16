#include "lowlevelfuncs.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *dtostrf(double val, signed char width, unsigned char prec, char *sout)
{
	//Commented code is the original version
	/*char fmt[20];
	sprintf(fmt, "%%%d.%df", width, prec);
	sprintf(sout, fmt, val);
	return sout;*/

	// Handle negative numbers
	uint8_t negative = 0;
	if (val < 0.0) {
		negative = 1;
		val = -val;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (int i = 0; i < prec; ++i) {
		rounding /= 10.0;
	}

	val += rounding;

	// Extract the integer part of the number
	unsigned long int_part = (unsigned long)val;
	double remainder = val - (double)int_part;

	if (prec > 0) {
		// Extract digits from the remainder
		unsigned long dec_part = 0;
		double decade = 1.0;
		for (int i = 0; i < prec; i++) {
		decade *= 10.0;
		}
		remainder *= decade;
		dec_part = (int)remainder;

		if (negative) {
		sprintf(sout, "-%ld.%0*ld", int_part, prec, dec_part);
		} else {
		sprintf(sout, "%ld.%0*ld", int_part, prec, dec_part);
		}
	} else {
		if (negative) {
		sprintf(sout, "-%ld", int_part);
		} else {
		sprintf(sout, "%ld", int_part);
		}
	}
	// Handle minimum field width of the output string
	// width is signed value, negative for left adjustment.
	// Range -128,127
	char fmt[129] = "";
	unsigned int w = width;
	if (width < 0) {
		negative = 1;
		w = -width;
	} else {
		negative = 0;
	}

	if (strlen(sout) < w) {
		memset(fmt, ' ', 128);
		fmt[w - strlen(sout)] = '\0';
		if (negative == 0) {
		char *tmp = (char *) malloc(strlen(sout) + 1);
		strcpy(tmp, sout);
		strcpy(sout, fmt);
		strcat(sout, tmp);
		free(tmp);
		} else {
		// left adjustment
		strcat(sout, fmt);
		}
	}

	return sout;
}





#if 0

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
	Return the position in DEST one byte past where C was copied, or
	NULL if C was not found in the first N bytes of SRC.
	*/
//https://en.cppreference.com/w/c/string/byte/memccpy
void * memccpy (void *dest, const void *src, int c, size_t n)
{
	/*for(size_t i = 0; i < n; i++)
	{
		*dest++
	}*/
	// https://opensource.apple.com/source/Libc/Libc-167/string.subproj/memccpy.c.auto.html
	if (n) {
		unsigned char *tp = (unsigned char*) dest;
		const unsigned char *fp = (unsigned char*) src;
		do {
			if ((*tp++ = *fp++) == c)
				return (tp);
		} while (--n != 0);
	}
	return (0);
	
	// https://elixir.bootlin.com/glibc/latest/source/string/string.h#L381
	/*
	void *p = memchr (src, c, n);

	if (p != NULL)
		return __mempcpy (dest, src, p - src + 1);

	memcpy (dest, src, n);
	return NULL;
	*/
}

#endif



/***************************** utoa **************************************/

#include <stdlib.h>

// source: https://github.com/bminor/newlib/blob/master/newlib/libc/stdlib/utoa.c

char* utoa (unsigned int value, char *str, int base)
{
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i, j;
	unsigned int remainder;
	char c;

	// Check base is supported
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}
		
	// Convert to string. Digits are in reverse order
	i = 0;
	do 
	{
		remainder = value % base;
		str[i++] = digits[remainder];
		value = value / base;
	} while (value != 0);
	str[i] = '\0'; 

	// Reverse string
	for (j = 0, i--; j < i; j++, i--)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c; 
	} 

	return str;
}


char* ultoa (unsigned long value, char *str, int base) 
{
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i, j;
	unsigned long remainder;
	char c;

	// Check base is supported
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}
		
	// Convert to string. Digits are in reverse order
	i = 0;
	do 
	{
		remainder = value % base;
		str[i++] = digits[remainder];
		value = value / base;
	} while (value != 0);
	str[i] = '\0'; 

	// Reverse string
	for (j = 0, i--; j < i; j++, i--)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c; 
	} 

	return str;
}



#ifndef VARIANTE_NATIVE_WINDOWS


char* itoa (int value, char *str, int base)
{
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i, j;
	int remainder;
	char c;

	// Check base is supported
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}
		
	// Convert to string. Digits are in reverse order
	bool isneg = value < 0;
	if(isneg)
		value = -value;

	i = 0;
	do 
	{
		remainder = value % base;
		str[i++] = digits[remainder];
		value = value / base;
	} while (value != 0);
	
	
	if(isneg)
		str[i++] = '-';
	
	str[i] = '\0'; 

	// Reverse string
	for (j = 0, i--; j < i; j++, i--)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c; 
	} 

	return str;
}


char* ltoa (long value, char *str, int base)
{
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i, j;
	long remainder;
	char c;

	// Check base is supported
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}
		
	// Convert to string. Digits are in reverse order
	bool isneg = value < 0;
	if(isneg)
		value = -value;

	i = 0;
	do 
	{
		remainder = value % base;
		str[i++] = digits[remainder];
		value = value / base;
	} while (value != 0);
	
	
	if(isneg)
		str[i++] = '-';
	
	str[i] = '\0'; 

	// Reverse string
	for (j = 0, i--; j < i; j++, i--)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c; 
	} 

	return str;
}

#endif // VARIANTE_NATIVE_WINDOWS



char* lltoa (long long value, char *str, int base)
{
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i, j;
	long long remainder;
	char c;

	// Check base is supported
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}
		
	// Convert to string. Digits are in reverse order
	bool isneg = value < 0;
	if(isneg)
		value = -value;

	i = 0;
	do 
	{
		remainder = value % base;
		str[i++] = digits[remainder];
		value = value / base;
	} while (value != 0);
	
	
	if(isneg)
		str[i++] = '-';
	
	str[i] = '\0'; 

	// Reverse string
	for (j = 0, i--; j < i; j++, i--)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c; 
	} 

	return str;
}


char* ulltoa (unsigned long long value, char *str, int base)
{
	const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i, j;
	unsigned long long remainder;
	char c;

	// Check base is supported
	if ((base < 2) || (base > 36))
	{ 
		str[0] = '\0';
		return NULL;
	}
		
	// Convert to string. Digits are in reverse order
	i = 0;
	do 
	{
		remainder = value % base;
		str[i++] = digits[remainder];
		value = value / base;
	} while (value != 0);
	str[i] = '\0'; 

	// Reverse string
	for (j = 0, i--; j < i; j++, i--)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c; 
	}

	return str;
}
