# BelAI

## Ovo je umjetna "inteligencija" za igranje bele (nije dovrseno)

## unosenje karata

svaka karta su 2 znaka: 1. boja 2. znak  
boja:  
T - tref  
K - karo  
P - pik  
H - herc  
znak:  
7 - 7  
8 - 8  
9 - 9  
X - 10  
J - decko  
Q - baba  
K - kralj  
A - as  
slova mogu biti mala ili velika

## kompajliranje

trebas imat SDL2 i SDL2_image za grafiku (pokazuje sta radi graficki)

```bash
git clone https://github.com/draz-primas/belai.git
cd belai
make init
make clean release # bez grafike
make clean grafika release # ako zelis grafiku
./belai # pokreni
```

## TODO:
* [x] biranje najbolje karte
* [x] biranje najboljeg aduta
* [ ] koristi minimax umjesto nasumicnih igri
* [ ] dovrsi readme
* [ ] ocisti kod
