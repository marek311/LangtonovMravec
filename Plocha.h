#include <vector>
#include <fstream>
#include <iostream>
#include "Pole.h"

#ifndef LANGTONOVMRAVEC_PLOCHA_H
#define LANGTONOVMRAVEC_PLOCHA_H

class Plocha {

private:
    int sirka;
    int vyska;
    std::vector<Pole> plocha;
    void vytvorPlochuRandom();
    void vytvorPlochuManual();
    void vytvorPlochuSubor();

public:
    Plocha() {}
    Plocha(int sirkaPlochy, int vyskaPlochy, int randomOrManualOrFile);
    int getSirka() const;
    int getVyska() const;
    int getVelkostPlochy() const { return plocha.size(); };
    void setSirka(int sirka);
    void setVyska(int vyska);
    void vypisPlochu();
    Pole getPoleOnIndex(int index);
    void zmenFarbaOnIndex(int index);
};

#endif //LANGTONOVMRAVEC_PLOCHA_H