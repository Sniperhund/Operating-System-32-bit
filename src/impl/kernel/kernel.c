#include "header-files/kernel.h"

char *os_version;

void kernel_main()
{
    os_version = "0.0.2";

    init();

    while (true)
    {
        printf(".");
    }
}

void init()
{
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);

    int number = strlen("idk?");
    printf("Strlen test: %d", number);
}