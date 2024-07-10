// #include <stdio.h>
#include "popravi.h"
#include "core.h"

int promjenjeno;

void popravi(struct bela_stanje *s) {
loop:
    promjenjeno = 0;
    /* situacija X+XX */
    for (int j = 0; j < 32; ++j) {
        int n = 0;
        int t = 0;
        for (int k = 0; k < 4; ++k) {
            n += s->karte[k][j] == nema;
            t += s->karte[k][j] == ima;
        }

        if (n != 3 && t) {
            // printf("promjenjeno 1, 1: %d\n", j);
            promjenjeno = 1;
            for (int k = 0; k < 4; ++k)
                if (s->karte[k][j] == mozda) s->karte[k][j] = nema;
        }
        if (n == 3 && !t) {
            // printf("promjenjeno 1, 2: %d\n", j);
            promjenjeno = 1;
            for (int k = 0; k < 4; ++k)
                if (s->karte[k][j] == mozda) s->karte[k][j] = ima;
        }
    }

    /* slicna stvar */
    for (int j = 0; j < 4; ++j) {
        int nima = 0;
        int nnema = 0;
        for (int k = 0; k < 32; ++k) {
            nima  += s->karte[j][k] == ima;
            nnema += s->karte[j][k] == nema;
        }

        int praznih = 32-nima-nnema;
        int ima_karata = 8-s->runda-s->bacili[j];
        /* mora imat i ostale onda */
        if (praznih && praznih + nima == ima_karata) {
            // printf("promjenjeno 2, 1: %d\n", j);
            promjenjeno = 1;
            for (int k = 0; k < 32; ++k)
                if (s->karte[j][k] == mozda)
                    s->karte[j][k] = ima;
        }
        /* onda nema nijednu od ostalih */
        if (nima == ima_karata && praznih != 0) {
            // printf("promjenjeno 2, 2: %d\n", j);
            promjenjeno = 1;
            for (int k = 0; k < 32; ++k)
                if (s->karte[j][k] == mozda)
                    s->karte[j][k] = nema;
        }
    }
    if (promjenjeno) goto loop;
}
