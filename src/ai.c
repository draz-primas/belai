#include "ai.h"
#include "core.h"
#include "bela.h"
#include "rnd.h"

int izaberi_kartu(struct bela_stanje *s) {
    int karta = 0;
    moze_se_bacit(s);
loop:
    karta = rnd_int()%8;
    if (s->moze[karta]) {
        int ret = s->moje_karte[karta];
        s->moje_karte[karta] = -8;
        return ret;
    }
    goto loop;
}
