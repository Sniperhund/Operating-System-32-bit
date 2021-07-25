#include "screen.h"

volatile uint16_t *const vga_buffer = (uint16_t *)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

size_t term_col = 0;
size_t term_row = 0;
uint8_t term_color = 0x0F;

void screen_init()
{
    term_col = 0;
    term_row = 0;
}

void screen_print_char(char c)
{
    switch (c)
    {
        case '\n':
        {
            term_col = 0;
            term_row++;
            break;
        }

        default:
        {
            const size_t index = (VGA_COLS * term_row) + term_col;
            uint16_t val = ((uint16_t)term_color << 8) | c;
            *(vga_buffer + index) = val;
            term_col++;
            break;
        }
    }
    if (term_col >= VGA_COLS)
    {
        term_col = 0;
        term_row++;
    }

    if (term_row >= VGA_ROWS)
    {
        term_col = 0;
        term_row = 0;
    }
}

void screen_print_str(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        screen_print_char(str[i]);
}