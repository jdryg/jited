#ifndef _CTYPE_H
#define _CTYPE_H

// C11 7.4.1 Character classification functions
int isalnum(int c);
int isalpha(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

// C11 7.4.2 Character case mapping functions
int tolower(int ch);
int toupper(int ch);

#endif // _CTYPE_H
