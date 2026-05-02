#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "sorts.hpp"
#include "randfiller.h"

using namespace std;

int main() {
    randfiller rf;

    // TEST SUL VETTORE DI INTERI

    // genero 100 dimensioni casuali
    vector<int> dim(100);
    rf.fill(dim, 1, 5000);

    // genero 100 vettori di interi di dimensioni casuali
    // contenenti valori casuali
    for (int i = 0; i < 100; i++) {
        vector<int> vec(dim[i]);
        rf.fill(vec, -5000, 5000);
        selectionsort(vec);

        if (!is_sorted(vec)) {
            cout << "Errore: vettore di interi non ordinato!\n";
            return EXIT_FAILURE;
        }
    }

    // TEST SUL VETTORE DI STRINGHE

    vector<string> parole = {"genova", "torino", "roma", "milano", "padova", "palermo", "treviso", "pisa", "savona", "cosenza"};
    selectionsort(parole);

    if (!is_sorted(parole)) {
        cout << "Errore: Vettore di stringhe non ordinato!\n";
        return EXIT_FAILURE;
    }

    cout << "Selection-sort ha passato tutti i test!\n";
    return EXIT_SUCCESS;
}