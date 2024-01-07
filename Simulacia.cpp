#include "Simulacia.h"

void Simulacia::nacitajAkaPlocha() {
    int randomOrManualOrFile;
    std::cout << "Zadajte cislo: \n";
    std::cout << "0:RANDOM \n";
    std::cout << "1:MANUAL \n";
    std::cout << "2:FILE \n";
    std::cin >> randomOrManualOrFile;
    inicializujPlochu(&plocha, randomOrManualOrFile);
}

void Simulacia::pridajMravca() {
    int startx = std::rand() % plocha.sirka;
    int starty = std::rand() % plocha.vyska;
    Mravec mravecNovy = createMravec(startx, starty);
    zoznamMravcov.push_back(mravecNovy);
}

void Simulacia::nacitajMravcov() {
    int numOfAnts;
    std::cout << "Zadajte pocet mravcov v simulacii:";
    std::cin >> numOfAnts;
    for (int i = 0; i < numOfAnts; ++i) pridajMravca();
}

void Simulacia::inicializuj() {
    nacitajAkaPlocha();
    nacitajMravcov();
}

int Simulacia::nacitajPocetKrokov() {
    int numSteps;
    std::cout << "Zadajte pocet krokov:";
    std::cin >> numSteps;
    return numSteps;
}

int Simulacia::nacitajLogiku() {
    int logika;
    std::cout << "Zadajte logiku: \n";
    std::cout << "0:PRIAMA \n";
    std::cout << "1:INVERZNA \n";
    std::cin >> logika;
    return logika;
}

int Simulacia::nacitajRiesenieKolizii() {
    int riesenieKolizii;
    std::cout << "Zadajte riesenie kolizii: \n";
    std::cout << "0:Mravec pri kolizii prestane existovat \n";
    std::cout << "1:Mravec sa pri kolizii zacne spravat podla opacnej logiky \n";
    std::cin >> riesenieKolizii;
    return riesenieKolizii;
}

void Simulacia::vypisSmerMravca(int x, int y) {
    bool mravecFound = false;
    for (int j = 0; j < zoznamMravcov.size(); j++) {
        int wrappedX = (zoznamMravcov[j].polohaX + plocha.sirka) % plocha.sirka;
        int wrappedY = (zoznamMravcov[j].polohaY + plocha.vyska) % plocha.vyska;

        if (wrappedX == x && wrappedY == y && !zoznamMravcov[j].disabled) {
            vypisSmer(&zoznamMravcov[j]);
            mravecFound = true;
            break;
        }
    }
    if (!mravecFound) { std::cout << "."; }
}

void Simulacia::vypisHorizontalLine(int length) {
    for (int i = 0; i < (length * 2) - 1; i++) { std::cout << "-"; }
    std::cout << "\n";
}

void Simulacia::vypisPlochuMravcov() {
    std::cout << "\n";
    vypisHorizontalLine(plocha.sirka);

    for (int y = 0; y < plocha.vyska; y++) {
        for (int x = 0; x < plocha.sirka; x++) {
            if (x > 0) std::cout << "|";
            vypisSmerMravca(x, y);
        }
        std::cout << "\n";
    }

    vypisHorizontalLine(plocha.sirka);
    std::cout << "\n";
}

void Simulacia::checkAndDisableAntsAtSamePosition(int currentAntIndex, int x, int y) {

    for (int k = 0; k < zoznamMravcov.size(); ++k) {
        if (k != currentAntIndex && !zoznamMravcov[k].disabled) {
            int wrappedX = (zoznamMravcov[k].polohaX + plocha.sirka) % plocha.sirka;
            int wrappedY = (zoznamMravcov[k].polohaY + plocha.vyska) % plocha.vyska;

            if (wrappedX == x && wrappedY == y) {
                zoznamMravcov[currentAntIndex].disabled = (true);
            }
        }
    }
}

