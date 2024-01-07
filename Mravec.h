// Mravec.h

#ifndef MRANVEC_H
#define MRANVEC_H

typedef struct {
    int polohaX;
    int polohaY;
    int smer; // 0 = hore | 1 = vpravo | 2 = dole | 3 = vľavo
    int disabled; // 0 or 1 (bool)
    int reverseLogic; // 0 or 1 (bool)
} Mravec;

Mravec createMravec(int startX, int startY);
int isDisabled(const Mravec *mravec);
void setDisabled(Mravec *mravec, int disabled);
int isReverseLogic(const Mravec *mravec);
void setReverseLogic(Mravec *mravec, int reverseLogic);
int getPolohaX(const Mravec *mravec);
void setPolohaX(Mravec *mravec, int polohaX);
int getPolohaY(const Mravec *mravec);
void setPolohaY(Mravec *mravec, int polohaY);
int getSmer(const Mravec *mravec);
void setSmer(Mravec *mravec, int smer);
void otocVpravo(Mravec *mravec);
void otocVlavo(Mravec *mravec);
void posunVpred(Mravec *mravec);
void vypis(const Mravec *mravec);
void vypisSmer(const Mravec *mravec);

#endif // MRANVEC_H
