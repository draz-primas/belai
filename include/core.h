/** @file */

#ifndef BELA_CORE123
#define BELA_CORE123

/**
 * @brief Znak na karti za belu.
 * poredani su po redosljedu za zvanja
 */
enum znak {sedam, osam, devet, deset, decko, baba, kralj, as};

/* karta je integer iz  [0, 32>
 * n%8 je znak          [0,  8>
 * n/8 je boja          [0,  4>
 * boja je:
 *   0 - žir
 *   1 - zvono
 *   2 - srce
 *   3 - list
 */

/**
 * @brief Lista znakova na kartama za belu.
 *
 * znakovi[i] je char koji predstavlja tu boju, npr. znakovi[0] je T (tref).
 * U kodu se za tref koristi 0, karo 1 itd. Po redu: tref, karo, herc, pik.
 * U bela bojama: žir, zvono/bundeva, srce, list
 */
extern char znakovi[];

/**
 * @brief Koliko bodova donosi koja karta.
 *
 * bodovi[i] je broj bodova koji na kraju igre donosi ta karta ako nije u adutu, a
 * i je `enum znak`
 */
extern int bodovi[];

/**
 * @brief Broj bodova karte u adutu.
 * @see bodovi[]
 */
extern int bodovi_adut[];

/**
 * @brief stanje karte za nekog igrača
 *
 * Koristi se u praćenju karata drugih igrača (brojanju karata).
 */
enum stanje {
    nema,      /**< @brief igrač sigurno nema kartu */
    ima,       /**< @brief igrač sigurno ima kartu */
    mozda,     /**< @brief ne zna se ima li igrač kartu */
    vjerojatno /**< @brief Velika je šansa da igrač ima kartu, ali nije sigurno. Ovo se još ne koristi u kodu */
};

/**
 * @brief Sadrži sve informacije o stanju partije.
 */
struct bela_stanje {
    /* 4 igraca po 32 karte */
    enum stanje karte[4][32]; /**< @brief Stanje za svakog igrača za svaku kartu (4 igrača, 32 karte)
                                   @see stanje */
    int moje_karte[8];        /**< @brief Karte koje ai ima. */
    int moze[8];              /**< @brief koje karte se mogu bacit (koristi se za funkciju [moze_se_bacit](#moze_se_bacit())) */
    int stih[4];              /**< @brief karte na stolu */
    int prvi;                 /**< @brief indeks igrača koji je prvi na redu */
    int na_redu;              /**< @brief indeks igrača koji je na redu */
    int sljedeci_na_redu;     /**< @brief indeks igrača koji je sljedeći na redu */
    int baceno;               /**< @brief baceno = na_redu - prvi */
    int adut;                 /**< @brief Boja aduta.
                                   @see znakovi[] */
    int sijeceno;             /**< @brief 1 ako je bačen adut, a prva karta nije adut, inače 0 */
    int najjaca;              /**< @brief najjača karta, koristi se interno u nekim funkcijama */
    int bodovi[2];            /**< @brief broj bodova: [0]: mi (ai + netko), [1]: vi (druga 2 igrača) */
    int runda;                /**< @brief brojač za runde (1 runda = pokupljen 1 štih) */
    int bacili[4];            /**< @brief za svakog igrača prati je li bacio kartu u ovoj rundi */
};

#endif
