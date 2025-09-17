# BelAI

### Ovo je umjetna "inteligencija" za igranje bele (nije dovršeno)

## Unošenje karata

Svaka karta je 2 znaka: 1. boja, 2. znak  

| chr | boja |
| --- | ---- |
| `T` | tref |
| `K` | karo |
| `P` | pik  |
| `H` | herc |

| chr | znak  |
| --- | ----- |
| `7` | 7     |
| `8` | 8     |
| `9` | 9     |
| `X` | 10    |
| `J` | dečko |
| `Q` | baba  |
| `K` | kralj |
| `A` | as    |

Primjer: `HQ` = herc baba  
Slova mogu biti mala ili velika.

## Kompajliranje

trebaš imat SDL2 i SDL2_image za grafiku (pokazuje šta radi grafički)

```bash
git clone https://github.com/draz-primas/belai.git
cd belai
make init
make clean release # bez grafike
make clean grafika release # ako zelis grafiku
./belai # pokreni
```

## Princip

### Brojanje karata

Ova "inteligencija" prati karte koje drugi igrači bacaju i pokušava pogoditi koje karte imaju ili nemaju.
Na primjer ako netko baci aduta na kartu koja nije adut, onda program zna da ta osoba nema tu boju.  
Točna pravila: (prava boja = boja prve karte, siječeno = netko prije je bacio aduta)  
 * Ako igrač nije bacio pravu boju niti aduta, onda nema tu boju niti aduta.
 * Ako je igrač bacio aduta, a prva karta nije adut, onda nema pravu boju.
 Ako je taj adut slabiji od najjačeg aduta koji je bačen u tom štihu, onda igrač nema niti adute jače od najjačeg.
 * Ako je igrač bacio pravu boju, ali je netko prije bacio jaču kartu u pravoj boji,
 onda igrač nema karte u toj boji koje su jače od najjače karte u štihu.

Osim ovih pravila koja su očita svakom igraču bele, program koristi i neke "naprednije" tehnike brojanja karata (ubuduće: drugi set pravila).
Za razumijevanje pravila treba znati da program ima 3 stanja za svaku kartu kod svakog igrača: (sigurno ima, sigurno nema, ne znam jel ju ima). (ubuduće: tablica stanja)
Na početku igre se za sve stavlja da se ne zna, a za sebe da ima one koje ima u ruci, a ostale nema.
 * Ako je karta bačena, nitko ju nema.
 * Ako netko ima neku kartu, onda ju ostali sigurno nemaju.
 * Ako 3 igrača sigurno nemaju neku kartu koja još nije bačena, onda ju ima onaj četvrti.
 * Ako je broj karata koje igrač ima u ruci jednak broju (karte koje znam da ima + karte za koje ne znam jel ih ima),
 onda igrač sigurno ima te karte za koje ne znam jel ih ima.
 * Ako je broj karata koje igrač ima u ruci jednak broju karata za koje znam da ih ima, onda nema niti jednu drugu kartu.

### Biranje najbolje karte

Trenutno ovaj program ne bira najbolju kartu, ali je dovoljno dobar. Algoritam ide ovako:
1. Podijeli nasumične karte ostalim igračima tako da nasumična karta koju dodjeljuješ bude u kategoriji (ne znam jel ju ima).
Koristi drugi set pravila nakon svake dodjele tako da na kraju svi imaju onoliko karata koliko trebaju i nema kontradikcija s početnim stanjem.
2. Do kraja partije bacaj nasumične karte i popravljaj tablicu stanja koristeći drugi set pravila. (zapamti prvu kartu koju si bacio)
3. Dodaj zbroj bodova u ukupni zbroj bodova koje si osvojio s tom kartom.
4. Ponovi korake 2-3 500 puta. (može i više)
5. Ponovi korake 1-4 500 puta. (može i više)

Na kraju se samo pogleda s kojom kartom se osvoji najviše bodova u prosjeku.

## TODO:
* [x] biranje najbolje karte
* [x] biranje najboljeg aduta
* [ ] koristi minimax umjesto nasumičnih igri
* [x] dovrši readme
* [ ] očisti kod

