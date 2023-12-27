#include <vector>
#include <iostream>
#include "Pole.h"

#ifndef LANGTONOVMRAVEC_PLOCHA_H
#define LANGTONOVMRAVEC_PLOCHA_H

class Plocha {

private:
    int sirka;
    int vyska;
    std::vector<Pole> plocha;

public:
    Plocha() {}
    Plocha(int sirkaPlochy, int vyskaPlochy, int randomOrManual);
    void plochaRandom();
    void plochaManual();
    void vypisPlochu();
    int getSirka() const;
    void setSirka(int sirka);
    int getVyska() const;
    void setVyska(int vyska);
    Pole getPoleOnIndex(int index);
    void zmenFarbaOnIndex(int index);
};

#endif //LANGTONOVMRAVEC_PLOCHA_H