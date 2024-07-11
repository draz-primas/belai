#include <stdio.h>
#include "core.h"
// #include "bela.h"

static inline int jaca(int ova, int od_ove, int adut) {
    int *skala = adut ? bodovi_adut : bodovi;
    if (skala[ova%8] == skala[od_ove%8]) /* npr. 7 i 8 */
        return ova > od_ove;
    return skala[ova%8] > skala[od_ove%8];
}

static inline void moze_se_bacit(struct bela_stanje *s, int kartee[8]) {
    int *karte = s->moje_karte;
    if (kartee != NULL) karte = kartee;
    int imam_dobru_boju = 0;
    int imam_adut = 0;
    int imam_jacu = 0;
    const int pocetna_boja = s->stih[0]/8;
    const int jeli_adut = pocetna_boja == s->adut;

    /* ako sam prvi na redu sve je dobro */
    if (s->baceno == 0) goto sve_su_dobre;

    for (int i = 0; i < 8; ++i) {
        if (karte[i]/8 == pocetna_boja) {
            imam_dobru_boju = 1;

            int jacat = 1;
            for (int j = 0; j < s->baceno; ++j)
                if (s->stih[j]/8 == pocetna_boja &&
                !jaca(karte[i], s->stih[j], jeli_adut))
                    jacat = 0;

            if (jacat) imam_jacu = 1;
        }
        if (karte[i]/8 == s->adut) imam_adut = 1;
    }

    if (imam_dobru_boju) {
        if (imam_jacu && !s->sijeceno) {
            /* mora bit jaca */
            for (int i = 0; i < 8; ++i)
                s->moze[i] = karte[i]/8 == pocetna_boja &&
                    jaca(karte[i], s->najjaca, jeli_adut);
            // printf("mora jacu od ");
            // printaj_kartu(s->najjaca);
            return;
        }
        /* ako nemam jacu onda mora imat istu boju */
        for (int i = 0; i < 8; ++i)
            s->moze[i] = karte[i]/8 == pocetna_boja;
        // printf("nema jacu ali mora istu boju\n");
        return;
    }
    /* nemam dobru boju */
    if (imam_adut) {
        /* moram jacu */
        int imam_jaci_adut = 0;
        for (int i = 0; i < 8; ++i)
            if (karte[i]/8 == s->adut && jaca(karte[i], s->najjaca, 1))
                imam_jaci_adut = 1;

        if (imam_jaci_adut) {
            for (int i = 0; i < 8; ++i)
                s->moze[i] = karte[i]/8 == s->adut &&
                  jaca(karte[i], s->najjaca, 1);
            // printf("mora jaci adut\n");
            return;
        }
        /* inace su svi aduti dobri */
        for (int i = 0; i < 8; ++i)
            s->moze[i] = karte[i]/8 == s->adut;
        // printf("bilo koji adut\n");
        return;
    }

    /* nemam adut ni pravu boju */
    sve_su_dobre:
    for (int i = 0; i < 8; ++i)
        s->moze[i] = karte[i] != -8;
    // printf("sve su dobre\n");
    return;
}

static inline void izbroji_stih(struct bela_stanje *s) {
    int *dobiva = &s->bodovi[s->sljedeci_na_redu%2];
    for (int i = 0; i < 4; ++i) {
        int karta = s->stih[i];
        *dobiva += karta/8 == s->adut ?
        bodovi_adut[karta%8] : bodovi[karta%8];
    }
    if (s->runda == 7) *dobiva += 10;
}

static inline void printaj_kartu(int karta) {
    if (karta == -8) {
        printf("--\n");
        return;
    }
    // @TODO zamijeni imena;
    char boja = znakovi[karta/8];
    char boje[] = {'7','8','9','X','J','Q','K','A'};
    char znak = boje[karta%8];
    printf("%c%c", boja, znak);
}
