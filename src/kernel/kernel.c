#include "kernel.h"
#include "screen.h"

void kernel_main()
{
    screen_init();
    printf("After like 100 years finally everything works except the console color!");
}