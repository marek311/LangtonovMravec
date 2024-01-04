#include "Simulacia.h"

void Simulacia::inicializuj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int randomOrManual) {

    plocha = Plocha(sirkaPlochy,vyskaPlochy, randomOrManual);

    for (int i = 0; i < pocetMravcov; ++i)
        pridajMravca();

}

void Simulacia::pridajMravca() {

    //int startx = std::rand() % plocha.getSirka();
    //int starty = std::rand() % plocha.getVyska();

    //toto je iba kvoli tomu aby sa mravce nespawnli na kraji plochy:
    int startx = 2 + std::rand() % (plocha.getSirka() - 4);
    int starty = 2 + std::rand() % (plocha.getVyska() - 4);

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

            // Oddelovac
            if (x > 0) std::cout << "|";

            bool mravecFound = false;

            for (int j = 0; j < zoznamMravcov.size(); j++) {

                int wrappedX = (zoznamMravcov[j].getPolohaX() + width) % width;
                int wrappedY = (zoznamMravcov[j].getPolohaY() + height) % height;

                if (wrappedX == x && wrappedY == y) {
                    std::cout << "M";
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

    std::cout << "\n" << index;

    int color = plocha.getPoleOnIndex(index).getFarba();

    /*
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
     */

    plocha.zmenFarbaOnIndex(index);
    zoznamMravcov[j].posunVpred();

    //std::cout << j << "\n";
}


void Simulacia::simuluj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int pocetKrokov, int logika, int randomOrManual) {

    //LOGIKA
    //0 = priama
    //1 = inverzna

    inicializuj(sirkaPlochy, vyskaPlochy, pocetMravcov, randomOrManual);
    plocha.vypisPlochu();
    vypisPlochuMravcov();

    for (int i = 0; i < pocetKrokov; ++i) {

        //std::vector<std::thread> threads;

        for (int j = 0; j < zoznamMravcov.size(); ++j) {

            //threads.emplace_back(&Simulacia::simulujKrok, this, j, logika);
            simulujKrok(j, logika);
        }

        //for (auto &thread : threads) {
            //thread.join();
        //}

        std::cout << "\n" << "\n";
        std::cout << "Krok: " << i;
        plocha.vypisPlochu();
        vypisPlochuMravcov();

        std::cout << "\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}