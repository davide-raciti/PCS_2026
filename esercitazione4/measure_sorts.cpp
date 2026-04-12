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

    for (int dim = 4; dim <= 8192; dim *= 2) {
        vector<int> vec_base(dim);
        rf.fill(vec_base, -5000, 5000);

        // bubblesort
        vector<int> v1 = vec_base;
        tc.tic();
        bubblesort(v1);
        double t_bub = tc.toc();

        // insertionsort
        vector<int> v2 = vec_base;
        tc.tic();
        insertionsort(v2);
        double t_ins = tc.toc();

        // selectionsort
        vector<int> v3 = vec_base;
        tc.tic();
        selectionsort(v3);
        double t_sel = tc.toc();

        // std::sort
        vector<int> v4 = vec_base;
        tc.tic();
        std::sort(v4.begin(), v4.end());
        double t_std = tc.toc();

        // Stampa i risultati in colonna
        cout << dim << "\t" << t_bub << "\t" << t_ins << "\t" << t_sel << "\t" << t_std << "\n";
    }

    return 0;
}