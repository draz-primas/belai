#include <stdio.h>
#include <unistd.h>
#include "ai.h"
#include "core.h"
#include "bela.h"
#include "rnd.h"
#include "popravi.h"
#include "render.h"

extern int bacili[4];

struct prazne {
    int ptr[32];
    int n;
};

int izaberi_kartu(struct bela_stanje *s) {
    int karta = 0;
    moze_se_bacit(s);
    /* podijeli karte nasumicno:
     * kreni od igraca 1, daj mu random kartu, popravi tablicu
     * ponavljaj dok nema dovoljno karata
     * ponovi za svakog igraca
     */
    // @TODO: optimizacije mozda
    struct bela_stanje stanje = *s;
    struct prazne p;
    for (int igrac = 1; igrac < 4; ++igrac) {
        while (1) {
            p.n = 0;
            for (int i = 0; i < 32; ++i) {
                if (stanje.karte[igrac][i] == mozda) {
                    p.ptr[p.n] = i;
                    p.n++;
                }
            }

            if (p.n == 0) break;
            int karta = rnd_int()%p.n;
            printf("p.n: %d  karta: %d  igrac: %d\n", p.n, karta, igrac);
            stanje.karte[igrac][p.ptr[karta]] = ima;
            for (int i = 0; i < 4; ++i) {
                if (stanje.karte[i][p.ptr[karta]] == mozda) {
                    stanje.karte[i][p.ptr[karta]] = nema;
                }
            }
            popravi(&stanje);
            render(&stanje);
            sleep(1);
        }
    }
    render(&stanje);
    sleep(5);
    
loop:
    karta = rnd_int()%8;
    if (s->moze[karta]) {
        int ret = s->moje_karte[karta];
        s->moje_karte[karta] = -8;
        return ret;
    }
    goto loop;
}
