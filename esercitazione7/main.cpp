#include "graphs.hpp"
#include "visits.hpp"
#include <iostream>

using namespace std;
int main() {
    // TEST graph_visit --------------------------
    undirected_graph<int> G;
    G.add_edge(undirected_edge<int>(1, 2));
    G.add_edge(undirected_edge<int>(1, 3));
    G.add_edge(undirected_edge<int>(1, 4));
    G.add_edge(undirected_edge<int>(1, 6));
    G.add_edge(undirected_edge<int>(2, 7));
    G.add_edge(undirected_edge<int>(2, 5));
    G.add_edge(undirected_edge<int>(2, 4));
    G.add_edge(undirected_edge<int>(3, 6));
    G.add_edge(undirected_edge<int>(4, 7));
    G.add_edge(undirected_edge<int>(4, 6));
    G.add_edge(undirected_edge<int>(5, 7));
    G.add_edge(undirected_edge<int>(6, 7));
    G.add_edge(undirected_edge<int>(6, 8));
    G.add_edge(undirected_edge<int>(7, 9));
    G.add_edge(undirected_edge<int>(8, 9));
    // albero DFS
    lifo<int> s_G;
    auto dfsG = graph_visit(G, 1, s_G);
    export_to_dot(dfsG, "dfs_G.dot");
    // albero BFS
    fifo<int> q_G;
    auto bfsG = graph_visit(G, 1, q_G);
    export_to_dot(bfsG, "bfs_G.dot");

    // TEST DFS ricorsivo --------------------------
    int sorgente = 1;
    undirected_graph<int> dfs_tree = recursive_dfs(G, sorgente);
    export_to_dot(dfs_tree, "dfs_recursive.dot");


    // TEST dijkstra -------------------------------
    undirected_graph<int> H;
    H.add_edge(undirected_edge<int>(0, 1, 4.0));
    H.add_edge(undirected_edge<int>(0, 2, 2.0));
    H.add_edge(undirected_edge<int>(1, 2, 1.0));
    H.add_edge(undirected_edge<int>(1, 3, 5.0));
    H.add_edge(undirected_edge<int>(2, 3, 8.0));
    H.add_edge(undirected_edge<int>(2, 4, 10.0));
    H.add_edge(undirected_edge<int>(3, 4, 2.0));
    H.add_edge(undirected_edge<int>(3, 5, 6.0));
    H.add_edge(undirected_edge<int>(4, 5, 3.0));
    int s_H = 0;
    undirected_graph<int> dijkstraH = dijkstra(H, s_H);
    export_to_dot(dijkstraH, "dijkstra_H.dot");

    return 0;
}