#include "string.h"
#include <stdarg.h>

char *itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char *p = b;
    if (i < 0)
    {
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do
    {
        ++p;
        shifter = shifter / 10;
    } while (shifter);
    *p = '\0';
    do
    {
        *--p = digit[i % 10];
        i = i / 10;
    } while (i);
    return b;
}

int strlen(const char *format)
{
    char *p = format;
    int num;

    while (*p != 0)
    {
        num++;
        p++;
    }
    return num;
}