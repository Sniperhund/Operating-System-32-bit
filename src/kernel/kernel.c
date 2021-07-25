#include "kernel.h"
#include "screen.h"
#include "idt.h"

void kernel_main()
{
    screen_init();
    //screen_print_char('H');
    //screen_print_char('E');
    //screen_print_char('L');
    //screen_print_char('L');
    //screen_print_char('O');
    printf("After like 100 years finally \neverything works except the console color!");
    init_idt();
    for (int i = 0; i < 25; i++)
        printf("Number: %d\n", i);
}