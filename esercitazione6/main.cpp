#include "graphs.hpp"
#include <iostream>

using namespace std;
int main() {

    // inizializza un graph alcuni edge    
    undirected_graph<char> G;

    undirected_edge<char> e1('A', 'B');
    undirected_edge<char> e2('B', 'C');
    undirected_edge<char> e3('C', 'B'); // uguale a e2, non dovrebbe apparire
    undirected_edge<char> e4('D', 'C');
    undirected_edge<char> e5('E', 'F');

    // aggiungi qualche edge e poi per ogni edge del grafo: stampa
    G.add_edge(e1);
    G.add_edge(e2);
    G.add_edge(e3);
    G.add_edge(e4);
    G.add_edge(e5);

    cout << "Archi di G:" << endl;
    for (const undirected_edge<char>& edge : G.all_edges()) {
        cout << edge << endl;
    }
    cout << endl;

    // per ogni edge in neighbours(x): stampa
    cout << "Vicini di C:" << endl;
    for (const char& node : G.neighbours('C')) {
        cout << node << endl;
    }
    cout << endl;

    // per ogni nodo in all_nodes: stampa
    cout << "Nodi di G:" << endl;
    for (const char& node : G.all_nodes()) {
        cout << node << endl;
    }
    cout << endl;

    // verifichiamo le funzioni di numerazione archi
    cout << "Numerazione archi:" << endl;
    int num = G.edge_number(e3);
    cout << "Il numero dell'arco e1 è: " << num << endl;
    cout << "L'arco associato al numero " << num << " è: " << G.edge_at(num) << endl;
    cout << endl;

    // costruisci un altro grafo e fai la differenza
    // poi stampa gli edge del grafo differenza
    undirected_graph<char> H = G;
    undirected_edge<char> e6('C', 'Z');
    undirected_edge<char> e7('P', 'E');
    H.add_edge(e6);
    H.add_edge(e7);

    cout << "Differenza H - G:" << endl;
    undirected_graph<char> diff = H - G;
    for (const undirected_edge<char>& edge : diff.all_edges()) {
        cout << edge << endl;
    }
    cout << endl;

    return 0;
}