#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "core.h"
#include "rnd.h"
#include "start.h"
#include "bela.h"
#include "render.h"
#include "ai.h"
#include "popravi.h"

int main(void) {
    rnd_init();
    render_init();
    struct bela_stanje s = start();
    render(&s);
    int karta;

for (s.runda = 0; s.runda < 8; ++s.runda) {
    s.sijeceno = 0;
    s.baceno = 0;
    s.prvi = s.sljedeci_na_redu;
    s.najjaca = -1;
    s.na_redu = s.prvi;
    for (int i = 0; i < 4; ++i) s.bacili[i] = 0;

    for (int i = 0; i < 4; ++i) {
        s.bacili[s.na_redu] = 1;
        render(&s);

        if (s.na_redu == 0) {
            clock_t start = clock();
            karta = izaberi_kartu(&s);
            printf("trebalo vremena: %f\n", ((double)(clock()-start))/CLOCKS_PER_SEC);
            printf("izabrano:\n");
            printaj_kartu(karta);
            printf("\n");
            sleep(1);
            render(&s);
        }
        else {
            printf("karta koju je bacio igrac %d: ", s.na_redu);
            karta = ucitaj_kartu();
        }

        int boja = karta/8;
        s.stih[i] = karta;
        int prva_boja = s.stih[0]/8;
        if (s.baceno == 0) {
            s.sljedeci_na_redu = s.na_redu;
            s.najjaca = karta;
        }
        for (int j = 0; j < 4; ++j)
            s.karte[j][karta] = nema;

        /* odavdje ne razumjem bas sto se dogada ali mislim da radi */

        // @TODO: sto ako je prva
        if (boja != prva_boja && boja != s.adut) {
            for (int j = s.adut*8; j < s.adut*8+8; ++j)
                s.karte[s.na_redu][j] = nema;
            for (int j = prva_boja*8; j < prva_boja*8+8; ++j)
                s.karte[s.na_redu][j] = nema;
            goto end;
        }

        if ((prva_boja != s.adut) && boja == s.adut) {
            int t = 1;
            if (s.sijeceno) {
                for (int j = 0; j < s.baceno; ++j) {
                    if (s.stih[j]/8 == s.adut && jaca(s.stih[j], karta, 1)) {
                        t = 0;
                        for (int k = 0; k < 8; ++k) {
                            if (jaca(s.adut*8+k, s.stih[j], 1)) {
                                s.karte[s.na_redu][s.adut*8+k] = nema;
                            }
                        }
                    }
                }
            }
            s.sijeceno = 1;
            for (int j = prva_boja*8; j < prva_boja*8+8; ++j)
                s.karte[s.na_redu][j] = nema;

            if (t) {
                s.najjaca = karta;
                s.sljedeci_na_redu = s.na_redu;
            }
        }
        
        /* ako je slabija nema jacu */
        if (!s.sijeceno) {
            if (boja == prva_boja && jaca(s.najjaca, karta, boja == s.adut)) {
                for (int k = 0; k < 8; ++k) {
                    if (jaca(prva_boja*8+k, s.najjaca, boja == s.adut)) {
                        s.karte[s.na_redu][prva_boja*8+k] = nema;
                    }
                }
            }
            else {
                s.najjaca = karta;
                s.sljedeci_na_redu = s.na_redu;
            }
        }

    end:
        popravi(&s);
        s.na_redu = (s.na_redu + 1)%4;
        s.baceno++;
        render(&s);
    }
    izbroji_stih(&s);
}
    printf("bodovi: %d vs %d\n", s.bodovi[0], s.bodovi[1]);
    render_deinit();
}
