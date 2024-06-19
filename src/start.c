#include "core.h"

void start(void) {
    /* @TODO: dobi ovo */
    int moje_karte[8] = {0};
    /* @TODO: popravi */
    struct bela_stanje stanje = {
        .karte = {0},
        .adut = 0,
        .baceno = 0,
        .na_redu = 0,
        .stih = {0},
        .prvi = 0,
    };
    for (int i = 0; i < 8; ++i) {
        /* 0 sam ja */
        stanje.karte[0][moje_karte[i]] = ima;
    }
}
