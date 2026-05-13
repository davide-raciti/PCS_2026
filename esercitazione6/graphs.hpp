#pragma once
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

// classe undirected_edge
template<typename N>
class undirected_edge {
private:
    N n1;
    N n2;
public:
    // costruttore user-defined
    undirected_edge(const N& a, const N& b) {
        if (a < b) {
            n1 = a;
            n2 = b;
        } else {
            n1 = b;
            n2 = a;
        }
    }

    // metodi per chiamare i valori dei nodi collegati dall'arco
    N from() const {return n1;}
    N to() const {return n2;}

    // operatore di confronto (<) 
    bool operator<(const undirected_edge& other) const {
        // confronto prima i nodi di partenza (i + piccoli)
        // se sono diversi vince il minore
        if (n1 != other.from()) {
            return n1 < other.from();
        }
        // se i nodi di partenza confronto i nodi di arrivo
        return n2 < other.to();
    }

    // operatore di uguaglianza (==)
    bool operator==(const undirected_edge& other) const {
        return n1 == other.from() && n2 == other.to();
    }
};

// operatore di stampa 
// va definito fuori dalla classe perchè deve prendere come elemento di sinistra os
template<typename N>
std::ostream& operator<<(std::ostream& os, const undirected_edge<N>& edge) {
    os << "(" << edge.from() << ") --> (" << edge.to() << ")";
    return os;
};

//////////////////////////////////////////////////////

// classe undirected_graph
using namespace std;
template<typename N>
class undirected_graph {
private:
    set<N> nodes;
    set<undirected_edge<N>> edges;
public:
    // costruttore di default
    undirected_graph() = default;

    // costruttore di copia
    undirected_graph(const undirected_graph& other) {
        nodes = other.nodes;
        edges = other.edges;
    }

    // metodo neighbours
    // input: Nodo, output: insieme dei Nodi collegati al Nodo in input
    set<N> neighbours(const N& nodo) const {
        set<N> result;
        for (const undirected_edge<N>& edge : edges) {
            if (edge.from() == nodo) {
                result.insert(edge.to());
            } else if (edge.to() == nodo) {
            result.insert(edge.from());
            }
        }
        return result;
    }

    // metodo add_edge
    // aggiunge un arco al grafo
    void add_edge(const undirected_edge<N>& edge) {
        // aggiorno i contenitori set
        edges.insert(edge);
        nodes.insert(edge.from());
        nodes.insert(edge.to());

    }

    // metodo all_edges
    // restituisce l'insieme degli archi del grafo
    set<undirected_edge<N>> all_edges() const {
        return edges;
    }

    // metodo all_nodes
    // restituisce l'insieme dei nodi del grafo
    set<N> all_nodes() const {
        return nodes;
    }

    // metodo edge_number
    // conta manualmente i passi fino all'arco cercato
        // !!! sfruttiamo che graph è un set di edges e quindi
        // gli archi al suo interno sono già ordinati dal più piccolo
        // al più grande secondo operator<
    int edge_number(const undirected_edge<N>& edge) const {
        int count = 0;
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if (*it == edge) {
                return count;
            }
            count++;
        }
        return -1; // se l'arco non esiste, impongo -1
    }

    // metodo edge_at
    // fa avanzare l'iteratore manualmente per 'num' volte
        // !!! sfruttiamo che graph è un set di edges e quindi
        // gli archi al suo interno sono già ordinati dal più piccolo
        // al più grande secondo operator<
    undirected_edge<N> edge_at(int num) const {
        auto it = edges.begin();
        for (int i = 0; i < num; ++i) {
            ++it; 
        }
        return *it; // dereferenzio l'iteratore per ottenere l'arco
    }

    // operatore di differenza tra grafi
        // !!! sfruttiamo che graph è un set di edges e quindi
        // gli archi al suo interno sono già ordinati dal più piccolo
        // al più grande secondo operator<
    undirected_graph<N> operator-(const undirected_graph<N>& other) const {
        undirected_graph<N> diff;
        // data un'operazione G1 - G2 = diff
        // itero tutti gli archi del grafo G1
        for(const auto& edge : edges) {
            // se l'arco non è presente in G2, lo aggiungo a diff
            if(other.edges.find(edge) == other.edges.end()) {
                diff.add_edge(edge);
            }
        }

        return diff;
    }
};