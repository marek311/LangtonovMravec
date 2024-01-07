#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include "Plocha.h"
#include "Mravec.h"

#ifndef LANGTONOVMRAVEC_SIMULACIA_H
#define LANGTONOVMRAVEC_SIMULACIA_H

class Simulacia {

private:
    std::mutex mutex;
    struct Plocha plocha;
    std::vector<Mravec> zoznamMravcov;

    void nacitajAkaPlocha();
    void pridajMravca();
    void nacitajMravcov();
    void inicializuj();
    int nacitajPocetKrokov();
    int nacitajLogiku();
    int nacitajRiesenieKolizii();
    void vypisSmerMravca(int x, int y);
    void vypisHorizontalLine(int length);
    void vypisPlochuMravcov();
    void checkAndDisableAntsAtSamePosition(int currentAntIndex, int x, int y);
    void checkAndReverseAntsAtSamePosition(int currentAntIndex, int x, int y);
    void otocMravca(int logika, int farbaPola, int indexMravca);
    void simulujKrok(int j, int logika, int riesenieKolizii);
    bool isAntOnIndex(int index);

public:
    Simulacia() {}
    void simuluj();
};

#endif //LANGTONOVMRAVEC_SIMULACIA_H