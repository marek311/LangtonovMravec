#include <vector>
#include <chrono>
#include <thread>
#include "Plocha.h"
#include "Mravec.h"

#ifndef LANGTONOVMRAVEC_SIMULACIA_H
#define LANGTONOVMRAVEC_SIMULACIA_H

class Simulacia {

private:
    Plocha plocha;
    std::vector<Mravec> zoznamMravcov;
    void inicializuj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int randomOrManual);
    void pridajMravca();
    void vypisPlochuMravcov();

public:
    Simulacia() {}
    void simuluj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int pocetKrokov, int logika, int randomOrManual);
};

#endif //LANGTONOVMRAVEC_SIMULACIA_H