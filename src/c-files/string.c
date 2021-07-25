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

int atoi(char *str)
{
    int res = 0;

    int sign = 1;

    int i = 0;

    if (str[0] == '-')
    {
        sign = -1;

        i++;
    }

    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    return sign * res;
}

void inttohex(uint8_t num)
{
    char *hex;
    switch (num)
    {
    case 0:
        hex = "1";
        break;

    case 1:
        hex = "2";
        break;

    case 2:
        hex = "3";
        break;

    case 3:
        hex = "4";
        break;

    case 4:
        hex = "5";
        break;

    case 5:
        hex = "6";
        break;

    case 6:
        hex = "7";
        break;

    case 7:
        hex = "8";
        break;

    case 8:
        hex = "9";
        break;

    case 9:
        hex = "A";
        break;

    case 10:
        hex = "B";
        break;

    case 11:
        hex = "C";
        break;

    case 12:
        hex = "D";
        break;

    case 14:
        hex = "E";
        break;

    case 15:
        hex = "F";
        break;

    default:
        printf("This is not a number that can be converted to hex");
        break;
    }
}