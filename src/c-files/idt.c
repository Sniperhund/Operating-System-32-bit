#define IDTBASE    0x00000000
#define IDTSIZE 0xFF

#include <stdint.h>
#include "stdio.h"
#include "string.h"
#include "../kernel/interrupt.h"

volatile struct IDTDescr {
    uint16_t offset_1; // offset bits 0..15
    uint16_t selector; // a code segment selector in GDT or LDT
    uint8_t zero;      // unused, set to 0
    uint8_t type_attr; // type and attributes, see below
    uint16_t offset_2; // offset bits 16..31
};

volatile struct idtr {
    uint16_t limite;
    uint32_t base;
};

struct IDTDescr kidt[256];
struct idtr kidtr;

void init_idt_desc(uint16_t select, uint32_t offset, uint8_t type, struct IDTDescr *desc)
{
    desc->offset_1 = (offset & 0xffff);
    desc->selector = select;
    desc->zero = 0x0;
    desc->type_attr = type;
    desc->offset_2 = (offset & 0xffff0000) >> 16;
    return;
}

void test() {
    printf("I love dogs!");
}

void init_idt(void)
{
    __asm__("cli");
    /* Init irq */
    for (int i = 0; i < IDTSIZE; i++)
        init_idt_desc(0x08, (uint32_t) interrupt_handler, INTGATE, &kidt[i]);

    test();
    /* Vectors  0 -> 31 are for exceptions */
    init_idt_desc(0x08, (uint32_t) interrupt_handler, INTGATE, &kidt[13]);
    init_idt_desc(0x08, (uint32_t) interrupt_handler, INTGATE, &kidt[14]);

    init_idt_desc(0x08, (uint32_t) interrupt_handler, INTGATE, &kidt[32]);
    init_idt_desc(0x08, (uint32_t) interrupt_handler, INTGATE, &kidt[33]);

    init_idt_desc(0x08, (uint32_t) interrupt_handler, TRAPGATE, &kidt[48]);
    init_idt_desc(0x08, (uint32_t) interrupt_handler, TRAPGATE, &kidt[128]); // 48

    /*
    init_idt_desc(0x08, (uint32_t) _asm_exc_GP, INTGATE, &kidt[13]);
    init_idt_desc(0x08, (uint32_t) _asm_exc_PF, INTGATE, &kidt[14]);

    init_idt_desc(0x08, (uint32_t) _asm_schedule, INTGATE, &kidt[32]);
    init_idt_desc(0x08, (uint32_t) _asm_int_1, INTGATE, &kidt[33]);

    init_idt_desc(0x08, (uint32_t) _asm_syscalls, INTGATE, &kidt[48]);
    init_idt_desc(0x08, (uint32_t) _asm_syscalls, INTGATE, &kidt[128]);
    */

    kidtr.limite = IDTSIZE * 8;
    kidtr.base = IDTBASE;


    /* Copy the IDT to the memory */
    memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

    /* Load the IDTR registry */
    __asm__("lidt (kidtr)");
    __asm__("sti");
}