void Simulacia::checkAndReverseAntsAtSamePosition(int currentAntIndex, int x, int y) {

    for (int k = 0; k < zoznamMravcov.size(); ++k) {
        if (k != currentAntIndex && !zoznamMravcov[k].reverseLogic) {
            int wrappedX = (zoznamMravcov[k].polohaX + plocha.sirka) % plocha.sirka;
            int wrappedY = (zoznamMravcov[k].polohaY + plocha.vyska) % plocha.vyska;
            if (wrappedX == x && wrappedY == y) {
                setReverseLogic(&zoznamMravcov[currentAntIndex], zoznamMravcov[currentAntIndex].reverseLogic % 2);
            }
        }
    }
}

void Simulacia::otocMravca(int logika, int farbaPola, int indexMravca) {
    if (logika == 0) {
        if (farbaPola == 0)
            otocVpravo(&zoznamMravcov[indexMravca]);
        if (farbaPola == 1)
            otocVlavo(&zoznamMravcov[indexMravca]);
    } else if (logika == 1) {
        if (farbaPola == 0)
            otocVlavo(&zoznamMravcov[indexMravca]);
        if (farbaPola == 1)
            otocVpravo(&zoznamMravcov[indexMravca]);
    }
}

void Simulacia::simulujKrok(int j, int logika, int riesenieKolizii) {
    int mravecX = zoznamMravcov[j].polohaX;
    int mravecY = zoznamMravcov[j].polohaY;
    int index = mravecY * plocha.sirka + mravecX;
    const Pole& pole = getPoleOnIndex(&plocha,index);
    int color = getFarba(&pole);
    if(riesenieKolizii == 0) checkAndDisableAntsAtSamePosition(j, mravecX, mravecY);
    if(riesenieKolizii == 1) checkAndReverseAntsAtSamePosition(j, mravecX, mravecY);
    otocMravca(logika, color, j);
    zmenFarbaOnIndex(&plocha, index);
    posunVpred(&zoznamMravcov[j]);
    setPolohaX(&zoznamMravcov[j], (getPolohaX(&zoznamMravcov[j]) + plocha.sirka) % plocha.sirka);
    setPolohaY(&zoznamMravcov[j], (getPolohaY(&zoznamMravcov[j]) + plocha.vyska) % plocha.vyska);
    //vypis(&zoznamMravcov[j]);
}

bool Simulacia::isAntOnIndex(int index) {

    int width = plocha.sirka;
    int height = plocha.vyska;
    int x = index % width;
    int y = index / width;
    for (int j = 0; j < zoznamMravcov.size(); ++j) {
        int wrappedX = (getPolohaX(&zoznamMravcov[j]) + width) % width;
        int wrappedY = (getPolohaY(&zoznamMravcov[j]) + height) % height;

        if (wrappedX == x && wrappedY == y && !zoznamMravcov[j].disabled) {
            return true;
        }
    }
    return false;
}

void Simulacia::simuluj() {
    inicializuj();
    int pocetKrokov = nacitajPocetKrokov();
    int logika = nacitajLogiku();
    int riesenieKolizii = nacitajRiesenieKolizii();
    vypisPlochu(&plocha);
    vypisPlochuMravcov();

    for (int i = 0; i < pocetKrokov; ++i) {
        for (int j = 0; j < zoznamMravcov.size(); ++j) {

            if(riesenieKolizii == 0) {
                if (!zoznamMravcov[j].disabled) {
                    simulujKrok(j, logika, riesenieKolizii);
                }
            }
            if(riesenieKolizii == 1) {
                if (!zoznamMravcov[j].reverseLogic) {
                    simulujKrok(j, logika, riesenieKolizii);
                }
                if (zoznamMravcov[j].reverseLogic) {
                    int opacnaLogika = (logika + 1) % 2;
                    simulujKrok(j, opacnaLogika, riesenieKolizii);
                }
            }
        }
        std::cout << "\n" << "\n";
        std::cout << "KROK: " << i << "\n";

        vypisPlochu(&plocha);
        vypisPlochuMravcov();
        std::cout << "\n";
    }
    zrusPlochu(&plocha);
}