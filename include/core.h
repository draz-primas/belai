#ifndef BELA_CORE123
#define BELA_CORE123

// enum boja {nista, zir, srce, list, zvono};
enum znak {sedam, osam, devet, deset, decko, baba, kralj, as};
// struct bela_karta {
//     enum boja boja;
//     enum znak znak;
// };

/* karta je integer iz  [0, 32>
 * n%8 je znak          [0,  8>
 * n/8 je boja          [0,  4>
 */

static int bodovi[] = {
    [sedam] = 0,
    [osam] = 0,
    [devet] = 0,
    [deset] = 10,
    [decko] = 2,
    [baba] = 3,
    [kralj] = 4,
    [as] = 11,
};

static int bodovi_adut[] = {
    [sedam] = 0,
    [osam] = 0,
    [devet] = 14,
    [deset] = 10,
    [decko] = 20,
    [baba] = 3,
    [kralj] = 4,
    [as] = 11,
};

enum stanje {nema, ima, mozda, vjerojatno};
struct bela_stanje {
    /* 4 igraca po 32 karte */
    enum stanje karte[4][32];
    int stih[4];
    int prvi;
    int na_redu;
    int baceno; /* baceno = na_redu - prvi */
    int adut;
};

#endif
