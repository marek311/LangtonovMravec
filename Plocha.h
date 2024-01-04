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
    void nacitajPlochuZoSuboru(const std::string& nazovSuboru);

public:
    Plocha() {}
    Plocha(int sirkaPlochy, int vyskaPlochy, int randomOrManual);
    Plocha(const std::string& nazovSuboru) { nacitajPlochuZoSuboru(nazovSuboru); }
    int getSirka() const;
    int getVyska() const;
    void setSirka(int sirka);
    void setVyska(int vyska);
    void vypisPlochu();
    Pole getPoleOnIndex(int index);
    void zmenFarbaOnIndex(int index);
};

#endif //LANGTONOVMRAVEC_PLOCHA_H