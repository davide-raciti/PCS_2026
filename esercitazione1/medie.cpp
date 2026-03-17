# include <iostream>
# include <fstream>
# include <string>
using namespace std;

int main(int argc, const char *argv[]) { // argc numero input, argv vettore input

    if (argc < 2)
    {
        cerr << "Non hai inserito il nome del file da leggere\n"; 
        return 1;
    }

    string filename = argv[1];
    ifstream ifs(filename); // legge il testo che gli stai passando

    if ( ifs.is_open() ) {
        string location;
        double temp1, temp2, temp3, temp4;
        while(ifs >> location >> temp1 >> temp2 >> temp3 >> temp4) {
            double media = (temp1 + temp2 + temp3 + temp4) / 4;
            cout << location << " " << media << "\n";
        }
    }
    else {
        cerr << "Errore nell'apertura del file\n";
        return 1;
    }

    return 0;
}