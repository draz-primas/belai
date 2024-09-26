#include "render.h"
#include "core.h"

#ifdef RENDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#define WIDTH 1000
#define HEIGHT 500

// @TODO promijeni imena fajlova i makni ovo
const int prava_imena[] = { 0, 1, 2, 6, 3, 4, 5, 7 };

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

int w, h;

struct bela_karta_ren{
    SDL_Texture *tex;
    SDL_Rect rect;
};

struct bela_karta_ren karte_ren[32];

extern double wins[8];
extern double bod[8];
extern int odigrano[8];

void render_init(void) {
    int wid, hig;
    char path[64];

    SDL_VideoInit(NULL);
    win = SDL_CreateWindow("belai", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    for (int i=0; i<4; ++i) {
        for (int j=0; j<8; ++j) {
            sprintf(path, "data/%d-%d.webp", i, prava_imena[j]);
            karte_ren[i*8+j].tex = IMG_LoadTexture(ren, path);
            SDL_QueryTexture(karte_ren[i*8+j].tex, NULL, NULL, &wid, &hig);
            karte_ren[i*8+j].rect.w = wid*6;
            karte_ren[i*8+j].rect.h = hig*6;
            karte_ren[i*8+j].rect.x = j*wid*9;
            karte_ren[i*8+j].rect.y = i*hig*9;
        }
    }
    w = 100;
    h = 150;
}

void render_deinit(void) {
    for (int i = 0; i < 32; ++i) {
        SDL_DestroyTexture(karte_ren[i].tex);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_VideoQuit();
}

void render(struct bela_stanje *stanje) {
    (void)stanje;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return;
    } 

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    for (int i = 0; i < 8; ++i) {
        SDL_Rect rect = {
            .x = i*w,
            .y = 800,
            .w = w,
            .h = h,
        };
        if (stanje->moje_karte[i] >= 0 && stanje->moje_karte[i] < 32)
            SDL_RenderCopy(ren, karte_ren[stanje->moje_karte[i]].tex, NULL, &rect);
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 64);
        if (!stanje->moze[i]) SDL_RenderFillRect(ren, &rect);

        if (odigrano[i]) {
            int hh = bod[i]/odigrano[i]/162*700;
            rect = (SDL_Rect){
                .x = i*w,
                .y = 800-hh,
                .w = w,
                .h = hh,
            };
            SDL_SetRenderDrawColor(ren, 0, 128, 255, 255);
            SDL_RenderFillRect(ren, &rect);
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderDrawRect(ren, &rect);
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 32; ++j) {
            SDL_Rect rct = {
                .x = j*30,
                .y = i*30,
                .w = 30,
                .h = 30,
            };
            switch (stanje->karte[i][j]) {
                case nema:
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    break;
                case ima:
                    SDL_SetRenderDrawColor(ren, 255, 255, 128, 255);
                    break;
                case mozda:
                    SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
                    break;
                case vjerojatno:
                    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
                    break;
            }
            SDL_RenderFillRect(ren, &rct);
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_RenderDrawRect(ren, &rct);
        }
    }
    for (int i = 0; i < 4; ++i) {
        SDL_Rect r = {
            .x = 8*30*i  -1,
            .y = 0,
            .w = 2,
            .h = 5 + 4*30,
        };
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &r);
    }
    SDL_RenderPresent(ren);
}

/* ifndef RENDER */
#else
void render_init(void){}
void render(struct bela_stanje *stanje){(void)stanje;}
void render_deinit(void){}

#endif
