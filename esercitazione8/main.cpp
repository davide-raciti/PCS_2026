#include "cg.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

// test matrice 3x3 simmetrica definita positiva
bool test_spd_3x3() {
  Eigen::MatrixXd A(3, 3);
  A << 4, 1, 0,
       1, 3, 1,
       0, 1, 2;
    
  Eigen::VectorXd b(3);
  b << 1, 2, 3;
    
  Eigen::VectorXd x0 = Eigen::VectorXd::Zero(3);
  unsigned int iter_done = 0;
  Eigen::VectorXd x = conjugate_gradient(A, b, x0, 1e-7, 100, iter_done); // cg
  
  // controllo la precisione della soluzione trovata
  if ((b - A * x).norm() < 1e-5) { 
      cout << "Test 3x3 SPD: passato\n";
      return true;
  } else {
      cout << "Test 3x3 SPD: fallito\n";
      return false;
  }
}

// test matrice 10x10 tridiagonale (SVD, sparsa, ben condizionata)
bool test_tridiagonale_10x10() {
  int n = 10;
  Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n); // matrice di zeri, da riempire
    
  // popolo la diagonale principale e le sottodiagonali
  for (int i = 0; i < n; ++i) {
    A(i, i) = 2.0;
    if (i > 0)     A(i, i - 1) = -1.0;
    if (i < n - 1) A(i, i + 1) = -1.0;
  }
    
  Eigen::VectorXd b = Eigen::VectorXd::Ones(n);
  Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
  unsigned int iter_done = 0;
  Eigen::VectorXd x = conjugate_gradient(A, b, x0, 1e-6, 100, iter_done); // cg
  
  // controllo la precisione della soluzione trovata
  if ((b - A * x).norm() < 1e-5) {
    cout << "Test 10x10 tridiagonale: passato\n";
    return true;
  } else {
    cout << "Test 10x10 tridiagonale: fallito\n";
    return false;
  }
}

// test con matrice non SPD (ci aspettiamo che raggiunga il massimo di iterazioni)
bool test_non_spd() {
  Eigen::MatrixXd A(3, 3);
  A << 1, 10,  0,
       0,  1, 10,
       0,  0,  1;
          
  Eigen::VectorXd b(3);
  b << 1, 1, 1;
    
  Eigen::VectorXd x0 = Eigen::VectorXd::Zero(3);
  unsigned int iter_done = 0;
    
  // ci aspettiamo l'errore di raggiungimento massimo iterazioni come scritto in cg.hp
  Eigen::VectorXd x = conjugate_gradient(A, b, x0, 1e-8, 50, iter_done);
    
  if ((b - A * x).norm() >= 1e-5) {
      cout << "Test matrice non SPD: passato (non c'è stata la convergenza)\n";
      return true;
  } else {
      cout << "Test matrice non SPD: fallito\n";
      return false;
  }
}

// test per sistema di soluzione nota (1, 1, 1, 1, 1)
bool test_soluzione_nota_ones() {
    int n = 5;
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n);
    for (int i = 0; i < n; ++i) {
        A(i, i) = 4.0;
        if (i > 0)     A(i, i - 1) = -1.0;
        if (i < n - 1) A(i, i + 1) = -1.0;
    }

    // costruisco la soluzione esatta (1, 1, 1, 1, 1)
    Eigen::VectorXd x_esatta = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b = A * x_esatta; // prendo il termine noto associato alla sol
    
    Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
    unsigned int iter_done = 0;
    Eigen::VectorXd x = conjugate_gradient(A, b, x0, 1e-7, 100, iter_done);
    
    // calcoliamo errore sulla soluzione e residuo per fare una doppia verifica
    double errore_vero = (x - x_esatta).norm();
    double residuo = (b - A * x).norm();
    
    if (residuo < 1e-5 && errore_vero < 1e-5) {
        cout << "Test soluzione nota ones(5): passato\n";
        return true;
    } else {
        cout << "Test soluzione nota ones(5): fallito\n";
        return false;
    }
}

int main() {
    bool successo = true;
    if(!test_spd_3x3() || !test_tridiagonale_10x10() || !test_non_spd() || !test_soluzione_nota_ones()) {
        successo = false;
    }
    
    if(successo){
        cout << "\nTutti i test passati" << endl;
        return EXIT_SUCCESS;
    } else {
        cout << "\nAlmeno un test è fallito" << endl;
        return EXIT_FAILURE;
    }
  }