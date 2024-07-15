#ifndef BELA_CORE123
#define BELA_CORE123

enum znak {sedam, osam, devet, deset, decko, baba, kralj, as};

/* karta je integer iz  [0, 32>
 * n%8 je znak          [0,  8>
 * n/8 je boja          [0,  4>
 * boja je:
 *   0 - zir
 *   1 - zvono
 *   2 - srce
 *   3 - list
 */

static char znakovi[] = { 'T', 'K', 'H', 'P' };

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
    int moje_karte[8];
    int moze[8];
    int stih[4];
    int prvi;
    int na_redu;
    int sljedeci_na_redu;
    int baceno; /* baceno = na_redu - prvi */
    int adut;
    int sijeceno;
    int najjaca;
    int bodovi[2];
    int runda;
    int bacili[4];
};

#endif
