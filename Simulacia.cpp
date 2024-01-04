#include "Simulacia.h"

void Simulacia::inicializuj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int randomOrManualOrFile) {

    plocha = Plocha(sirkaPlochy, vyskaPlochy, randomOrManualOrFile);
    for (int i = 0; i < pocetMravcov; ++i) pridajMravca();
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

    int width = plocha.getSirka();
    int height = plocha.getVyska();

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {

            if (x > 0) std::cout << "|";

            bool mravecFound = false;
            for (int j = 0; j < zoznamMravcov.size(); j++) {

                int wrappedX = (zoznamMravcov[j].getPolohaX() + width) % width;
                int wrappedY = (zoznamMravcov[j].getPolohaY() + height) % height;

                if (wrappedX == x && wrappedY == y && !zoznamMravcov[j].isDisabled()) {

                    if(zoznamMravcov[j].getSmer() == 0) std::cout << "^";
                    if(zoznamMravcov[j].getSmer() == 1) std::cout << ">";
                    if(zoznamMravcov[j].getSmer() == 2) std::cout << "v";
                    if(zoznamMravcov[j].getSmer() == 3) std::cout << "<";

                    mravecFound = true;
                    break;
                }
            }
            if (!mravecFound) std::cout << ".";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < (height * 2) - 1; i++) { std::cout << "-"; }
    std::cout << "\n";
}

void Simulacia::simulujKrok(int j, int logika) {

    std::lock_guard<std::mutex> lock(mutex);

    int mravecX = zoznamMravcov[j].getPolohaX();
    int mravecY = zoznamMravcov[j].getPolohaY();

    int width = plocha.getSirka();
    int height = plocha.getVyska();

    mravecX = (mravecX + width) % width;
    mravecY = (mravecY + height) % height;

    int index = mravecY * width + mravecX;

    int color = plocha.getPoleOnIndex(index).getFarba();

    if (!zoznamMravcov[j].isDisabled()) {

        for (int k = 0; k < zoznamMravcov.size(); ++k) {

            if (k != j && !zoznamMravcov[k].isDisabled()) {
                int wrappedX = (zoznamMravcov[k].getPolohaX() + width) % width;
                int wrappedY = (zoznamMravcov[k].getPolohaY() + height) % height;

                if (wrappedX == mravecX && wrappedY == mravecY) {
                    zoznamMravcov[j].setDisabled(true);
                }
            }
        }
    }

    if (logika == 0) {
        if (color == 0)
            zoznamMravcov[j].otocVpravo();
        if (color == 1)
            zoznamMravcov[j].otocVlavo();
    } else if (logika == 1) {
        if (color == 0)
            zoznamMravcov[j].otocVlavo();
        if (color == 1)
            zoznamMravcov[j].otocVpravo();
    }

    plocha.zmenFarbaOnIndex(index);
    zoznamMravcov[j].posunVpred();
}


void Simulacia::simuluj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int pocetKrokov, int logika, int randomOrManualOrFile) {

    //LOGIKA
    //0 = priama
    //1 = inverzna

    inicializuj(sirkaPlochy, vyskaPlochy, pocetMravcov, randomOrManualOrFile);
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
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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