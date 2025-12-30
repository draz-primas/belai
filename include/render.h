/** @file */

#ifndef RENDER_H
#define RENDER_H

#include "core.h"

/** @brief inicijacija grafike */
extern void render_init(void);

/**
 * @brief Grafički prikaži stanje partije.
 *
 * @param stanje Stanje partije koja se prikazuje.
 */
extern void render(struct bela_stanje *stanje);

/** @brief čišćenje memorije */
extern void render_deinit(void);

#endif
