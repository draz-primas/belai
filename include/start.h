/** @file */

#ifndef START_H_2394284 /* brojevi za svaki slučaj */
#define START_H_2394284

/**
 * @brief Učitaj kartu sa standardnog ulaza.
 *
 * Ulazni format je isti kao ispis u [printaj_kartu](#printaj_kartu), a return kao ulaz u toj funkciji.
 *
 * @return učitana karta
 */
extern int ucitaj_kartu(void);

/* @TODO bolji opis */

/**
 * @brief Podešava početne vrijednosti
 *
 * Čita sa standardnog ulaza
 *
 * @return početno stanje partije
 */
extern struct bela_stanje start(void);

#endif
