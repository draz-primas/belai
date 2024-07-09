#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "rnd.h"
#include "start.h"
#include "bela.h"
#include "render.h"
#include "ai.h"

int main(void) {
    int promjenjeno = 0;
    int karta;
    // @TODO: pretvori ovo u O(1) (makni)
    int bacili[4] = {0};
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
        promjenjeno = 0;
        /* situacija X+XX */
        for (int j = 0; j < 32; ++j) {
            int n = 0;
            int t = 0;
            for (int k = 0; k < 4; ++k) {
                n += s.karte[k][j] == nema;
                t += s.karte[k][j] == ima;
            }

            if (n != 3 || t) continue;
            printf("promjenjeno 1: %d\n", j);
            promjenjeno = 1;
            for (int k = 0; k < 4; ++k)
                if (s.karte[k][j] != nema) s.karte[k][j] = ima;
        }

        /* slicna stvar */
        for (int j = 0; j < 4; ++j) {
            int nima = 0;
            int nnema = 0;
            for (int k = 0; k < 32; ++k) {
                nima  += s.karte[j][k] == ima;
                nnema += s.karte[j][k] == nema;
            }

            int praznih = 32-nima-nnema;
            int ima_karata = 8-runda-bacili[j];
            /* mora imat i ostale onda */
            if (praznih && praznih + nima == ima_karata) {
                printf("promjenjeno 2, 1: %d\n", j);
                promjenjeno = 1;
                for (int k = 0; k < 32; ++k)
                    if (s.karte[j][k] == mozda)
                        s.karte[j][k] = ima;
            }
            /* onda nema nijednu od ostalih */
            if (nima == ima_karata && praznih != 0) {
                printf("promjenjeno 2, 2: %d\n", j);
                promjenjeno = 1;
                for (int k = 0; k < 32; ++k)
                    if (s.karte[j][k] == mozda)
                        s.karte[j][k] = nema;
            }
        }
        if (promjenjeno) goto end;

        s.na_redu = (s.na_redu + 1)%4;
        s.baceno++;
        render(&s);
    }
}
    render_deinit();
    rnd_deinit();
}
