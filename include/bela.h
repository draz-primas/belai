/** @file */

#ifndef BELA_H
#define BELA_H

#include "core.h"

/**
 * @brief Uspoređuje jačinu dvaju karata.
 * 
 * @param ova    prva karta
 * @param od_ove druga karta
 * @param adut   1 ako su karte u adutu, 0 ako nisu
 *
 * @return 1 ako je ova jača od od_ove, inače 0
 */
extern int jaca(int ova, int od_ove, int adut);

/**
 * @brief Gleda koje karte se smiju bacit s obzirom na štih.
 *
 * @param[in,out] s      Stanje partije. Mijenja se samo s->moze.
 * @param[in]     kartee Karte igrača koji gleda jel smije bacit. Ako je NULL, gleda se iz s->moje_karte.
 */
extern void moze_se_bacit(struct bela_stanje *s, int kartee[8]);

/**
 * @brief Broji bodove u štihu.
 *
 * Za zadnji štih automatski dodaje +10
 *
 * @param s[in,out] Stanje partije. Mijenja se s->bodovi.
 */
extern void izbroji_stih(struct bela_stanje *s);

/**
 * @brief Printa kartu.
 *
 * printa u obliku npr. TQ za tref baba
 *
 * @param karta integer 0-31
 */
extern void printaj_kartu(int karta);

#endif
