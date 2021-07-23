#define IVT_BASE 0x0000

void interupt_handler() {
    printf("Interupt handler was called\n");
}

void setup_interupt_vector_table() {
    return;
}