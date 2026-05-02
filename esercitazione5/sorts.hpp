#pragma once
#include <vector>
#include <string> 
#include <iostream>
#include "randfiller.h"

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

// funzione merge
template<typename T>
void merge(std::vector<T>& A, size_t p, size_t q, size_t r) {
    
    size_t n1 = q - p + 1;
    size_t n2 = r - q;
    std::vector<T> L(n1 + 1);
    std::vector<T> R(n2 + 1);

    for (size_t i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }

    for (size_t j = 0; j < n2; j++) {
        R[j] = A[q + j + 1];
    }

    if constexpr (std::is_same_v<T, std::string>) {
        L[n1] = std::string(1000,'\xff');
        R[n2] = std::string(1000,'\xff'); 
    } else {
        L[n1] = std::numeric_limits<T>::max(); 
        R[n2] =  std::numeric_limits<T>::max();
    }

    size_t i = 0;
    size_t j = 0;

    for (size_t k = p; k <= r; k++) {

        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

// funzione merge-sort
template<typename T>
void mergesort(std::vector<T>& vec, size_t p, size_t r) {
    
    if (p < r) {
        size_t q = (p + r) / 2;
        mergesort(vec, p, q);
        mergesort(vec, q + 1, r);
        merge(vec, p, q, r);
    }
}

// funzione partition
template<typename T>
int partition(std::vector<T>& A, int p, int r) {
    T x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            T temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    T temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

// funzione quick-sort
template<typename T>
void quicksort(std::vector<T>& A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

// ALGORITMO OTTIMIZZATO

// insertion-sort modificato per lavorare nei sottovettori di quick-sort
template<typename T>
void insertionsort_sottovettore(std::vector<T>& vec, int p, int r) {
    if (p >= r) return;
    for (int j = p + 1; j <= r; j++) {
        T key = vec[j];
        int i = j - 1;
        while (i >= p && vec[i] > key) {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}

template<typename T>
void quicksort_ottimizzato(std::vector<T>& A, int p, int r) {
    if (p < r) {
        if ((r - p + 1) <= 35) {
            insertionsort_sottovettore(A, p, r);
        } else {
            int q = partition(A, p, r);
            quicksort_ottimizzato(A, p, q - 1);
            quicksort_ottimizzato(A, q + 1, r);
        }
    }
}

