#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL_timer.h>
#include "ai.h"
#include "core.h"
#include "bela.h"
#include "render.h"
#include "rnd.h"
#include "popravi.h"
#include "render.h"

static int konfiguracija = 500;
static int igara = 500;

extern int bacili[4];

struct prazne {
    int ptr[32];
    int n;
};

double wins[8];
double bod[8];
int odigrano[8];

static struct bela_stanje podijeli_karte(struct bela_stanje *s) {
    static int ptr[32];
    static int n;
    struct bela_stanje stanje = *s;
    /* podijeli karte nasumicno:
     * kreni od igraca 1, daj mu random kartu, popravi tablicu
     * ponavljaj dok nema dovoljno karata
     * ponovi za svakog igraca
     */
    for (int igrac = 1; igrac < 4; ++igrac) {
        while (1) {
            n = 0;
            for (int i = 0; i < 32; ++i) {
                if (stanje.karte[igrac][i] == mozda) {
                    ptr[n] = i;
                    n++;
                }
            }

            if (n == 0) break;
            int karta = rnd_int()%n;
            stanje.karte[igrac][ptr[karta]] = ima;
            for (int i = 0; i < 4; ++i) {
                if (stanje.karte[i][ptr[karta]] == mozda) {
                    stanje.karte[i][ptr[karta]] = nema;
                }
            }
            popravi(&stanje);
        }
    }
    return stanje;
}

static void odigraj_partiju(struct bela_stanje s, int karte[4][8]) {
    int karta;
    int prva = 1;
    int prva_karta = 0;
    for (; s.runda < 8; ++s.runda) {
        if (!prva) {
            s.sijeceno = 0;
            s.prvi = s.sljedeci_na_redu;
            s.najjaca = -1;
            s.na_redu = s.prvi;
            s.baceno = 0;
        }
        for (int i = 0; i < 4; ++i) s.bacili[i] = 0;
        for (; s.baceno < 4; ++s.baceno) {
            s.bacili[s.na_redu] = 1;
            moze_se_bacit(&s, karte[s.na_redu]);
            int n = 0;
            int ptrs[8];
            for (int j = 0; j < 8; ++j) {
                if (s.moze[j]) {
                    ptrs[n] = j;
                    n++;
                }
            }

            if (n == 0) {
                printf("auzmes\n");
                exit(0);
            }
            int rndi = ptrs[rnd_int()%n];
            karta = karte[s.na_redu][rndi];
            karte[s.na_redu][rndi] = -8;

            if (prva) {
                prva = 0;
                prva_karta = rndi;
            }

            int boja = karta/8;
            s.stih[s.baceno] = karta;
            int prva_boja = s.stih[0]/8;
            if (s.baceno == 0) {
                s.sljedeci_na_redu = s.na_redu;
                s.najjaca = karta;
            }

            if ((prva_boja != s.adut) && boja == s.adut) {
                int t = 1;
                if (s.sijeceno) {
                    for (int j = 0; j < s.baceno; ++j) {
                        if (s.stih[j]/8 == s.adut && jaca(s.stih[j], karta, 1)) {
                            t = 0;
                        }
                    }
                }
                s.sijeceno = 1;

                if (t) {
                    s.najjaca = karta;
                    s.sljedeci_na_redu = s.na_redu;
                }
            }

            /* ako je slabija nema jacu */
            if (!s.sijeceno) {
                if (boja == prva_boja && !jaca(s.najjaca, karta, boja == s.adut)) {
                    s.najjaca = karta;
                    s.sljedeci_na_redu = s.na_redu;
                }
            }

            s.na_redu = (s.na_redu + 1)%4;
        }
        izbroji_stih(&s);
    }
    bod[prva_karta] += s.bodovi[0];
    wins[prva_karta] += s.bodovi[0] > s.bodovi[1];
    odigrano[prva_karta]++;
}

int izaberi_kartu(struct bela_stanje *s) {
    int karta = 0;
    moze_se_bacit(s, NULL);

    for (int i = 0; i < 8; ++i) {
        wins[i] = 0;
        bod[i] = 0;
        odigrano[i] = 0;
    }
    for (int i = 0; i < konfiguracija; ++i) {
        struct bela_stanje stanje = podijeli_karte(s);
        int karte[4][8];
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 8; ++k) {
                karte[j][k] = -8;
            }
        }

        int br_karata[4] = {0};
        for (int j = 0; j < 32; ++j) {
            /* prvi mora bit po redu kak je unesen */
            for (int k = 1; k < 4; ++k) {
                if (stanje.karte[k][j] == ima) {
                    karte[k][br_karata[k]++] = j;
                    break;
                }
            }
        }
        for (int j = 0; j < 8; ++j) {
            karte[0][j] = stanje.moje_karte[j];
        }

        int karte2[4][8];
        for (int j = 0; j < igara; ++j) {
            memcpy(karte2, karte, 4*8*sizeof(int));

            odigraj_partiju(stanje, karte2);
        }
        render(&stanje);
    }
    int najbolja = 0;
    double najbolja_win = 0;
    double najbolja_bod = 0;
    double najbolja_odigrano = 1;
    for (int i = 0; i < 8; ++i) {
        if (odigrano[i]) {
            printf("[%d]: avg bod: %.1f, win rate: %.1f%%\n",
                   i, bod[i]/odigrano[i], wins[i]*100/odigrano[i]);
            if (bod[i]/odigrano[i] > najbolja_bod/najbolja_odigrano) {
                najbolja = i;
                najbolja_win = wins[i];
                najbolja_bod = bod[i];
                najbolja_odigrano = odigrano[i];
            }
        }
    }
    karta = s->moje_karte[najbolja];
    s->moje_karte[najbolja] = -8;
    return karta;
}
