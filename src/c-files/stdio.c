#include "stdio.h"

void printf(char *format, ...)
{
    va_list L;
    va_start(L, format);

    char *p = format;

    while (*p != 0)
    {
        char mychar = *p;

        if (mychar == '%')
        {
            p++;
            char mychar2 = *p;
            switch (mychar2)
            {
                case 'd':
                {
                    int x = va_arg(L, int);
                    char buffer[12];
                    itoa(x, buffer);
                    printf("%s", buffer);
                }
                break;
                case 's':
                {
                    char *s = va_arg(L, char*);
                    while (*s != 0)
                    {
                        screen_print_char(*s);
                        s++;
                    }
                }
                break;
            }
        }
        else
        {
            screen_print_char(*p);
        }
        p++;
    }

    va_end(L);
}