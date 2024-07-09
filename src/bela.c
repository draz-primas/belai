#include "core.h"
#include "bela.h"

int jaca(int ova, int od_ove, int adut) {
    int *skala = adut ? bodovi_adut : bodovi;
    if (skala[ova%8] == skala[od_ove%8]) /* npr. 7 i 8 */
        return ova > od_ove;
    return skala[ova%8] > skala[od_ove%8];
}

void moze_se_bacit(struct bela_stanje *s) {
    int imam_dobru_boju = 0;
    int imam_adut = 0;
    int imam_jacu = 0;
    const int pocetna_boja = s->stih[0]/8;
    const int jeli_adut = pocetna_boja == s->adut;

    /* ako sam prvi na redu sve je dobro */
    if (s->baceno == 0) goto sve_su_dobre;

    for (int i = 0; i < 8; ++i) {
        if (s->moje_karte[i]/8 == pocetna_boja) {
            imam_dobru_boju = 1;

            int jacat = 1;
            for (int j = 0; j < s->baceno; ++j)
                if (s->stih[j]/8 == pocetna_boja &&
                !jaca(s->moje_karte[i], s->stih[j], jeli_adut))
                    jacat = 0;

            if (jacat) imam_jacu = 1;
        }
        if (s->moje_karte[i]/8 == s->adut) imam_adut = 1;
    }

    if (imam_dobru_boju) {
        if (imam_jacu && !s->sijeceno) {
            /* mora bit jaca */
            for (int i = 0; i < 8; ++i)
                s->moze[i] = s->moje_karte[i]/8 == pocetna_boja &&
                    jaca(s->moje_karte[i], s->najjaca, jeli_adut);
            return;
        }
        /* ako nemam jacu onda mora imat istu boju */
        for (int i = 0; i < 8; ++i)
            s->moze[i] = s->moje_karte[i]/8 == pocetna_boja;
        return;
    }
    /* nemam dobru boju */
    if (imam_adut) {
        /* moram jacu */
        int imam_jaci_adut = 0;
        for (int i = 0; i < 8; ++i)
            if (s->moje_karte[i]/8 == s->adut && jaca(s->moje_karte[i], s->najjaca, 1))
                imam_jaci_adut = 1;

        if (imam_jaci_adut) {
            for (int i = 0; i < 8; ++i)
                s->moze[i] = s->moje_karte[i]/8 == s->adut &&
                  jaca(s->moje_karte[i], s->najjaca, 1);
            return;
        }
        /* inace su svi aduti dobri */
        for (int i = 0; i < 8; ++i)
            s->moze[i] = s->moje_karte[i]/8 == s->adut;
        return;
    }

    /* nemam adut ni pravu boju */
    sve_su_dobre:
    for (int i = 0; i < 8; ++i)
        s->moze[i] = s->moje_karte[i] != -8;
    return;
}
