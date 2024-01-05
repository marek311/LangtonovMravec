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
    void inicializuj(int randomOrManualOrFile);
    void pridajMravca();
    void vypisPlochuMravcov();
    void simulujKrok(int j, int logika);
    bool isAntOnIndex(int index);
    void readNumOfAntsAndInicializeAnts();
    void otocMravca(int logika, int farbaPola, int indexMravca);
    void vypisAntDirection(int x, int y);
    void vypisHorizontalLine(int length);
    void checkAndDisableAntsAtSamePosition(int currentAntIndex, int x, int y);

public:
    Simulacia() {}
    void simuluj(int pocetKrokov, int logika, int randomOrManualOrFile);
};

#endif //LANGTONOVMRAVEC_SIMULACIA_H