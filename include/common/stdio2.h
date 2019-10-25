#ifndef STDIO2_H
#define STDIO2_H

char getc2(void);
void putc2(char c);

void puts2(const char * s);

// This version of gets copies until newline, replacing newline with null char, or until buflen.
// whichever comes first
void gets2(char * buf, int buflen);

int printf2(const char *format, ...);

#endif

