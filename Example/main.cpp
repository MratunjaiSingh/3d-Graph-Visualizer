// #include <iostream>
// #include "../Include/Graph.h"
// #include "../Include/VisualGraphDSA.h"

// using namespace std;

// int main(int argc, char** argv) {
//     // 1. Total Nodes define karo (8 nodes ka example)
//     int n = 8; 
//     UnweightedGraph ug;

//     // 2. Graph Edges add karo (Undirected Rectangle/Grid jaisa)
//     // Layer 0 to 1
//     ug.add_edge(0, 1, false); ug.add_edge(0, 2, false);
//     // Layer 1 to 2
//     ug.add_edge(1, 3, false); ug.add_edge(1, 4, false);
//     ug.add_edge(2, 5, false); ug.add_edge(2, 6, false);
//     // Layer 2 to 3
//     ug.add_edge(3, 7, false);

//     // 3. Algorithm Run Karo
//     // bfs_traversal_disconnected(total_nodes)
//     // Ye apne aap Node 0 ko SRC banayega aur -2 level markers add karega
//     cout << ">> Starting BFS Traversal from Node 0..." << endl;
//     ug.bfs_traversal_disconnected(n);

//     // 4. Visualizer ko Data pass karo
//     // Parameters: (Graph object, Total nodes, IsDirected?)
//     GraphVisualizer viz(ug, n, false);
    
//     // 5. Visualize! (Window open hogi aur animation shuru)
//     viz.visualize(argc, argv);

//     return 0;
// }

//
#include <iostream>
#include "../Include/Graph.h"
#include "../Include/VisualGraphDSA.h"

using namespace std;

int main(int argc, char** argv) {
    int n = 9; // 3x3 Grid banayenge
    UnweightedGraph ug;

    // --- ROW 1 (0, 1, 2) ---
    ug.add_edge(0, 1, false); ug.add_edge(1, 2, false);
    
    // --- ROW 2 (3, 4, 5) ---
    ug.add_edge(3, 4, false); ug.add_edge(4, 5, false);
    
    // --- ROW 3 (6, 7, 8) ---
    ug.add_edge(6, 7, false); ug.add_edge(7, 8, false);

    // --- VERTICAL CONNECTIONS (Connecting Rows) ---
    ug.add_edge(0, 3, false); ug.add_edge(3, 6, false);
    ug.add_edge(1, 4, false); ug.add_edge(4, 7, false);
    ug.add_edge(2, 5, false); ug.add_edge(5, 8, false);

    // Algorithm Run
    cout << ">> Running Clean BFS on 3x3 Grid..." << endl;
    ug.bfs_traversal_disconnected(n);

    GraphVisualizer viz(ug, n, false);
    viz.visualize(argc, argv);

    return 0;
}