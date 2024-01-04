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
    void plochaRandom();
    void plochaManual();
    void plochaSubor(const std::string& nazovSuboru);

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
    int getVelkostPlochy() const { return plocha.size(); };
};

#endif //LANGTONOVMRAVEC_PLOCHA_H