#include "Mravec.h"

bool Mravec::isDisabled() const {
    return disabled;
}

void Mravec::setDisabled(bool disabled) {
    Mravec::disabled = disabled;
}

bool Mravec::isReverseLogic() const {
    return reverseLogic;
}

void Mravec::setReverseLogic(bool reverseLogic) {
    Mravec::reverseLogic = reverseLogic;
}

int Mravec::getPolohaX() const {
    return polohaX;
}

void Mravec::setPolohaX(int polohaX) {
    Mravec::polohaX = polohaX;
}

int Mravec::getPolohaY() const {
    return polohaY;
}

void Mravec::setPolohaY(int polohaY) {
    Mravec::polohaY = polohaY;
}

int Mravec::getSmer() const {
    return smer;
}

void Mravec::setSmer(int smer) {
    Mravec::smer = smer;
}

void Mravec::otocVpravo() {
    smer = (smer + 1) % 4;
}

void Mravec::otocVlavo() {
    smer = (smer + 3) % 4;
}

void Mravec::posunVpred() {
    if (smer == 0) polohaY--;
    else if (smer == 1) polohaX++;
    else if (smer == 2) polohaY++;
    else if (smer == 3) polohaX--;
}

void Mravec::vypis() {
    std::cout << "\n"<< "Poloha X:" << polohaX << "\n";
    std::cout << "Poloha Y:" << polohaY << "\n";
    std::cout << "Smer:" << smer << "\n" << "\n";
}

void Mravec::vypisSmer() {
    if(smer == 0) std::cout << "^";
    if(smer == 1) std::cout << ">";
    if(smer == 2) std::cout << "v";
    if(smer == 3) std::cout << "<";
}