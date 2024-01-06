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
    Plocha(int randomOrManualOrFile);
    int getSirka() const;
    void setSirka(int sirka);
    int getVyska() const;
    void setVyska(int vyska);
    int getVelkostPlochy() const { return this->plocha.size(); };
    void vypisPlochu();
    Pole getPoleOnIndex(int index);
    void zmenFarbaOnIndex(int index);
};

#endif //LANGTONOVMRAVEC_PLOCHA_H