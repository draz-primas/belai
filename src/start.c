#include <stdio.h>
#include "core.h"

void start(void) {
    int moje_karte[8] = {0};
    for (int i = 0; i < 6; ++i) {
        input1:
        printf("karta %d", i+1);
        char boja;
        char znak;
        scanf("%c%c", &boja, &znak);
        int t1, t2;
        /*
         * T - 0 - tref zir
         * H - 1 - herc srce
         * P - 2 - pik list
         * K - 3 - karo zvono
         */
        switch (boja) {
            case 'T': t1 = 0; break;
            case 'H': t1 = 1; break;
            case 'P': t1 = 2; break;
            case 'K': t1 = 3; break;
            default:
            printf("kriva boja");
            goto input1;
        }
        switch (znak) {
            case '7': t2 = 0; break;
            case '8': t2 = 1; break;
            case '9': t2 = 2; break;
            case 'J': t2 = 3; break;
            case 'D': t2 = 4; break;
            case 'K': t2 = 5; break;
            case 'X': t2 = 6; break;
            case 'A': t2 = 7; break;
            default:
            printf("krivi znak");
            goto input1;
        }
        moje_karte[i] = t1*8 + t2;
    }
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
