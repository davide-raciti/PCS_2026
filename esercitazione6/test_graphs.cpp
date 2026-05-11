#include "graphs.hpp"
#include <cstdlib>
using namespace std;

int main() {
    undirected_graph<char> G;
    undirected_edge<char> e1('A', 'B');
    undirected_edge<char> e2('B', 'A');
    undirected_edge<char> e3('A', 'C');

    G.add_edge(e1);
    G.add_edge(e2); // duplicato: gli archi sono indiretti, e2 = e1
    G.add_edge(e1); // duplicato

    // test di inserimento e dei duplicati
    if (G.all_edges().size() != 1 ||
        G.all_nodes().size() != 2 ||
        !G.all_nodes().contains('A') ||
        !G.all_nodes().contains('B')) {
            return EXIT_FAILURE;
        }

    if (G.all_edges().size() != 1) {
        return EXIT_FAILURE;
    }

    // test dei vicini
    G.add_edge(e3);
    set<char> vicini_A = G.neighbours('A');

    if (vicini_A.size() != 2 || 
        !vicini_A.contains('B') || 
        !vicini_A.contains('C')) {
        return EXIT_FAILURE;
    }

    // test della differenza
        // con sè stesso
    if ((G - G).all_edges().size() != 0) {
        return EXIT_FAILURE;
    }
        // con un altro grafo
    undirected_graph<char> H = G;
    undirected_edge<char> e4('C', 'D');
    H.add_edge(e4);
    undirected_graph<char> diff = H - G;
    if (diff.all_edges().size() != 1 ||
        !diff.all_nodes().contains('C') ||
        !diff.all_nodes().contains('D')) {
            return EXIT_FAILURE;
        }

    // test del mapping
    int id_e1 = G.edge_number(e1);
    if (!(G.edge_at(id_e1) == e1)) {
        return EXIT_FAILURE;
    }

    cout << "Tutti i test sono andati a buon fine!" << endl;
    return EXIT_SUCCESS;
}