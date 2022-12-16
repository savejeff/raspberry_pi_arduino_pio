#pragma once 


char *dtostrf(double val, signed char width, unsigned char prec, char *sout);

#if 0
void *	 memccpy (void *__restrict, const void *__restrict, int, size_t);
#endif



char * utoa (unsigned int value, char *str, int base);


#ifndef VARIANTE_NATIVE_WINDOWS
char * ultoa (unsigned long value, char *str, int base);

char * itoa (int value, char *str, int base);
char * ltoa (long value, char *str, int base);

#endif 

char * lltoa (long long value, char *str, int base);

char * ulltoa (unsigned long long value, char *str, int base);



//#define ltoa utoa