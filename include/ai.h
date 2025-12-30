/** @file */

#ifndef BELA_AI
#define BELA_AI

#include "core.h"

/**
 * @brief Traži kartu koju je najbolje odigrati.
 * 
 * Podijeli nasumično karte drugim igračima s obzirom na to koje karte su do sad
 * bacili (prema tome se zne koje karte sigurno imaju ili nemaju). Sa podijeljenim
 * kartama odigra nasumične partije do kraja i gleda s kojom početnom kartom ima
 * najviše karte za pobijedu. Karte se dijele drugim igračima više puta.
 *
 * @param s stanje u trenutku biranja najbolje karte
 * @param biramaduta 1 ako se bira adut, 0 ako se bira karta
 * @param moram_zvat 1 ako mora zvat, 0 ako smije reći dalje
 * 
 * @return ako se bira karta, vraća integer 0-31, a ako se bira adut onda integer 0-3 ili -1 za dalje
 */
extern int izaberi_kartu(struct bela_stanje *s, int biramaduta, int moram_zvat);

#endif
