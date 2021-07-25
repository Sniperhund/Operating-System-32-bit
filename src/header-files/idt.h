#pragma once
//
// Created by lucas on 7/25/21.
//

void init_idt(void);
void init_idt_desc(uint16_t select, uint32_t offset, uint8_t type, struct IDTDescr *desc);
void test();