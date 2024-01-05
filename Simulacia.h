#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include "Plocha.h"
#include "Mravec.h"

#ifndef LANGTONOVMRAVEC_SIMULACIA_H
#define LANGTONOVMRAVEC_SIMULACIA_H

class Simulacia {

private:
    std::mutex mutex;
    Plocha plocha;
    std::vector<Mravec> zoznamMravcov;
    void inicializuj(int pocetMravcov, int randomOrManualOrFile);
    void pridajMravca();
    void vypisPlochuMravcov();
    void simulujKrok(int j, int logika);
    bool isAntOnIndex(int index);

public:
    Simulacia() {}
    void simuluj(int pocetMravcov, int pocetKrokov, int logika, int randomOrManualOrFile);
};

#endif //LANGTONOVMRAVEC_SIMULACIA_H