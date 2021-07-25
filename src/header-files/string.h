#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"

char *itoa(int i, char b[]);
int strlen(const char *format);
void inttohex(uint8_t num);
void *memcpy(void *dest, const void *src, size_t size);