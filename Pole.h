#ifndef LANGTONOVMRAVEC_POLE_H
#define LANGTONOVMRAVEC_POLE_H

class Pole {
private:
    int farba; // 0 = biela | 1 = cierna

public:
    Pole(int farba);
    int getFarba() const;
    void zmenFarba();
};

#endif //LANGTONOVMRAVEC_POLE_H