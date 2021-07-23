#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void term_init();
void term_putc(char c);
void term_print(const char *str);