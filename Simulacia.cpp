#include "Simulacia.h"

void Simulacia::inicializuj() {
    nacitajAkaPlocha();
    readNumOfAntsAndInicializeAnts();
}

void Simulacia::pridajMravca() {
    int startx = std::rand() % plocha.getSirka();
    int starty = std::rand() % plocha.getVyska();
    Mravec mravecNovy(startx, starty);
    zoznamMravcov.push_back(mravecNovy);
}

void Simulacia::vypisPlochuMravcov() {

    std::cout << "\n";
    vypisHorizontalLine(plocha.getSirka());

    for (int y = 0; y < plocha.getVyska(); y++) {

        for (int x = 0; x < plocha.getSirka(); x++) {
            if (x > 0) std::cout << "|";
            vypisAntDirection(x,y);
        }
        std::cout << "\n";
    }

    vypisHorizontalLine(plocha.getSirka());
    std::cout << "\n";
}

void Simulacia::simulujKrok(int j, int logika, int riesenieKolizii) {

    std::lock_guard<std::mutex> lock(mutex);

    int mravecX = zoznamMravcov[j].getPolohaX();
    int mravecY = zoznamMravcov[j].getPolohaY();

    int index = mravecY * plocha.getSirka() + mravecX;

    int color = plocha.getPoleOnIndex(index).getFarba();

    if(riesenieKolizii == 0) {
        checkAndDisableAntsAtSamePosition(j, mravecX, mravecY);
    }

    if(riesenieKolizii == 1) {
        checkAndReverseAntsAtSamePosition(j, mravecX, mravecY);
    }


    otocMravca(logika, color, j);
    plocha.zmenFarbaOnIndex(index);
    zoznamMravcov[j].posunVpred();

    zoznamMravcov[j].setPolohaX((zoznamMravcov[j].getPolohaX() + plocha.getSirka()) % plocha.getSirka());
    zoznamMravcov[j].setPolohaY((zoznamMravcov[j].getPolohaY() + plocha.getVyska()) % plocha.getVyska());
}

void Simulacia::simuluj() {
    //LOGIKA
    //0 = priama
    //1 = inverzna

    inicializuj();
    int pocetKrokov = nacitajPocetKrokov();
    int logika = nacitajLogiku();
    int riesenieKolizii = nacitajRiesenieKolizii();

    plocha.vypisPlochu();
    vypisPlochuMravcov();

    std::vector<std::thread> zoznamKrokovVlakna;

    for (int i = 0; i < pocetKrokov; ++i) {

        for (int j = 0; j < zoznamMravcov.size(); ++j) {

            //simulujKrok(j, logika);

            if(riesenieKolizii == 0) {

                if (!zoznamMravcov[j].isDisabled()) {
                    zoznamKrokovVlakna.emplace_back(&Simulacia::simulujKrok, this, j, logika, riesenieKolizii);
                }
            }

            if(riesenieKolizii == 1) {

                if (!zoznamMravcov[j].isReverseLogic()) {
                    zoznamKrokovVlakna.emplace_back(&Simulacia::simulujKrok, this, j, logika, riesenieKolizii);
                }

                if (zoznamMravcov[j].isReverseLogic()) {
                    int opacnaLogika = (logika + 1) % 2;
                    zoznamKrokovVlakna.emplace_back(&Simulacia::simulujKrok, this, j, opacnaLogika, riesenieKolizii);
                }
            }
        }

        std::cout << "\n" << "\n";
        std::cout << "KROK: " << i << "\n";

        for (auto &thread : zoznamKrokovVlakna) {
            thread.join();
        }
        zoznamKrokovVlakna.clear();

        plocha.vypisPlochu();
        vypisPlochuMravcov();

        std::cout << "\n";
    }
}

bool Simulacia::isAntOnIndex(int index) {

    int width = plocha.getSirka();
    int height = plocha.getVyska();

    int x = index % width;
    int y = index / width;

    for (int j = 0; j < zoznamMravcov.size(); ++j) {
        int wrappedX = (zoznamMravcov[j].getPolohaX() + width) % width;
        int wrappedY = (zoznamMravcov[j].getPolohaY() + height) % height;

        if (wrappedX == x && wrappedY == y && !zoznamMravcov[j].isDisabled()) {
            return true;
        }
    }
    return false;
}

void Simulacia::readNumOfAntsAndInicializeAnts() {

    int numOfAnts;

    std::cout << "Zadajte pocet mravcov v simulacii:";
    std::cin >> numOfAnts;

    for (int i = 0; i < numOfAnts; ++i) pridajMravca();
}

void Simulacia::otocMravca(int logika, int farbaPola, int indexMravca) {
    if (logika == 0) {
        if (farbaPola == 0)
            zoznamMravcov[indexMravca].otocVpravo();
        if (farbaPola == 1)
            zoznamMravcov[indexMravca].otocVlavo();
    } else if (logika == 1) {
        if (farbaPola == 0)
            zoznamMravcov[indexMravca].otocVlavo();
        if (farbaPola == 1)
            zoznamMravcov[indexMravca].otocVpravo();
    }
}

void Simulacia::vypisAntDirection(int x, int y) {

    bool mravecFound = false;

    for (int j = 0; j < zoznamMravcov.size(); j++) {
        int wrappedX = (zoznamMravcov[j].getPolohaX() + plocha.getSirka()) % plocha.getSirka();
        int wrappedY = (zoznamMravcov[j].getPolohaY() + plocha.getVyska()) % plocha.getVyska();

        if (wrappedX == x && wrappedY == y && !zoznamMravcov[j].isDisabled()) {
            zoznamMravcov[j].vypisSmer();
            mravecFound = true;
            break;
        }
    }

    if (!mravecFound) { std::cout << "."; }
}

void Simulacia::vypisHorizontalLine(int length) {
    for (int i = 0; i < (length * 2) - 1; i++) {
        std::cout << "-";
    }
    std::cout << "\n";
}

void Simulacia::checkAndDisableAntsAtSamePosition(int currentAntIndex, int x, int y) {

    for (int k = 0; k < zoznamMravcov.size(); ++k) {
        if (k != currentAntIndex && !zoznamMravcov[k].isDisabled()) {
            int wrappedX = (zoznamMravcov[k].getPolohaX() + plocha.getSirka()) % plocha.getSirka();
            int wrappedY = (zoznamMravcov[k].getPolohaY() + plocha.getVyska()) % plocha.getVyska();

            if (wrappedX == x && wrappedY == y) {
                zoznamMravcov[currentAntIndex].setDisabled(true);
            }
        }
    }
}

void Simulacia::checkAndReverseAntsAtSamePosition(int currentAntIndex, int x, int y) {

    for (int k = 0; k < zoznamMravcov.size(); ++k) {
        if (k != currentAntIndex && !zoznamMravcov[k].isReverseLogic()) {
            int wrappedX = (zoznamMravcov[k].getPolohaX() + plocha.getSirka()) % plocha.getSirka();
            int wrappedY = (zoznamMravcov[k].getPolohaY() + plocha.getVyska()) % plocha.getVyska();

            if (wrappedX == x && wrappedY == y) {
                zoznamMravcov[currentAntIndex].setReverseLogic(true);
            }
        }
    }
}

void Simulacia::nacitajAkaPlocha() {

    int randomOrManualOrFile;
    std::cout << "Zadajte cislo: \n";
    std::cout << "0:RANDOM \n";
    std::cout << "1:MANUAL \n";
    std::cout << "2:FILE \n";
    std::cin >> randomOrManualOrFile;

    plocha = Plocha(randomOrManualOrFile);
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
