#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init(void);
void writeChar(char c);
char readChar(void);
void writeString(char *str);

#endif // _SERIAL_H
