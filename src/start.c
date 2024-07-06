#include <stdio.h>
#include "rnd.h"
#include "core.h"

/* kod ucitavanje karte
 * T - 0 - tref zir
 * H - 1 - herc srce
 * P - 2 - pik list
 * K - 3 - karo zvono
 */

static int ucitaj_kartu(void) {
    char boja;
    char znak;
    int t1, t2;
input1:
    scanf("%c%c", &boja, &znak);
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
    return t1*8 + t2;
}

struct bela_stanje start(void) {
    int moje_karte[8] = {0};

    for (int i = 0; i < 6; ++i) {
        printf("karta %d: ", i+1);
        moje_karte[i] = ucitaj_kartu();
    }

    int prvi = 0;
    printf("tko je prvi (ako sam ja 0)? ");
    scanf("%d", &prvi);

    /* biranje aduta */
    int adut = 0;
    if (rnd_int() % 2) {
        adut = rnd_int()%4 +1;
        printf("adut: %c", znakovi[adut]);
    }
    else {
    input2:
        printf("dalje\nadut: ");
        char c;
        scanf("%c", &c);
        switch (c) {
            case 'T': adut = 0; break;
            case 'H': adut = 1; break;
            case 'P': adut = 2; break;
            case 'K': adut = 3; break;
            default:
            printf("kriva boja");
            goto input2;
        }
    }

    /* talon */
    for (int i = 6; i < 8; ++i) {
        printf("karta %d: ", i+1);
        moje_karte[i] = ucitaj_kartu();
    }

    struct bela_stanje stanje = {
        .moje_karte = {0},
        .karte = {0},
        .adut = adut,
        .baceno = 0,
        .na_redu = prvi,
        .stih = {0},
        .prvi = prvi,
    };

    for (int i = 1; i < 4; ++i)
        for (int j = 0; j < 32; ++j)
            stanje.karte[i][j] = mozda;

    /* moje karte */
    /* 0 sam ja */
    for (int i = 0; i < 8; ++i)
        stanje.moje_karte[i] = moje_karte[i];
    for (int i = 0; i < 32; ++i)
        stanje.karte[0][i] = nema;
    for (int i = 0; i < 8; ++i)
        stanje.karte[0][moje_karte[i]] = ima;

    return stanje;
}
