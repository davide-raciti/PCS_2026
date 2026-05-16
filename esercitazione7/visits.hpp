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
#include <fstream>
#include <string>
#include <limits>
#include "graphs.hpp"
using namespace std;

// contenitore FIFO
template<typename T>
class fifo {
private:
    queue<T> q; // ricalca la struttura di queue
public:
    void put(const T& element) {
        q.push(element);
    }

    T get() {
        T result = q.front();
        q.pop();
        return result;
    }

    bool empty() {
        return q.empty();
    }
};

// contenitore LIFO
template<typename T>
class lifo {
private:
    stack<T> s; // ricalca la struttura di stack
public:
    void put(const T& element) {
        s.push(element);
    }

    T get() {
        T result = s.top();
        s.pop();
        return result;
    }

    bool empty() {
        return s.empty();
    }
};

// funzione graph_visit
// input: grafo di nodi T, sorgente T, struttura fifo/lifo
    // grazie al template Container, fa dfs/bfs se la struttura è lifo/fifo
    // (adapter)
template<typename T, typename Container>
undirected_graph<T> graph_visit(const undirected_graph<T>& G, const T& source, Container& container) {
    undirected_graph<T> tree;
    unordered_map<T, bool> reached; // sfrutto il fatto che non sono ammessi nodi duplicati
    // inizializzo il vettore reached, non ho ancora visitato alcun nodo
    for (const T& node : G.all_nodes()) {
        reached[node] = false;
    }
    // inserisco la sorgente nel contenitore e lo segno visitato
    container.put(source);
    reached[source] = true;

    while (!container.empty()) { // finchè il contenitore non è vuoto
        T u = container.get(); // estraggo il primo elemento del contenitore
        reached[u] = true; // lo segno visitato
        for (const T& w : G.neighbours(u)) { // per ogni vicino del nodo estratto
            if (!reached[w]) { // se non è visitato
                reached[w] = true; // lo segno visitato
                container.put(w); // lo inserisco nel contenitore
                undirected_edge<T> e(u, w); // dichiaro un nuovo arco
                tree.add_edge(e); // e lo inserisco nell'albero di ricerca
            }
        }
    }
    return tree;
}

// funzione per visualizzare l'albero di ricerca
// prende oggetto undirected_graph e costruisce in cartella un file .dot
    // del formato giusto per darlo in input a GraphViz 
template<typename T>
void export_to_dot(const undirected_graph<T>& G, const string& filename) {
    ofstream cout(filename);
    cout << "graph VisitTree {\n";
    for (const auto& edge : G.all_edges()) { // per ogni arco del grafo
        // lo stampo a video
        cout << "    " << edge.from() << " -- " << edge.to() << ";\n";
    }
    cout << "}\n";
}

// DFS ricorsivo
template<typename T>
void dfs_helper(const undirected_graph<T>& G, T u, unordered_map<T, bool>& visited, undirected_graph<T>& tree) {
    visited[u] = true; // segno visitato il nodo corrente
    for (const T& vicino : G.neighbours(u)) { // per ogni suo vicino
        if (!visited[vicino]) { // se ce n'è uno non visitato
            tree.add_edge(undirected_edge<T>(u, vicino)); // lo aggiungo all'albero
            dfs_helper(G, vicino, visited, tree); // riavvio la funzione sul vicino
        }
    }
}

template<typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& G, T& source) {
    undirected_graph<T> tree; // albero di ricerca
    unordered_map<T, bool> visited; // struttura per segnare le visite

    for (const T& node : G.all_nodes()) { // segno tutti non visitati
        visited[node] = false;
    }

    dfs_helper(G, source, visited, tree); // innesco la ricorsione
    return tree;
}

// funzione dijkstra
template<typename T>
undirected_graph<T> dijkstra(const undirected_graph<T>& G, T& source) {
    priority_queue<pair<double, T>> PQ; // coda con priorità per salvare i risultati delle iterazioni
    unordered_map<T, T> pred; // unordered map come struttura per i predecessori
    unordered_map<T, double> dist; //

    for (const T& node : G.all_nodes()) { // inizializzo le strutture predecesseori e distanze
        pred[node] = -1;
        dist[node] = numeric_limits<double>::infinity();
    }
    pred[source] = source; // il predecessore della sorgente è la sorgente stessa
    dist[source] = 0;

    PQ.push({-0.0, source}); // inserisco la sorgente nella priority queue
    
    while (!PQ.empty()) { 
        pair<double, T> current_element = PQ.top(); // leggo il primo elemento di PQ
        PQ.pop(); // lo elimino
        T u = current_element.second; // seleziono in nodo dalla tupla
        for (const T& node : G.neighbours(u)) { // per ogni nodo suo vicino
            if (dist[node] > dist[u] + G.get_weight(node, u)) { // condizione di if
                dist[node] = dist[u] + G.get_weight(node, u);
                pred[node] = u;
                PQ.push({-dist[node], node}); // distanza negativa perchè PQ ordina crescente
            }
        }
    }
    // funzione che legge il contenitore dei predecessori e restituisce l'albero di ricerca
    undirected_graph<T> tree;

    for (const auto& coppia : pred) {
        T nodo = coppia.first;
        T predecessore = coppia.second;

        if (predecessore != (T)-1 && nodo != source) { 
            // se -1 è stato raggiunto, se è source non ha precedenti
            double peso = G.get_weight(nodo, predecessore);
            undirected_edge<T> nuovo_arco(nodo, predecessore, peso);
            tree.add_edge(nuovo_arco); 
        }
    }
    return tree;
}