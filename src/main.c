#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "rnd.h"
#include "start.h"
#include "bela.h"
#include "render.h"
#include "ai.h"
#include "popravi.h"

int bacili[4] = {0};

int main(void) {
    int karta;
    // @TODO: pretvori ovo u O(1) (makni)
    rnd_init();
    render_init();
    struct bela_stanje s = start();
    render(&s);
for (int runda = 0; runda < 8; ++runda) {
    s.sijeceno = 0;
    s.baceno = 0;
    s.prvi = s.sljedeci_na_redu;
    s.najjaca = -1;
    s.na_redu = s.prvi;
    izbroji_stih(&s);
    for (int i = 0; i < 4; ++i) bacili[i] = 0;
    for (int i = 0; i < 4; ++i) {
        bacili[s.na_redu] = 1;
        render(&s);
        if (s.na_redu == 0) {
            karta = izaberi_kartu(&s);
            printf("izabrano: %d\n", karta);
            sleep(1);
            render(&s);
        }
        printf("karta koju je bacio igrac %d: ", s.na_redu);
        karta = ucitaj_kartu();
        int boja = karta/8;
        s.stih[i] = karta;
        int prva_boja = s.stih[0]/8;
        if (s.baceno == 0) {
            s.sljedeci_na_redu = s.na_redu;
            s.najjaca = karta;
        }
        for (int j = 0; j < 4; ++j)
            s.karte[j][karta] = nema;

        // @TODO: sto ako je prva
        if (boja != prva_boja && boja != s.adut) {
            for (int j = s.adut*8; j < s.adut*8+8; ++j)
                s.karte[s.na_redu][j] = nema;
            for (int j = prva_boja*8; j < prva_boja*8+8; ++j)
                s.karte[s.na_redu][j] = nema;
            printf("kriva boja\n");
            goto end;
        }

        if ((prva_boja != s.adut) && boja == s.adut) {
            int t = 1;
            if (s.sijeceno) {
                for (int j = 0; j < s.baceno; ++j) {
                    if (s.stih[j]/8 == s.adut && jaca(s.stih[j], karta, 1)) {
                        t = 0;
                        printf("sijece ali nije jaca: %d vs %d\n",
                               bodovi_adut[s.stih[j]%8], bodovi_adut[karta%8]);
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
                printf("sijece i sad je najjaca\n");
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
                printf("nema jacu\n");
            }
            else {
                printf("sad je najjaca\n");
                s.najjaca = karta;
                s.sljedeci_na_redu = s.na_redu;
            }
        }

    end:
        popravi(&s, runda);
        s.na_redu = (s.na_redu + 1)%4;
        s.baceno++;
        render(&s);
    }
}
    printf("bodovi: %d vs %d\n", s.bodovi[0], s.bodovi[1]);
    render_deinit();
    rnd_deinit();
}
