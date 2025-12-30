/** @file */

#ifndef POPRAVI
#define POPRAVI

#include "core.h"

/**
 * @brief popravlja tablicu stanja
 *
 * @param[in,out] s Stanje partije. Mijenja s->karte
 * @see bela_stanje::karte
 */
extern void popravi(struct bela_stanje *s);

#endif
