#pragma once
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

// classe undirected_edge
template<typename N>
class undirected_edge {
private:
    N n1;
    N n2;
    double peso; // inserito un valore per il peso del nodo per implementare dijkstra
public:
    // costruttore user-defined
    undirected_edge(const N& a, const N& b, double w = 1.0) {
        if (a < b) {
            n1 = a;
            n2 = b;
        } else {
            n1 = b;
            n2 = a;
        }

        peso = w; 
    }

    // metodi per chiamare i valori dei nodi collegati dall'arco e il peso
    N from() const {return n1;}
    N to() const {return n2;}
    double weight() const {return peso;}

    // operatore di confronto (<) 
    bool operator<(const undirected_edge& other) const {
        // confronto prima i nodi di partenza (i + piccoli)
        // se sono diversi vince il minore
        if (n1 != other.from()) {
            return n1 < other.from();
        }
        // se i nodi di partenza sono uguali confronto i nodi di arrivo
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
template<typename N>
class undirected_graph {
private:
    set<N> nodes; // insieme contenente i nodi
    set<undirected_edge<N>> edges; // insieme contenente gli archi
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
        set<N> result; // insieme di nodi da riempire
        for (const undirected_edge<N>& edge : edges) { // per ogni arco
            if (edge.from() == nodo) { // se esce dal nodo input
                result.insert(edge.to()); // inserisco il nodo in cui entra
            } else if (edge.to() == nodo) { // viceversa
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
        int count = 0; // dichiaro contatore numerico
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if (*it == edge) { // se l'iteratore punta all'arco input
                return count;  // restituisci il contatore
            }
            count++; // aggiorno il contatore
        }
        return -1; // se l'arco non esiste, impongo -1
    }

    // metodo edge_at
    // fa avanzare l'iteratore manualmente per 'num' volte
        // !!! sfruttiamo che graph è un set di edges e quindi
        // gli archi al suo interno sono già ordinati dal più piccolo
        // al più grande secondo operator<
    undirected_edge<N> edge_at(int num) const {
        auto it = edges.begin(); // dichiaro l'iteratore
        for (int i = 0; i < num; ++i) { 
            ++it; // aggiorno l'iteratore
        }
        return *it; // dereferenzio l'iteratore per ottenere l'arco
    }

    // operatore di differenza tra grafi
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

    // metodo get_weight
    // necessario per l'implementazione di dijkstra
    // input: due nodi del grafo
    // output: peso dell'arco (se i nodi sono nel grafo e se c'è un arco tra di loro)
    double get_weight(N u, N v) const {
        double peso = -1.0;
        N n1;
        N n2;
        // faccio in modo che il nodo più piccolo sia a sinistra
        if (u < v) {
            n1 = u;
            n2 = v;
        } else if (v < u) {
            n1 = v;
            n2 = u;
        } else {
            cerr << "Arco non valido, i nodi sono uguali!\n";
        }
        // cerco fra gli archi quello che unisce i nodi input
        for (const auto& edge : all_edges()) {
            if (edge.from() == n1 && edge.to() == n2) {
                peso = edge.weight(); // ne estraggo il peso
                break;
            }
        }
        
        return peso;
    }

};
