#ifndef RAND_H_234634
#define RAND_H_234634

#include <stdlib.h>

extern void rnd_init(void);
extern void rnd_deinit(void);
// extern int rnd_int(void);
static inline int rnd_int(void) {
    return rand();
}

#endif
