#include "Pole.h"

Pole::Pole(int farba) : farba(farba) {}

int Pole::getFarba() const {
    return farba;
}

void Pole::zmenFarba() {
    Pole::farba = (farba + 1) % 2;
}