#ifndef LANGTONOVMRAVEC_PLOCHA_H
#define LANGTONOVMRAVEC_PLOCHA_H

#include "pole.h"

struct Plocha {
    int sirka;
    int vyska;
    struct Pole *plocha;
};

void vytvorPlochuRandom(struct Plocha *plocha);
void vytvorPlochuManual(struct Plocha *plocha);
void inicializujPlochu(struct Plocha *plocha, int randomOrManualOrFile);
void zrusPlochu(struct Plocha *plocha);
void vypisPlochu(const struct Plocha *plocha);
struct Pole getPoleOnIndex(const struct Plocha *plocha, int index);
void zmenFarbaOnIndex(struct Plocha *plocha, int index);

#endif // LANGTONOVMRAVEC_PLOCHA_H
