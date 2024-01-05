#include "Simulacia.h"

void Simulacia::inicializuj(int randomOrManualOrFile) {

    plocha = Plocha(randomOrManualOrFile);
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
    for (int i = 0; i < (plocha.getSirka() * 2) - 1; i++) { std::cout << "-"; }
    std::cout << "\n";
    for (int y = 0; y < plocha.getVyska(); y++) {

        for (int x = 0; x < plocha.getSirka(); x++) {

            if (x > 0) std::cout << "|";

            vypisAntDirection(x,y);
        }
        std::cout << "\n";
    }
    for (int i = 0; i < (plocha.getVyska() * 2) - 1; i++) { std::cout << "-"; }
    std::cout << "\n";
}

void Simulacia::simulujKrok(int j, int logika) {

    std::lock_guard<std::mutex> lock(mutex);

    int mravecX = zoznamMravcov[j].getPolohaX();
    int mravecY = zoznamMravcov[j].getPolohaY();

    mravecX = (mravecX + plocha.getSirka()) % plocha.getSirka();
    mravecY = (mravecY + plocha.getVyska()) % plocha.getVyska();

    int index = mravecY * plocha.getSirka() + mravecX;

    int color = plocha.getPoleOnIndex(index).getFarba();

    if (!zoznamMravcov[j].isDisabled()) {

        for (int k = 0; k < zoznamMravcov.size(); ++k) {

            if (k != j && !zoznamMravcov[k].isDisabled()) {
                int wrappedX = (zoznamMravcov[k].getPolohaX() + plocha.getSirka()) % plocha.getSirka();
                int wrappedY = (zoznamMravcov[k].getPolohaY() + plocha.getVyska()) % plocha.getVyska();

                if (wrappedX == mravecX && wrappedY == mravecY) {
                    zoznamMravcov[j].setDisabled(true);
                }
            }
        }
    }

    otocMravca(logika, color, j);
    plocha.zmenFarbaOnIndex(index);
    zoznamMravcov[j].posunVpred();
}


void Simulacia::simuluj(int pocetKrokov, int logika, int randomOrManualOrFile) {

    //LOGIKA
    //0 = priama
    //1 = inverzna

    inicializuj(randomOrManualOrFile);
    plocha.vypisPlochu();
    vypisPlochuMravcov();

    std::vector<std::thread> zoznamKrokovVlakna;

    for (int i = 0; i < pocetKrokov; ++i) {

        for (int j = 0; j < zoznamMravcov.size(); ++j) {

            zoznamKrokovVlakna.emplace_back(&Simulacia::simulujKrok, this, j, logika);
            //simulujKrok(j, logika);
        }

        for (auto &thread : zoznamKrokovVlakna) {
            thread.join();
        }
        zoznamKrokovVlakna.clear();

        std::cout << "\n" << "\n";
        std::cout << "Krok: " << i;
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

    if (!mravecFound) {
        std::cout << ".";
    }

}