# include <iostream>
# include <array>
# include <cmath>
using namespace std;

int main()
{   
    // definisco l'array
    static const int N = 10;
    double arr[N] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

    // minimo e massimo
    double minimo = arr[0];
    double massimo = arr[0];

    for (int i=0; i<N; i++)  // ciclo for per massimo e minimo
    {
        minimo = min(arr[i], minimo);  // a ogni iterazione seleziona il minimo tra l'elemento corrente e il successivo
        massimo = max(arr[i], massimo);  // a ogni iterazione seleziona il massimo tra l'elemento corrente e il successivo
    }

    cout << "Il minimo è " << minimo << "\n";
    cout << "Il massimo è " << massimo << "\n";

    // media
    double media = 0.0;
    for (int i=0; i<N; i++) // ciclo for per la media
    {
        media += arr[i]/N;  // a ogni iterazione sommo il contributo dell'elemento corrente
    }

    cout << "La media è " << media << "\n";

    // deviazione standard
    double scarti_quadratici = 0.0;
    for (int i=0; i<N; i++)  // ciclo for per gli scarti quadratici
    {
        scarti_quadratici += pow(arr[i]-media,2);  // a ogni iterazione sommo il contributo dell'elemento corrente
    }
    double varianza = scarti_quadratici/N;  // definisco la varianza
    double deviazione_standard = sqrt(varianza);  // definisco la deviazione standard
    cout << "La deviazione standard è " << deviazione_standard << "\n";    
}