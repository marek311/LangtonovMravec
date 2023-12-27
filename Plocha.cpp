#include "Plocha.h"

Plocha::Plocha(int sirkaPlochy, int vyskaPlochy) {

    sirka = sirkaPlochy;
    vyska = vyskaPlochy;
    int pocetPoli = sirka * vyska;
    for(int i = 0; i < pocetPoli; i++) {
        int cislo = 1;//std::rand() % 2;
        Pole vytvaranePole(cislo);
        plocha.push_back(vytvaranePole);
    }
}

void Plocha::vypisPlochu() {

    std::cout << "\n";
    for (int i = 0; i < (sirka * 2) - 1; i++) { std::cout << "-"; }
    std::cout << "\n";

    int pocetPoli = sirka * vyska;
    for(int i = 0; i < pocetPoli; i++) {

        //Koniec riadku -> novy riadok
        if (i > 0 && i % sirka == 0) std::cout << "\n";

        //Nie koniec riadku -> oddelovac
        if (i % sirka != 0) std::cout << "|";

        int cislo = plocha[i].getFarba();
        std::cout << cislo;
    }

    std::cout << "\n";
    for (int i = 0; i < (sirka * 2) - 1; i++) { std::cout << "-"; }
}

int Plocha::getSirka() const {
    return sirka;
}

void Plocha::setSirka(int sirka) {
    Plocha::sirka = sirka;
}

int Plocha::getVyska() const {
    return vyska;
}

void Plocha::setVyska(int vyska) {
    Plocha::vyska = vyska;
}

Pole Plocha::getPoleOnIndex(int index) {
    return plocha[index];
}

void Plocha::zmenFarbaOnIndex(int index) {
    plocha[index].zmenFarba();
}