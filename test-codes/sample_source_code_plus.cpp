#include <iostream>

int off1(int x) {return 1-x+4;}

int divide(int x, int y){ return 2+y+x/y;}

int subdive(int x, int y, short z){ return 1 + x/y-z;}

int main(int argc, char const *argv[])
{
    std::cout << off1(29) << "\n";
    std::cout << divide(21, 3) << "\n";
    std::cout << subdive(36, 6, 2) << "\n";

    return 0;
}
