#include <ctime>
#include "Simulacia.h"

int main() {

    std::srand(std::time(nullptr));

    Simulacia s;
    s.simuluj();
    //TODO:ulozit do suboru svet
    //TODO:spravanie mravcov pri koliizi na 1 policku
}