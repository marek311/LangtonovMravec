#include <ctime>
#include "Simulacia.h"

int main() {

    std::srand(std::time(nullptr));

    Simulacia s;
    s.simuluj(10,10,5,20,0,2);
}