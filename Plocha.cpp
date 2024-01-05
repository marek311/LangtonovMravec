#include "Plocha.h"

void Plocha::vytvorPlochuRandom() {

    int sirkaNacitana, vyskaNacitana;

    std::cout << "Zadajte rozmery plochy ktora bude vygenerovana RANDOM:" << "\n";
    std::cout << "Sirka: ";
    std::cin >> sirkaNacitana;
    std::cout << "Vyska: ";
    std::cin >> vyskaNacitana;

    if(0 < sirkaNacitana && sirkaNacitana < 50) sirka = sirkaNacitana;
    if(0 < vyskaNacitana && vyskaNacitana < 50) vyska = vyskaNacitana;

    int pocetPoli = sirka * vyska;
    for(int i = 0; i < pocetPoli; i++) {
        int cislo = std::rand() % 2;
        Pole vytvaranePole(cislo);
        plocha.push_back(vytvaranePole);
    }
}

void Plocha::vytvorPlochuManual() {

    int sirkaNacitana, vyskaNacitana;

    std::cout << "Zadajte rozmery plochy ktora bude vygenerovana MANUALNE:" << "\n";
    std::cout << "Sirka: ";
    std::cin >> sirkaNacitana;
    std::cout << "Vyska: ";
    std::cin >> vyskaNacitana;

    if(0 < sirkaNacitana && sirkaNacitana < 50) sirka = sirkaNacitana;
    if(0 < vyskaNacitana && vyskaNacitana < 50) vyska = vyskaNacitana;

    int pocetPoli = sirka * vyska;
    for(int i = 0; i < pocetPoli; i++) {
        int cislo = 0;
        Pole vytvaranePole(cislo);
        plocha.push_back(vytvaranePole);
    }

    int stop, x, y;

    while (true) {

        std::cout << "Zadajte suradnice prvku ktory chcete nastavit na cierny:" << "\n";
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;

        if (0 <= x && x < sirka && 0 <= y && y < vyska) plocha[y * sirka + x].zmenFarba();

        std::cout << "Zadajte \n"
                     "0 - dalsie pole na cierne \n"
                     "1 - ukoncit zadavanie ciernych poli \n";

        std::cin >> stop;

        if (stop == 1) break;

        std::cin.clear();
    }
}

void Plocha::vytvorPlochuSubor() {

    std::string nazovSuboru;

    std::cout << "Zadajte absolutnu cestu k suboru z ktoreho chcete nacitat rozlozenie plochy:" << "\n";
    std::cout << "Absolutna cesta: ";
    std::cin >> nazovSuboru;
    std::cin.clear();

    std::cout << nazovSuboru << "\n";

    std::ifstream subor(nazovSuboru);
    if (!subor.is_open()) {
        std::cerr << "Chyba pri otvarani suboru!" << std::endl;
        return;
    }

    subor >> sirka >> vyska;
    plocha.clear();

    for (int i = 0; i < vyska; ++i) {
        for (int j = 0; j < sirka; ++j) {
            int cislo;
            subor >> cislo;
            Pole vytvaranePole(cislo);
            plocha.push_back(vytvaranePole);
        }
    }
    subor.close();
}

Plocha::Plocha(int sirkaPlochy, int vyskaPlochy, int randomOrManualOrFile) {
    sirka = sirkaPlochy;
    vyska = vyskaPlochy;

    //0 = random
    if(randomOrManualOrFile == 0) vytvorPlochuRandom();

    //1 = manual
    if(randomOrManualOrFile == 1) vytvorPlochuManual();

    //2 = file
    if(randomOrManualOrFile == 2) vytvorPlochuSubor();
}

int Plocha::getSirka() const {
    return sirka;
}

int Plocha::getVyska() const {
    return vyska;
}

void Plocha::setSirka(int sirka) {
    Plocha::sirka = sirka;
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

        int cislo = plocha[i].getFarba();
        std::cout << cislo;
    }

    std::cout << "\n";
    for (int i = 0; i < (sirka * 2) - 1; i++) { std::cout << "-"; }
}

Pole Plocha::getPoleOnIndex(int index) {
    if(index < plocha.size()) return plocha[index];
}

void Plocha::zmenFarbaOnIndex(int index) {
    if(index < plocha.size()) plocha[index].zmenFarba();
}