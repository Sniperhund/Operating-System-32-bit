#include "kernel.h"
#include "screen.h"

void kernel_main()
{
    screen_init();
    screen_print_str("Testing");
    printf("After like 100 years finally everything works except the console color!");
}