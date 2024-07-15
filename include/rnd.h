#ifndef RAND_H_234634
#define RAND_H_234634

#include <stdlib.h>
#include <time.h>

static void rnd_init(void) {
    srand(time(0));
}

static inline int rnd_int(void) {
    return rand();
}

#endif
