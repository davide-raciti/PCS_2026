#pragma once
#include <vector>
#include <string> 
#include <iostream>

// funzione is_sorted()
template<typename T>
bool is_sorted(const std::vector<T>& vec) {
    // vettore di lunghezza zero : ordinato per definizione
    if (vec.size() == 0)  {
        return true;
    }

    // vettore di lunghezza > 0 : ciclo for
    for (size_t i = 0; i < vec.size() - 1; i++) {
        if (vec[i] > vec[i+1]) {
            return false;
        }
    }
    return true;
}

// funzione bubble-sort
template<typename T>
void bubblesort(std::vector<T>& vec) {

    if (vec.size() <= 1) {
        return;
    }

    for (size_t i = 0; i < vec.size() - 1; i++) {
        for (size_t j = vec.size() - 1; j > i; j--) {
            if (vec[j] < vec[j - 1]) {
                T temp = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = temp;
            }
        }
    }
}

// funzione insertion-sort 
template<typename T>
void insertionsort(std::vector<T>& vec) {

    if (vec.size() <= 1) {
        return;
    }

    for (size_t j = 1; j < vec.size(); j++) {
        T key = vec[j];
        int i = j - 1;
        while (i >= 0 && vec[i] > key) {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}

// funzione selection-sort
template<typename T>
void selectionsort(std::vector<T>& vec) {

    if (vec.size() <= 1) {
        return;
    }

    for (size_t i = 0; i < vec.size() - 1; i++) {
        size_t min = i;
        for (size_t j = i + 1; j < vec.size(); j++) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }
        T temp = vec[i];
        vec[i] = vec[min];
        vec[min] = temp;
    }
}