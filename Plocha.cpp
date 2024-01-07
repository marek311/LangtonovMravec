#include "Plocha.h"

void Plocha::vytvorPlochuRandom() {

    int sirkaNacitana, vyskaNacitana;

    std::cout << "Zadajte rozmery plochy ktora bude vygenerovana RANDOM: \n";
    std::cout << "Sirka: \n" ;
    std::cin >> sirkaNacitana;
    std::cout << "Vyska: \n";
    std::cin >> vyskaNacitana;

    if(0 < sirkaNacitana && sirkaNacitana < 50) sirka = sirkaNacitana;
    if(0 < vyskaNacitana && vyskaNacitana < 50) vyska = vyskaNacitana;

    int pocetPoli = sirka * vyska;
    for(int i = 0; i < pocetPoli; i++) {
        int cislo = std::rand() % 2;
        struct Pole myPole;
        initPole(&myPole, cislo);
        plocha.push_back(myPole);
    }
}

void Plocha::vytvorPlochuManual() {

    int sirkaNacitana, vyskaNacitana;

    std::cout << "Zadajte rozmery plochy ktora bude vygenerovana MANUALNE: \n";
    std::cout << "Sirka: \n" ;
    std::cin >> sirkaNacitana;
    std::cout << "Vyska: \n";
    std::cin >> vyskaNacitana;

    if(0 < sirkaNacitana && sirkaNacitana < 50) sirka = sirkaNacitana;
    if(0 < vyskaNacitana && vyskaNacitana < 50) vyska = vyskaNacitana;

    int pocetPoli = sirka * vyska;
    for(int i = 0; i < pocetPoli; i++) {
        int cislo = 0;
        struct Pole myPole;
        initPole(&myPole, cislo);
        plocha.push_back(myPole);
    }

    int stop, x, y;

    while (true) {

        std::cout << "Zadajte suradnice prvku ktory chcete nastavit na cierny:" << "\n";
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;

        if (0 <= x && x < sirka && 0 <= y && y < vyska) zmenFarba(&plocha[y * sirka + x]);

        std::cout << "Zadajte \n"
                     "0 - dalsie pole na cierne \n"
                     "1 - ukoncit zadavanie ciernych poli \n";

        std::cin >> stop;

        if (stop == 1) break;

        std::cin.clear();
    }
}

Plocha::Plocha(int randomOrManualOrFile) {
    if(randomOrManualOrFile == 0) vytvorPlochuRandom();
    if(randomOrManualOrFile == 1) vytvorPlochuManual();
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

        int cislo = getFarba(&plocha[i]);
        std::cout << cislo;
    }

    std::cout << "\n";
    for (int i = 0; i < (sirka * 2) - 1; i++) { std::cout << "-"; }
}

Pole Plocha::getPoleOnIndex(int index) {
    if(index < plocha.size()) return plocha[index];
}

void Plocha::zmenFarbaOnIndex(int index) {
    if(index < plocha.size()) zmenFarba(&plocha[index]);
}