#include <stdio.h>
#include "rnd.h"

static FILE *file = NULL;

void rnd_init(void) {
    file = fopen("/dev/urandom", "r");
    if (file == NULL)
        printf("nisam uspio otvorit /dev/urandom");
}

void rnd_deinit(void) {
    fclose(file);
}

int rnd_int(void) {
    int n;
    if (fread(&n, sizeof(int), 1, file) != 1) {
        printf("nisam uspio procitat /dev/urandom");
    }
    /* stavi sign bit na 0 da uvijek bude pozitivno */
    /* nece radit ako int nije 4 bajta */
    n &= 0x7FFFFFFF;
    return n;
}
