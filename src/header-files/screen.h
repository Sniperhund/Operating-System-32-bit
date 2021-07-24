#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"

void screen_init();
void screen_print_char(char c);
void screen_print_str(const char *str);