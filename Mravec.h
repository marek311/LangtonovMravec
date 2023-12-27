#include <iostream>

#ifndef LANGTONOVMRAVEC_MRAVEC_H
#define LANGTONOVMRAVEC_MRAVEC_H

class Mravec {

private:
    int polohaX;
    int polohaY;
    int smer; // 0 = hore | 1 = vpravo | 2 = dole | 3 = vľavo

public:
    Mravec() {}
    Mravec(int startX, int startY) : polohaX(startX), polohaY(startY), smer(0) {}
    int getPolohaX() const;
    int getPolohaY() const;
    int getSmer() const;
    void setPolohaX(int polohaX);
    void setPolohaY(int polohaY);
    void setSmer(int smer);
    void otocVpravo();
    void otocVlavo();
    void posunVpred();
    void vypis();
};

#endif //LANGTONOVMRAVEC_MRAVEC_H