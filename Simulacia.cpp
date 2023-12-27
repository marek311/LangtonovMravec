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

    int pocetPoli = plocha.getSirka() * plocha.getVyska();
    for (int i = 0; i < pocetPoli; i++) {

        // Koniec riadku -> novy riadok
        if (i > 0 && i % plocha.getSirka() == 0) std::cout << "\n";

        // Nie koniec riadku -> oddelovac
        if (i % plocha.getSirka() != 0) std::cout << "|";

        bool mravecFound = false;

        for (int j = 0; j < zoznamMravcov.size(); j++) {

            if (zoznamMravcov[j].getPolohaX() == i % plocha.getVyska() &&
                zoznamMravcov[j].getPolohaY() == i / plocha.getSirka()) {
                std::cout << "M";
                mravecFound = true;
                break;
            }
        }
        if (!mravecFound) std::cout << ".";
    }

    std::cout << "\n";
    for (int i = 0; i < (plocha.getVyska() * 2) - 1; i++) { std::cout << "-"; }

    for (int i = 0; i < zoznamMravcov.size(); ++i) {
        //zoznamMravcov[i].vypis();
    }
}

void Simulacia::simuluj(int sirkaPlochy, int vyskaPlochy, int pocetMravcov, int pocetKrokov, int logika, int randomOrManual) {

    //LOGIKA
    //0 = priama
    //1 = inverzna

    inicializuj(sirkaPlochy, vyskaPlochy, pocetMravcov, randomOrManual);
    plocha.vypisPlochu();
    vypisPlochuMravcov();

    for (int i = 0; i < pocetKrokov; ++i) {

        for (int j = 0; j < zoznamMravcov.size(); ++j) {

            int mravecX = zoznamMravcov[j].getPolohaX();
            int mravecY = zoznamMravcov[j].getPolohaY();

            int index = mravecY * plocha.getSirka() + mravecX;

            int color = plocha.getPoleOnIndex(index).getFarba();

            //PRIAMA
            if(logika == 0) {

                //BIELA
                if (color == 0)
                    zoznamMravcov[j].otocVpravo();

                //CIERNA
                if (color == 1)
                    zoznamMravcov[j].otocVlavo();

            }

            //INVERZNA
            if(logika == 1) {

                //BIELA
                if (color == 0)
                    zoznamMravcov[j].otocVlavo();

                //CIERNA
                if (color == 1)
                    zoznamMravcov[j].otocVpravo();
            }

            plocha.zmenFarbaOnIndex(index);
            zoznamMravcov[j].posunVpred();
        }

        std::cout << "\n" << "\n";
        std::cout << "Krok: " << i;
        plocha.vypisPlochu();
        vypisPlochuMravcov();

        std::cout << "\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}