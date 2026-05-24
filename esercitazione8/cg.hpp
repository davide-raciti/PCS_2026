#pragma once
#include <iostream>
#include <Eigen/Dense>

inline Eigen::VectorXd conjugate_gradient(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, double tol, unsigned int iter_max, unsigned int& iter_done) {
    // controlli preliminari sulle dimensioni degli input
    if (A.rows() != A.cols()) {
        std::cerr << "Errore: la matrice A deve essere quadrata.\n";
        return x0;
    }
    if (A.rows() != b.size() || A.rows() != x0.size()) {
        std::cerr << "Errore: dimensioni di A, b e x0 non compatibili.\n";
        return x0;
    }

    // inizializzazione del problema prendendo l'input
    Eigen::VectorXd x = x0; // soluzione iniziale
    Eigen::VectorXd res = b - A * x; // residuo
    double res_norm_0 = res.norm(); // res normalizzato, serve per la condizione di stop sulla tolleranza
    Eigen::VectorXd p = res; // prima direzione di discesa
    unsigned int it = 0; // contatore

    // ciclo while con le condizioni di stop del metodo: iterazioni oppure tolleranza
    while (it < iter_max && res.norm() > tol * res_norm_0) {
        Eigen::VectorXd Ap = A * p;
        const double alpha_k = p.dot(res) / p.dot(Ap); // lunghezza passo k-esimo
        x = x + alpha_k * p; // aggiornamento soluzione
        res = b - A * x; // ricalcolo del residuo
        const double beta_k = p.dot(A * res) / p.dot(Ap); // calcolo di beta k-esimo
        p = res - beta_k * p; // calcolo della successiva direzione di discesa
        it++; // aggiornamento contatore
    }

    // avviso di mancata convergenza per raggiungimento di numero max iterazioni
    if (it == iter_max) {
        std::cerr << "Attenzione: Raggiunto il numero massimo di iterazioni (" << iter_max << ") senza convergenza completa.\n";
    }

    iter_done = it;
    return x;
}