#include <iostream>
#include "rational.hpp"
#include <concepts>

int main()
{   int a,b,c,d;
    std:: cout << "Inserisci il numeratore e il denominatore separati da uno spazio: \n";
    if(!(std::cin >>a >>b))
    {
        std::cout << "Errore: non hai inserito degli interi!\n";
        return 1;
    }
    rational<int> r1(a,b);

    std:: cout << "Inserisci il numeratore e il denominatore separati da uno spazio: \n";
    if(!(std::cin >>c >>d))
    {
        std::cout << "Errore: non hai inserito degli interi!\n";
        return 1;
    }
    rational<int> r2(c,d);

    rational<int> ad=r1+r2;
    rational<int> sot=r1-r2;
    rational<int> molt=r1*r2;
    rational<int> div=r1/r2;
    std:: cout <<"\nStampo i due numeri razionali:\n"<< r1 << " " << r2
    <<"\n\nStampo tutte le operazioni: \n" << "La somma è: "<< ad << "\n"<< "La sottrazione è: "<< sot <<"\n" << "La moltiplicazione è: "<< molt << "\n" <<"La divisione è: "<< div << "\n";
    return 0;
}