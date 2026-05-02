#include <iostream>
#include <vector>
#include <algorithm> 
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

using namespace std;


int main() {
    randfiller rf;
    timecounter tc;

    for (int D = 2; D <= 100 ; D++) {
        
        std::vector<std::vector<int>> contenitore(100, std::vector<int>(D));

        cout << "Dimensione : " << D << "\n";

        // bubble-sort
        for (int i = 0; i < 100; i++) {
            rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            bubblesort(contenitore[i]);
        }
        double tempo_totale_bub = tc.toc();
        double tempo_medio_bub = tempo_totale_bub / 100.0;
        cout << "Bubble-sort : " << tempo_medio_bub << "\n";

        // selection-sort
        for (int i = 0; i < 100; i++) {
            rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            selectionsort(contenitore[i]);
        }
        double tempo_totale_sel = tc.toc();
        double tempo_medio_sel = tempo_totale_sel / 100.0;
        cout << "Selection-sort : " << tempo_medio_sel << "\n";

        // insertion-sort
        for (int i = 0; i < 100; i++) {
            rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            insertionsort(contenitore[i]);
        }
        double tempo_totale_ins = tc.toc();
        double tempo_medio_ins = tempo_totale_ins / 100.0;
        cout << "Insertion-sort : " << tempo_medio_ins << "\n";

        // merge-sort
        for (int i = 0; i < 100; i++) {
            rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            mergesort(contenitore[i], 0, D - 1);
        }
        double tempo_totale_mer = tc.toc();
        double tempo_medio_mer = tempo_totale_mer / 100.0;
        cout << "Merge-sort : " << tempo_medio_mer << "\n";

        // quick-sort
        for (int i = 0; i < 100; i++) {
            rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            quicksort(contenitore[i], 0, D - 1);
        }
        double tempo_totale_qui = tc.toc();
        double tempo_medio_qui = tempo_totale_qui / 100.0;
        cout << "Quick-sort : " << tempo_medio_qui << "\n";

        // std::sort()
        for (int i = 0; i < 100; i++) {
        rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            std::sort(contenitore[i].begin(), contenitore[i].end());
        }
        double tempo_totale_sort = tc.toc();
        double tempo_medio_sort = tempo_totale_sort / 100.0;
        cout << "std::sort() : " << tempo_medio_sort << "\n";

        // ottimizzato
        for (int i = 0; i < 100; i++) {
        rf.fill(contenitore[i], 0, 100); 
        }
        tc.tic();
        for (int i = 0; i < 100; i++) {
            quicksort_ottimizzato(contenitore[i], 0, D - 1);
        }
        double tempo_totale_ott = tc.toc();
        double tempo_medio_ott = tempo_totale_ott / 100.0;
        cout << "Algoritmo ottimizzato : " << tempo_medio_ott << "\n";

        if (tempo_medio_qui < tempo_medio_ins) {
            cout << "Quick batte Ins!\n";
        }

        if ((tempo_medio_ott < tempo_medio_qui) && (tempo_medio_ott < tempo_medio_ins) && (tempo_medio_ott < tempo_medio_sort)) {
            cout << "Ott batte Quick, Ins e std:: !\n";
        }
        
        cout << "\n";

    }

    return 0;
}
