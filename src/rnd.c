#include <stdio.h>
#include "rnd.h"

static FILE *file = NULL;

void rnd_init(void) {
    file = fopen("/dev/urandom", "r");
}

void rnd_deinit(void) {
    fclose(file);
}

int rnd_byte(void) {
    int n;
    fread(&n, sizeof(int), 1, file);
    return n;
}
