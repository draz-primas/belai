#include <stdio.h>
#include "ai.h"
#include "core.h"
#include "popravi.h"
#include "start.h"

extern FILE *junk_out;

/* kod ucitavanje karte
 * T - 0 - tref zir
 * K - 1 - karo zvono
 * H - 2 - herc srce
 * P - 3 - pik list
 */

static char string[16];
static char scanchar(void) {
    scanf("%s", string);
    return string[0];
}

int ucitaj_kartu(void) {
    char boja;
    char znak;
    int t1, t2;
input1:
    scanf("%s", string);
    boja = string[0];
    znak = string[1];
    switch (boja) {
        case 't':
        case 'T': t1 = 0; break;
        case 'k':
        case 'K': t1 = 1; break;
        case 'h':
        case 'H': t1 = 2; break;
        case 'p':
        case 'P': t1 = 3; break;
        default:
        fprintf(junk_out, "kriva boja\n");
        goto input1;
    }
    switch (znak) {
        case '7': t2 = 0; break;
        case '8': t2 = 1; break;
        case '9': t2 = 2; break;
        case 'x':
        case 'X': t2 = 3; break;
        case 'j':
        case 'J': t2 = 4; break;
        case 'q':
        case 'Q': t2 = 5; break;
        case 'k':
        case 'K': t2 = 6; break;
        case 'a':
        case 'A': t2 = 7; break;
        default:
        fprintf(junk_out, "krivi znak\n");
        goto input1;
    }
    return t1*8 + t2;
}

void ucitaj_moju_kartu(int i, struct bela_stanje *s) {
    int karta = ucitaj_kartu();
    s->moje_karte[i] = karta;
    for (int j = 0; j < 4; ++j)
        s->karte[j][s->moje_karte[i]] = nema;
    s->karte[0][s->moje_karte[i]] = ima;
}

struct bela_stanje start(void) {
    struct bela_stanje s = {
        .moje_karte = {0},
        .karte = {{0}},
        .baceno = 0,
        .stih = {0},
        .moze = {0},
        .sijeceno = 0,
        .najjaca = -1,
        .bodovi = {0},
        .runda = 0,
        .bacili = {0},
    };
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 32; ++j)
            s.karte[i][j] = mozda;

    for (int i = 0; i < 6; ++i) {
        fprintf(junk_out, "karta %d: ", i+1);
        ucitaj_moju_kartu(i, &s);
    }

    fprintf(junk_out, "tko je prvi (ako sam ja 0)? ");
    scanf("%d", &s.prvi);
    s.sljedeci_na_redu = s.prvi;
    s.na_redu = s.prvi;

    /* biranje aduta */
    /* @TODO:
     * podijeli sve karte osim prvih 6 nasumicno
     * odigraj random partije s adutima po redu i izaberi adut s najvise
     * pobjeda ili bodova ili nemoj
     * izaberi adut ako jako povecava win rate il nes
     * neznam
     */
    s.adut = 0;
    char c;
    int izabran = 0;

    input4:
    fprintf(junk_out, "jeli adut izabran? [y/n]: ");
    c = scanchar();
    if (c == 'y') {
        izabran = 1;
    }
    else if (c != 'n') {
        fprintf(junk_out, "moras napisat y ili n\n");
        goto input4;
    }

    if (!izabran) {
        // @TODO: biraj adut koji nije random
        s.adut = izaberi_kartu(&s, 1, s.prvi == 1);
        if (s.adut == -1) goto input2;
        printf("%c\n", znakovi[s.adut]);
        fflush(stdout);
    }
    else {
    input2:
        printf("dalje\n");
        fflush(stdout);
        fprintf(junk_out, "adut: ");
        char c;
        c = scanchar();
        switch (c) {
            case 't':
            case 'T': s.adut = 0; break;
            case 'k':
            case 'K': s.adut = 1; break;
            case 'h':
            case 'H': s.adut = 2; break;
            case 'p':
            case 'P': s.adut = 3; break;
            default:
            fprintf(junk_out, "kriva boja\n");
            goto input2;
        }
    }

    /* talon */
    for (int i = 6; i < 8; ++i) {
        fprintf(junk_out, "karta %d: ", i+1);
        ucitaj_moju_kartu(i, &s);
    }

    for (int i = 0; i < 32; ++i)
        if (s.karte[0][i] == mozda)
            s.karte[0][i] = nema;

    /* zvanja */
    // @TODO: moja zvanja
    fprintf(junk_out, "zvanja:\n");
    for (int i = 1; i < 4; ++i) {
        char c = ' ';

        input3:
        fprintf(junk_out, "igrac %d: [y/n]: ", i);
        c = scanchar();
        if (c == 'y') {
            int n = 0;
            fprintf(junk_out, "broj karata: ");
            scanf("%d", &n);
            for (int j = 0; j < n; ++j) {
                fprintf(junk_out, "karta %d: ", j+1);
                int karta = ucitaj_kartu();
                for (int k = 0; k < 4; ++k)
                    s.karte[k][karta] = nema;
                s.karte[i][karta] = ima;
                popravi(&s);
            }
        }
        else if (c != 'n') {
            fprintf(junk_out, "moras upisat y ili n\n");
            goto input3;
        }
    }

    return s;
}
