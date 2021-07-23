#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

char *itoa(int i, char b[]);
int strlen(const char *format);
void inttohex(uint8_t num);