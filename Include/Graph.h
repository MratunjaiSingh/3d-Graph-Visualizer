
// // // // // // // // // #ifndef GRAPH_H
// // // // // // // // // #define GRAPH_H

// // // // // // // // // #include<iostream>
// // // // // // // // // #include<unordered_map>
// // // // // // // // // #include<list>
// // // // // // // // // #include<vector>
// // // // // // // // // #include<queue>
// // // // // // // // // #include<set>
// // // // // // // // // #include<algorithm>
// // // // // // // // // #include<climits>
// // // // // // // // // #include<stack>
// // // // // // // // // #include "DSU.h"

// // // // // // // // // using namespace std;

// // // // // // // // // enum AlgoType {
// // // // // // // // //     NONE, BFS, DFS, TOPOSORT_DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, TARJAN, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED
// // // // // // // // // };

// // // // // // // // // // ==========================================
// // // // // // // // // // 1. UNWEIGHTED GRAPH CLASS (FIXED)
// // // // // // // // // // ==========================================
// // // // // // // // // class UnweightedGraph {
// // // // // // // // // public:
// // // // // // // // //     unordered_map<int, list<int>> adjlist; // <--- Yeh missing tha shayad
// // // // // // // // //     AlgoType lastAlgo = NONE;             // <--- Yeh error de raha tha
// // // // // // // // //     vector<int> anim_nodes;
// // // // // // // // //     vector<pair<int, int>> anim_edges;

// // // // // // // // //     void add_edge(int u, int v, bool direction) {
// // // // // // // // //         adjlist[u].push_back(v);
// // // // // // // // //         if (!direction) adjlist[v].push_back(u);
// // // // // // // // //     }

// // // // // // // // //     void bfs(int startNode) {
// // // // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // // // //         unordered_map<int, bool> vis;
// // // // // // // // //         queue<pair<int, int>> q;
// // // // // // // // //         q.push({startNode, -1}); vis[startNode] = true;
// // // // // // // // //         while (!q.empty()) {
// // // // // // // // //             int u = q.front().first; int p = q.front().second; q.pop();
// // // // // // // // //             anim_nodes.push_back(u);
// // // // // // // // //             if (p != -1) anim_edges.push_back({p, u});
// // // // // // // // //             for (int v : adjlist[u]) if (!vis[v]) { vis[v] = true; q.push({v, u}); }
// // // // // // // // //         }
// // // // // // // // //         lastAlgo = BFS;
// // // // // // // // //     }

// // // // // // // // //     void dfs_helper(int u, int p, unordered_map<int, bool>& vis) {
// // // // // // // // //         vis[u] = true; anim_nodes.push_back(u);
// // // // // // // // //         if (p != -1) anim_edges.push_back({p, u});
// // // // // // // // //         for (int v : adjlist[u]) if (!vis[v]) dfs_helper(v, u, vis);
// // // // // // // // //     }
    
// // // // // // // // //     void dfs(int startNode) {
// // // // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // // // //         unordered_map<int, bool> vis;
// // // // // // // // //         dfs_helper(startNode, -1, vis);
// // // // // // // // //         lastAlgo = DFS;
// // // // // // // // //     }
// // // // // // // // // };

// // // // // // // // // // ==========================================
// // // // // // // // // // 2. WEIGHTED GRAPH CLASS
// // // // // // // // // // ==========================================
// // // // // // // // // class WeightedGraph {
// // // // // // // // // public:
// // // // // // // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // // // // // // //     int lastCalculatedDistance = -1;
// // // // // // // // //     AlgoType lastAlgo = NONE;
// // // // // // // // //     vector<int> anim_nodes;
// // // // // // // // //     vector<pair<int, int>> anim_edges;
// // // // // // // // //     vector<int> nodeGroup; 

// // // // // // // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // // // // // // //         adjlist[u].push_back({v, wt});
// // // // // // // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // // // // // // //     }

// // // // // // // // //     void toposort_bfs(int n) {
// // // // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // // // //         vector<int> indegree(n, 0);
// // // // // // // // //         for (auto const& p : adjlist) {
// // // // // // // // //             for (auto const& nbrPair : p.second) indegree[nbrPair.first]++;
// // // // // // // // //         }
// // // // // // // // //         queue<int> q;
// // // // // // // // //         for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // // // // // // // //         int count = 0;
// // // // // // // // //         while (!q.empty()) {
// // // // // // // // //             int u = q.front(); q.pop(); anim_nodes.push_back(u);
// // // // // // // // //             count++;
// // // // // // // // //             for (auto const& nbrPair : adjlist[u]) {
// // // // // // // // //                 int v = nbrPair.first;
// // // // // // // // //                 anim_edges.push_back({u, v});
// // // // // // // // //                 if (--indegree[v] == 0) q.push(v);
// // // // // // // // //             }
// // // // // // // // //         }
// // // // // // // // //         if (count < n) {
// // // // // // // // //             lastAlgo = CYCLE_DETECTED;
// // // // // // // // //             for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); 
// // // // // // // // //         } else lastAlgo = TOPOSORT_BFS;
// // // // // // // // //     }
// // // // // // // // // };
// // // // // // // // // #endif
// // // // // // // // //
// // // // // // // // //
// // // // // // // // #ifndef GRAPH_H
// // // // // // // // #define GRAPH_H

// // // // // // // // #include<iostream>
// // // // // // // // #include<unordered_map>
// // // // // // // // #include<list>
// // // // // // // // #include<vector>
// // // // // // // // #include<queue>
// // // // // // // // #include<algorithm>


// // // // // // // // using namespace std;

// // // // // // // // enum AlgoType { NONE, BFS, DFS, TOPOSORT_BFS, CYCLE_DETECTED, DIJKSTRA, SCC, BRIDGES };

// // // // // // // // struct EdgeInfo { int u, v, weight; };

// // // // // // // // class UnweightedGraph {
// // // // // // // // public:
// // // // // // // //     unordered_map<int, list<int>> adjlist;
// // // // // // // //     AlgoType lastAlgo = NONE;
// // // // // // // //     vector<int> anim_nodes;
// // // // // // // //     vector<pair<int, int>> anim_edges;

// // // // // // // //     void add_edge(int u, int v, bool direction) {
// // // // // // // //         adjlist[u].push_back(v);
// // // // // // // //         if (!direction) adjlist[v].push_back(u);
// // // // // // // //     }
// // // // // // // // };

// // // // // // // // class WeightedGraph {
// // // // // // // // public:
// // // // // // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // // // // // //     AlgoType lastAlgo = NONE;
// // // // // // // //     vector<int> anim_nodes;
// // // // // // // //     vector<pair<int, int>> anim_edges;
// // // // // // // //     vector<int> nodeGroup;
// // // // // // // //     int lastCalculatedDistance = -1;

// // // // // // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // // // // // //         adjlist[u].push_back({v, wt});
// // // // // // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // // // // // //     }

// // // // // // // //     void toposort_bfs(int n) {
// // // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // // //         vector<int> indegree(n, 0);
// // // // // // // //         for (auto const& p : adjlist) {
// // // // // // // //             for (auto const& nbr : p.second) indegree[nbr.first]++;
// // // // // // // //         }
// // // // // // // //         queue<int> q;
// // // // // // // //         for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
        
// // // // // // // //         int count = 0;
// // // // // // // //         while (!q.empty()) {
// // // // // // // //             int u = q.front(); q.pop(); anim_nodes.push_back(u);
// // // // // // // //             count++;
// // // // // // // //             for (auto const& nbr : adjlist[u]) {
// // // // // // // //                 anim_edges.push_back({u, nbr.first});
// // // // // // // //                 if (--indegree[nbr.first] == 0) q.push(nbr.first);
// // // // // // // //             }
// // // // // // // //         }
// // // // // // // //         if (count < n) {
// // // // // // // //             lastAlgo = CYCLE_DETECTED;
// // // // // // // //             for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i);
// // // // // // // //         } else lastAlgo = TOPOSORT_BFS;
// // // // // // // //     }
// // // // // // // // };
// // // // // // // // #endif
// // // // // // // //
// // // // // // // #ifndef GRAPH_H
// // // // // // // #define GRAPH_H

// // // // // // // #include<iostream>
// // // // // // // #include<unordered_map>
// // // // // // // #include<list>
// // // // // // // #include<vector>
// // // // // // // #include<queue>
// // // // // // // #include<stack>
// // // // // // // #include<set>
// // // // // // // #include<algorithm>
// // // // // // // #include<climits>

// // // // // // // using namespace std;

// // // // // // // // Saare algorithms ke types
// // // // // // // enum AlgoType { 
// // // // // // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // // // // // };

// // // // // // // // ==========================================
// // // // // // // // 1. UNWEIGHTED GRAPH (BFS Shortest Path, DFS Cycle, etc.)
// // // // // // // // ==========================================
// // // // // // // class UnweightedGraph {
// // // // // // // public:
// // // // // // //     unordered_map<int, list<int>> adjlist;
// // // // // // //     AlgoType lastAlgo = NONE;
// // // // // // //     vector<int> anim_nodes;
// // // // // // //     vector<pair<int, int>> anim_edges;

// // // // // // //     void add_edge(int u, int v, bool direction) {
// // // // // // //         adjlist[u].push_back(v);
// // // // // // //         if (!direction) adjlist[v].push_back(u);
// // // // // // //     }

// // // // // // //     // 🔥 BFS SHORTEST PATH (Unweighted)
// // // // // // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // //         vector<int> parent(n, -1);
// // // // // // //         vector<bool> vis(n, false);
// // // // // // //         queue<int> q;

// // // // // // //         q.push(startNode); vis[startNode] = true;
// // // // // // //         while(!q.empty()){
// // // // // // //             int u = q.front(); q.pop();
// // // // // // //             if(u == targetNode) break;
// // // // // // //             for(int v : adjlist[u]){
// // // // // // //                 if(!vis[v]){
// // // // // // //                     vis[v] = true; parent[v] = u; q.push(v);
// // // // // // //                 }
// // // // // // //             }
// // // // // // //         }
// // // // // // //         // Path Reconstruction
// // // // // // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // // // // // //             anim_nodes.push_back(v);
// // // // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // // // //         }
// // // // // // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // // // // // //         lastAlgo = BFS;
// // // // // // //     }

// // // // // // //     // 🔥 DFS CYCLE DETECTION
// // // // // // //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// // // // // // //         vis[u] = true; dfsvis[u] = true;
// // // // // // //         anim_nodes.push_back(u);
// // // // // // //         for (int v : adjlist[u]) {
// // // // // // //             if (!vis[v]) {
// // // // // // //                 anim_edges.push_back({u, v});
// // // // // // //                 if (dfs_cycle_helper(v, vis, dfsvis)) return true;
// // // // // // //             } else if (dfsvis[v]) {
// // // // // // //                 anim_edges.push_back({u, v}); // Cycle Edge!
// // // // // // //                 return true;
// // // // // // //             }
// // // // // // //         }
// // // // // // //         dfsvis[u] = false; return false;
// // // // // // //     }

// // // // // // //     void detect_cycle_dfs(int n) {
// // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // //         vector<bool> vis(n, false), dfsvis(n, false);
// // // // // // //         for(int i=0; i<n; i++) if(!vis[i]) if(dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// // // // // // //         lastAlgo = DFS;
// // // // // // //     }
// // // // // // // };

// // // // // // // // ==========================================
// // // // // // // // 2. WEIGHTED GRAPH (Dijkstra, Topo, MST, etc.)
// // // // // // // // ==========================================
// // // // // // // class WeightedGraph {
// // // // // // // public:
// // // // // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // // // // //     AlgoType lastAlgo = NONE;
// // // // // // //     vector<int> anim_nodes;
// // // // // // //     vector<pair<int, int>> anim_edges;
// // // // // // //     int lastCalculatedDistance = -1;

// // // // // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // // // // //         adjlist[u].push_back({v, wt});
// // // // // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // // // // //     }

// // // // // // //     // 🔥 DIJKSTRA (Shortest Path in Weighted Graph)
// // // // // // //     void dijkstra(int n, int src, int dest) {
// // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // //         vector<int> dist(n, INT_MAX); vector<int> parent(n, -1);
// // // // // // //         set<pair<int, int>> st;
// // // // // // //         dist[src] = 0; st.insert({0, src});

// // // // // // //         while(!st.empty()){
// // // // // // //             auto top = *(st.begin()); st.erase(st.begin());
// // // // // // //             int u = top.second; int d = top.first;
// // // // // // //             for(auto nbr : adjlist[u]){
// // // // // // //                 if(d + nbr.second < dist[nbr.first]){
// // // // // // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // // // // // //                     dist[nbr.first] = d + nbr.second;
// // // // // // //                     parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // // // // // //                 }
// // // // // // //             }
// // // // // // //         }
// // // // // // //         for(int v = dest; v != -1; v = parent[v]) {
// // // // // // //             anim_nodes.push_back(v);
// // // // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // // // //         }
// // // // // // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = dist[dest];
// // // // // // //     }

// // // // // // //     // 🔥 KAHN'S ALGO (BFS Cycle & Topo)
// // // // // // //     void toposort_bfs(int n) {
// // // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // // //         vector<int> indegree(n, 0);
// // // // // // //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// // // // // // //         queue<int> q;
// // // // // // //         for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // // // // // //         int count = 0;
// // // // // // //         while (!q.empty()) {
// // // // // // //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// // // // // // //             for (auto const& nbr : adjlist[u]) {
// // // // // // //                 anim_edges.push_back({u, nbr.first});
// // // // // // //                 if (--indegree[nbr.first] == 0) q.push(nbr.first);
// // // // // // //             }
// // // // // // //         }
// // // // // // //         if (count < n) {
// // // // // // //             lastAlgo = CYCLE_DETECTED;
// // // // // // //             for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i);
// // // // // // //         } else lastAlgo = TOPOSORT_BFS;
// // // // // // //     }
// // // // // // // };

// // // // // // // #endif


// // // // // // #ifndef GRAPH_H
// // // // // // #define GRAPH_H

// // // // // // #include<iostream>
// // // // // // #include<unordered_map>
// // // // // // #include<list>
// // // // // // #include<vector>
// // // // // // #include<queue>
// // // // // // #include<stack>
// // // // // // #include<set>
// // // // // // #include<algorithm>
// // // // // // #include<climits>

// // // // // // using namespace std;

// // // // // // enum AlgoType { 
// // // // // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // // // // };

// // // // // // class UnweightedGraph {
// // // // // // public:
// // // // // //     unordered_map<int, list<int>> adjlist;
// // // // // //     AlgoType lastAlgo = NONE;
// // // // // //     vector<int> anim_nodes;
// // // // // //     vector<pair<int, int>> anim_edges;

// // // // // //     void add_edge(int u, int v, bool direction) {
// // // // // //         adjlist[u].push_back(v);
// // // // // //         if (!direction) adjlist[v].push_back(u);
// // // // // //     }

// // // // // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // //         vector<int> parent(n, -1);
// // // // // //         vector<bool> vis(n, false);
// // // // // //         queue<int> q;
// // // // // //         q.push(startNode); vis[startNode] = true;
// // // // // //         while(!q.empty()){
// // // // // //             int u = q.front(); q.pop();
// // // // // //             if(u == targetNode) break;
// // // // // //             for(int v : adjlist[u]){
// // // // // //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// // // // // //             }
// // // // // //         }
// // // // // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // // // // //             anim_nodes.push_back(v);
// // // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // // //         }
// // // // // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // // // // //         lastAlgo = BFS;
// // // // // //     }
// // // // // // };

// // // // // // class WeightedGraph {
// // // // // // public:
// // // // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // // // //     AlgoType lastAlgo = NONE;
// // // // // //     vector<int> anim_nodes;
// // // // // //     vector<pair<int, int>> anim_edges;
// // // // // //     int lastCalculatedDistance = -1;

// // // // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // // // //         adjlist[u].push_back({v, wt});
// // // // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // // // //     }

// // // // // //     void dijkstra(int n, int src, int dest) {
// // // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // // //         vector<int> dist(n, INT_MAX); vector<int> parent(n, -1);
// // // // // //         set<pair<int, int>> st;
// // // // // //         dist[src] = 0; st.insert({0, src});
// // // // // //         while(!st.empty()){
// // // // // //             auto top = *(st.begin()); st.erase(st.begin());
// // // // // //             int u = top.second; int d = top.first;
// // // // // //             for(auto nbr : adjlist[u]){
// // // // // //                 if(d + nbr.second < dist[nbr.first]){
// // // // // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // // // // //                     dist[nbr.first] = d + nbr.second;
// // // // // //                     parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // // // // //                 }
// // // // // //             }
// // // // // //         }
// // // // // //         for(int v = dest; v != -1; v = parent[v]) {
// // // // // //             anim_nodes.push_back(v);
// // // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // // //         }
// // // // // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = dist[dest];
// // // // // //     }
// // // // // // };
// // // // // // #endif
// // // // // //
// // // // // #ifndef GRAPH_H
// // // // // #define GRAPH_H

// // // // // #include<iostream>
// // // // // #include<unordered_map>
// // // // // #include<list>
// // // // // #include<vector>
// // // // // #include<queue>
// // // // // #include<stack>
// // // // // #include<set>
// // // // // #include<algorithm>
// // // // // #include<climits>

// // // // // using namespace std;

// // // // // // ==========================================
// // // // // // 🔥 ALL ALGORITHMS ENUM
// // // // // // ==========================================
// // // // // enum AlgoType { 
// // // // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // // // };

// // // // // // ==========================================
// // // // // // 🔥 DSU CLASS (For Kruskal's Algorithm)
// // // // // // ==========================================
// // // // // class DSU {
// // // // //     vector<int> parent, rank;
// // // // // public:
// // // // //     DSU(int n) {
// // // // //         parent.resize(n); rank.resize(n, 0);
// // // // //         for(int i = 0; i < n; i++) parent[i] = i;
// // // // //     }
// // // // //     int findUPar(int node) {
// // // // //         if(node == parent[node]) return node;
// // // // //         return parent[node] = findUPar(parent[node]); 
// // // // //     }
// // // // //     bool unionByRank(int u, int v) {
// // // // //         int ulp_u = findUPar(u), ulp_v = findUPar(v);
// // // // //         if(ulp_u == ulp_v) return false; // Cycle detected, edges won't be added
// // // // //         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
// // // // //         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
// // // // //         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
// // // // //         return true; // Successfully merged
// // // // //     }
// // // // // };

// // // // // // ==========================================
// // // // // // 1. UNWEIGHTED GRAPH (BFS, DFS, Bridges, SCC)
// // // // // // ==========================================
// // // // // class UnweightedGraph {
// // // // // public:
// // // // //     unordered_map<int, list<int>> adjlist;
// // // // //     AlgoType lastAlgo = NONE;
// // // // //     vector<int> anim_nodes;
// // // // //     vector<pair<int, int>> anim_edges;

// // // // //     void add_edge(int u, int v, bool direction) {
// // // // //         adjlist[u].push_back(v);
// // // // //         if (!direction) adjlist[v].push_back(u);
// // // // //     }

// // // // //     // --- 1. BFS Shortest Path ---
// // // // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> parent(n, -1);
// // // // //         vector<bool> vis(n, false);
// // // // //         queue<int> q;
        
// // // // //         q.push(startNode); vis[startNode] = true;
// // // // //         while(!q.empty()){
// // // // //             int u = q.front(); q.pop();
// // // // //             if(u == targetNode) break;
// // // // //             for(int v : adjlist[u]){
// // // // //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// // // // //             }
// // // // //         }
// // // // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // // // //             anim_nodes.push_back(v);
// // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // //         }
// // // // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // // // //         lastAlgo = BFS;
// // // // //     }

// // // // //     // --- 2. DFS Cycle Detection ---
// // // // //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// // // // //         vis[u] = true; dfsvis[u] = true;
// // // // //         anim_nodes.push_back(u);
// // // // //         for (int v : adjlist[u]) {
// // // // //             if (!vis[v]) {
// // // // //                 anim_edges.push_back({u, v});
// // // // //                 if (dfs_cycle_helper(v, vis, dfsvis)) return true;
// // // // //             } else if (dfsvis[v]) {
// // // // //                 anim_edges.push_back({u, v}); 
// // // // //                 return true;
// // // // //             }
// // // // //         }
// // // // //         dfsvis[u] = false; return false;
// // // // //     }

// // // // //     void detect_cycle_dfs(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<bool> vis(n, false), dfsvis(n, false);
// // // // //         for(int i=0; i<n; i++) {
// // // // //             if(!vis[i]) {
// // // // //                 if(dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// // // // //             }
// // // // //         }
// // // // //         lastAlgo = DFS;
// // // // //     }

// // // // //     // --- 3. Tarjan's Find Bridges ---
// // // // //     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
// // // // //         vis[u] = true; tin[u] = low[u] = timer++;
// // // // //         anim_nodes.push_back(u);
// // // // //         for (int v : adjlist[u]) {
// // // // //             if (v == p) continue;
// // // // //             if (vis[v]) {
// // // // //                 low[u] = min(low[u], tin[v]);
// // // // //             } else {
// // // // //                 findBridgesHelper(v, u, tin, low, timer, vis);
// // // // //                 low[u] = min(low[u], low[v]);
// // // // //                 if (low[v] > tin[u]) anim_edges.push_back({u, v}); // Bridge Edge Highlight
// // // // //             }
// // // // //         }
// // // // //     }

// // // // //     void find_bridges(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> tin(n, -1), low(n, -1);
// // // // //         vector<bool> vis(n, false);
// // // // //         int timer = 0;
// // // // //         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
// // // // //         lastAlgo = BRIDGES;
// // // // //     }

// // // // //     // --- 4. Kosaraju's SCC (Strongly Connected Components) ---
// // // // //     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
// // // // //         vis[u] = true;
// // // // //         for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st);
// // // // //         st.push(u);
// // // // //     }
// // // // //     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
// // // // //         vis[u] = true; anim_nodes.push_back(u); // Highlight component nodes
// // // // //         for(int v : revAdj[u]) {
// // // // //             if(!vis[v]) {
// // // // //                 anim_edges.push_back({u, v});
// // // // //                 dfs_scc2(v, vis, revAdj);
// // // // //             }
// // // // //         }
// // // // //     }
// // // // //     void getSCC(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<bool> vis(n, false); stack<int> st;
// // // // //         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
        
// // // // //         unordered_map<int, list<int>> revAdj;
// // // // //         for(int i=0; i<n; i++) {
// // // // //             for(int v : adjlist[i]) revAdj[v].push_back(i);
// // // // //         }
        
// // // // //         fill(vis.begin(), vis.end(), false);
// // // // //         while(!st.empty()) {
// // // // //             int node = st.top(); st.pop();
// // // // //             if(!vis[node]) dfs_scc2(node, vis, revAdj);
// // // // //         }
// // // // //         lastAlgo = SCC;
// // // // //     }
// // // // // };

// // // // // // ==========================================
// // // // // // 2. WEIGHTED GRAPH (Dijkstra, MST, Shortest Paths)
// // // // // // ==========================================
// // // // // class WeightedGraph {
// // // // // public:
// // // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // // //     AlgoType lastAlgo = NONE;
// // // // //     vector<int> anim_nodes;
// // // // //     vector<pair<int, int>> anim_edges;
// // // // //     int lastCalculatedDistance = -1;

// // // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // // //         adjlist[u].push_back({v, wt});
// // // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // // //     }

// // // // //     // --- 5. Dijkstra Algorithm ---
// // // // //     void dijkstra(int n, int src, int dest) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> dist(n, INT_MAX); vector<int> parent(n, -1);
// // // // //         set<pair<int, int>> st;
        
// // // // //         dist[src] = 0; st.insert({0, src});
// // // // //         while(!st.empty()){
// // // // //             auto top = *(st.begin()); st.erase(st.begin());
// // // // //             int u = top.second; int d = top.first;
// // // // //             for(auto nbr : adjlist[u]){
// // // // //                 if(d + nbr.second < dist[nbr.first]){
// // // // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // // // //                     dist[nbr.first] = d + nbr.second;
// // // // //                     parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // // // //                 }
// // // // //             }
// // // // //         }
// // // // //         for(int v = dest; v != -1; v = parent[v]) {
// // // // //             anim_nodes.push_back(v);
// // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // //         }
// // // // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = dist[dest];
// // // // //     }

// // // // //     // --- 6. Kahn's TopoSort & Cycle Detection (BFS) ---
// // // // //     void toposort_bfs(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> indegree(n, 0);
// // // // //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// // // // //         queue<int> q;
// // // // //         for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // // // //         int count = 0;
// // // // //         while (!q.empty()) {
// // // // //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// // // // //             for (auto const& nbr : adjlist[u]) {
// // // // //                 anim_edges.push_back({u, nbr.first});
// // // // //                 if (--indegree[nbr.first] == 0) q.push(nbr.first);
// // // // //             }
// // // // //         }
// // // // //         if (count < n) {
// // // // //             lastAlgo = CYCLE_DETECTED;
// // // // //             for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i);
// // // // //         } else lastAlgo = TOPOSORT_BFS;
// // // // //     }

// // // // //     // --- 7. Prim's Algorithm (MST) ---
// // // // //     void primsMST(int n, int src) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
// // // // //         vector<bool> vis(n, false);
// // // // //         pq.push({0, {src, -1}});
// // // // //         while (!pq.empty()) {
// // // // //             auto it = pq.top(); pq.pop();
// // // // //             int u = it.second.first, p = it.second.second;
// // // // //             if (vis[u]) continue;
// // // // //             vis[u] = true; anim_nodes.push_back(u);
// // // // //             if (p != -1) anim_edges.push_back({p, u});
// // // // //             for (auto nbr : adjlist[u]) {
// // // // //                 if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
// // // // //             }
// // // // //         }
// // // // //         lastAlgo = PRIMS;
// // // // //     }

// // // // //     // --- 8. Kruskal's Algorithm (MST using DSU) ---
// // // // //     void kruskalMST(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         struct Edge { int u, v, w; };
// // // // //         vector<Edge> edges;
// // // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
        
// // // // //         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
// // // // //         DSU ds(n);
        
// // // // //         for(auto e : edges) {
// // // // //             if(ds.unionByRank(e.u, e.v)) {
// // // // //                 anim_nodes.push_back(e.u); anim_nodes.push_back(e.v);
// // // // //                 anim_edges.push_back({e.u, e.v});
// // // // //             }
// // // // //         }
// // // // //         lastAlgo = KRUSKAL;
// // // // //     }

// // // // //     // --- 9. Bellman-Ford Algorithm (Negative Weights) ---
// // // // //     void bellman_ford(int n, int src) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> dist(n, 1e9); dist[src] = 0; anim_nodes.push_back(src);
// // // // //         struct Edge { int u, v, w; };
// // // // //         vector<Edge> edges;
// // // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});

// // // // //         for (int i = 0; i < n - 1; i++) {
// // // // //             for (auto e : edges) {
// // // // //                 if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) {
// // // // //                     dist[e.v] = dist[e.u] + e.w;
// // // // //                     anim_edges.push_back({e.u, e.v}); 
// // // // //                 }
// // // // //             }
// // // // //         }
// // // // //         lastAlgo = BELLMAN_FORD;
// // // // //     }

// // // // //     // --- 10. Floyd-Warshall Algorithm (All-Pairs Shortest Path) ---
// // // // //     void floyd_warshall(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<vector<int>> matrix(n, vector<int>(n, 1e9));
// // // // //         for(int i=0; i<n; i++) matrix[i][i] = 0;
// // // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) matrix[p.first][nbr.first] = nbr.second;

// // // // //         for(int k = 0; k < n; k++) {
// // // // //             anim_nodes.push_back(k); // Highlight intermediate node
// // // // //             for(int i = 0; i < n; i++) {
// // // // //                 for(int j = 0; j < n; j++) {
// // // // //                     if(matrix[i][k] != 1e9 && matrix[k][j] != 1e9) {
// // // // //                         matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
// // // // //                     }
// // // // //                 }
// // // // //             }
// // // // //         }
// // // // //         lastAlgo = FLOYD;
// // // // //     }
// // // // // };

// // // // // #endif
// // // // //
// // // // // #ifndef GRAPH_H
// // // // // #define GRAPH_H

// // // // // #include <iostream>
// // // // // #include <unordered_map>
// // // // // #include <list>
// // // // // #include <vector>
// // // // // #include <queue>
// // // // // #include <stack>
// // // // // #include <set>
// // // // // #include <algorithm>
// // // // // #include <climits>

// // // // // using namespace std;

// // // // // // ==========================================
// // // // // // 🔥 ALL ALGORITHMS ENUM
// // // // // // ==========================================
// // // // // enum AlgoType { 
// // // // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // // // };

// // // // // // ==========================================
// // // // // // 🔥 DSU CLASS (For Kruskal's Algorithm)
// // // // // // ==========================================
// // // // // class DSU {
// // // // //     vector<int> parent, rank;
// // // // // public:
// // // // //     DSU(int n) {
// // // // //         parent.resize(n); rank.resize(n, 0);
// // // // //         for(int i = 0; i < n; i++) parent[i] = i;
// // // // //     }
// // // // //     int findUPar(int node) {
// // // // //         if(node == parent[node]) return node;
// // // // //         return parent[node] = findUPar(parent[node]); 
// // // // //     }
// // // // //     bool unionByRank(int u, int v) {
// // // // //         int ulp_u = findUPar(u), ulp_v = findUPar(v);
// // // // //         if(ulp_u == ulp_v) return false; 
// // // // //         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
// // // // //         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
// // // // //         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
// // // // //         return true; 
// // // // //     }
// // // // // };

// // // // // // ==========================================
// // // // // // 1. UNWEIGHTED GRAPH (BFS, DFS, Bridges, SCC)
// // // // // // ==========================================
// // // // // class UnweightedGraph {
// // // // // public:
// // // // //     unordered_map<int, list<int>> adjlist;
// // // // //     AlgoType lastAlgo = NONE;
// // // // //     vector<int> anim_nodes;
// // // // //     vector<pair<int, int>> anim_edges;

// // // // //     void add_edge(int u, int v, bool direction) {
// // // // //         adjlist[u].push_back(v);
// // // // //         if (!direction) adjlist[v].push_back(u);
// // // // //     }

// // // // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> parent(n, -1);
// // // // //         vector<bool> vis(n, false);
// // // // //         queue<int> q;
        
// // // // //         q.push(startNode); vis[startNode] = true;
// // // // //         while(!q.empty()){
// // // // //             int u = q.front(); q.pop();
// // // // //             if(u == targetNode) break;
// // // // //             for(int v : adjlist[u]){
// // // // //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// // // // //             }
// // // // //         }
// // // // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // // // //             anim_nodes.push_back(v);
// // // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // // //         }
// // // // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // // // //         lastAlgo = BFS;
// // // // //     }

// // // // //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// // // // //         vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
// // // // //         for (int v : adjlist[u]) {
// // // // //             if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
// // // // //             else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
// // // // //         }
// // // // //         dfsvis[u] = false; return false;
// // // // //     }

// // // // //     void detect_cycle_dfs(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<bool> vis(n, false), dfsvis(n, false);
// // // // //         for(int i=0; i<n; i++) if(!vis[i] && dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// // // // //         lastAlgo = DFS;
// // // // //     }

// // // // //     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
// // // // //         vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
// // // // //         for (int v : adjlist[u]) {
// // // // //             if (v == p) continue;
// // // // //             if (vis[v]) low[u] = min(low[u], tin[v]);
// // // // //             else {
// // // // //                 findBridgesHelper(v, u, tin, low, timer, vis);
// // // // //                 low[u] = min(low[u], low[v]);
// // // // //                 if (low[v] > tin[u]) anim_edges.push_back({u, v});
// // // // //             }
// // // // //         }
// // // // //     }

// // // // //     void find_bridges(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false);
// // // // //         int timer = 0;
// // // // //         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
// // // // //         lastAlgo = BRIDGES;
// // // // //     }

// // // // //     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
// // // // //         vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
// // // // //     }
// // // // //     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
// // // // //         vis[u] = true; anim_nodes.push_back(u); 
// // // // //         for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
// // // // //     }
// // // // //     void getSCC(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<bool> vis(n, false); stack<int> st;
// // // // //         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
        
// // // // //         unordered_map<int, list<int>> revAdj;
// // // // //         for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
        
// // // // //         fill(vis.begin(), vis.end(), false);
// // // // //         while(!st.empty()) {
// // // // //             int node = st.top(); st.pop();
// // // // //             if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); } // -1 as component separator
// // // // //         }
// // // // //         lastAlgo = SCC;
// // // // //     }
// // // // // };

// // // // // // ==========================================
// // // // // // 2. WEIGHTED GRAPH (Dijkstra, MST, etc.)
// // // // // // ==========================================
// // // // // class WeightedGraph {
// // // // // public:
// // // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // // //     AlgoType lastAlgo = NONE;
// // // // //     vector<int> anim_nodes;
// // // // //     vector<pair<int, int>> anim_edges;
// // // // //     int lastCalculatedDistance = -1;

// // // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // // //         adjlist[u].push_back({v, wt});
// // // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // // //     }

// // // // //     void dijkstra(int n, int src, int dest) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> dist(n, INT_MAX); vector<int> parent(n, -1);
// // // // //         set<pair<int, int>> st;
// // // // //         dist[src] = 0; st.insert({0, src});
// // // // //         while(!st.empty()){
// // // // //             auto top = *(st.begin()); st.erase(st.begin());
// // // // //             int u = top.second; int d = top.first;
// // // // //             for(auto nbr : adjlist[u]){
// // // // //                 if(d + nbr.second < dist[nbr.first]){
// // // // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // // // //                     dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // // // //                 }
// // // // //             }
// // // // //         }
// // // // //         for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// // // // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == INT_MAX) ? -1 : dist[dest];
// // // // //     }

// // // // //     void toposort_bfs(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> indegree(n, 0);
// // // // //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// // // // //         queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // // // //         int count = 0;
// // // // //         while (!q.empty()) {
// // // // //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// // // // //             for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
// // // // //         }
// // // // //         if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } 
// // // // //         else lastAlgo = TOPOSORT_BFS;
// // // // //     }

// // // // //     void primsMST(int n, int src) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
// // // // //         vector<bool> vis(n, false); pq.push({0, {src, -1}});
// // // // //         while (!pq.empty()) {
// // // // //             auto it = pq.top(); pq.pop();
// // // // //             int u = it.second.first, p = it.second.second;
// // // // //             if (vis[u]) continue;
// // // // //             vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
// // // // //             for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
// // // // //         }
// // // // //         lastAlgo = PRIMS;
// // // // //     }

// // // // //     void kruskalMST(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // // // //         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
// // // // //         DSU ds(n);
// // // // //         for(auto e : edges) if(ds.unionByRank(e.u, e.v)) { anim_nodes.push_back(e.u); anim_nodes.push_back(e.v); anim_edges.push_back({e.u, e.v}); }
// // // // //         lastAlgo = KRUSKAL;
// // // // //     }

// // // // //     void bellman_ford(int n, int src) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<int> dist(n, 1e9); dist[src] = 0; anim_nodes.push_back(src);
// // // // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // // // //         for (int i = 0; i < n - 1; i++) for (auto e : edges) if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; anim_edges.push_back({e.u, e.v}); }
// // // // //         lastAlgo = BELLMAN_FORD;
// // // // //     }

// // // // //     void floyd_warshall(int n) {
// // // // //         anim_nodes.clear(); anim_edges.clear();
// // // // //         vector<vector<int>> matrix(n, vector<int>(n, 1e9));
// // // // //         for(int i=0; i<n; i++) matrix[i][i] = 0;
// // // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) matrix[p.first][nbr.first] = nbr.second;
// // // // //         for(int k = 0; k < n; k++) {
// // // // //             anim_nodes.push_back(k); 
// // // // //             for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(matrix[i][k] != 1e9 && matrix[k][j] != 1e9) matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
// // // // //         }
// // // // //         lastAlgo = FLOYD;
// // // // //     }
// // // // // };

// // // // // #endif
// // // // //

// // // // #ifndef GRAPH_H
// // // // #define GRAPH_H

// // // // #include <iostream>
// // // // #include <unordered_map>
// // // // #include <list>
// // // // #include <vector>
// // // // #include <queue>
// // // // #include <stack>
// // // // #include <set>
// // // // #include <algorithm>
// // // // #include <climits>

// // // // using namespace std;

// // // // enum AlgoType { 
// // // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // // };

// // // // class DSU {
// // // //     vector<int> parent, rank;
// // // // public:
// // // //     DSU(int n) {
// // // //         parent.resize(n); rank.resize(n, 0);
// // // //         for(int i = 0; i < n; i++) parent[i] = i;
// // // //     }
// // // //     int findUPar(int node) {
// // // //         if(node == parent[node]) return node;
// // // //         return parent[node] = findUPar(parent[node]); 
// // // //     }
// // // //     bool unionByRank(int u, int v) {
// // // //         int ulp_u = findUPar(u), ulp_v = findUPar(v);
// // // //         if(ulp_u == ulp_v) return false; 
// // // //         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
// // // //         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
// // // //         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
// // // //         return true; 
// // // //     }
// // // // };

// // // // class UnweightedGraph {
// // // // public:
// // // //     unordered_map<int, list<int>> adjlist;
// // // //     AlgoType lastAlgo = NONE;
// // // //     vector<int> anim_nodes;
// // // //     vector<pair<int, int>> anim_edges;
// // // //     int sourceNode = -1; // 🔥 For UI
// // // //     int destNode = -1;   // 🔥 For UI

// // // //     void add_edge(int u, int v, bool direction) {
// // // //         adjlist[u].push_back(v);
// // // //         if (!direction) adjlist[v].push_back(u);
// // // //     }

// // // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // // //         sourceNode = startNode; destNode = targetNode;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<int> parent(n, -1); vector<bool> vis(n, false); queue<int> q;
// // // //         q.push(startNode); vis[startNode] = true;
// // // //         while(!q.empty()){
// // // //             int u = q.front(); q.pop();
// // // //             if(u == targetNode) break;
// // // //             for(int v : adjlist[u]){
// // // //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// // // //             }
// // // //         }
// // // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // // //             anim_nodes.push_back(v);
// // // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // // //         }
// // // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // // //         lastAlgo = BFS;
// // // //     }

// // // //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// // // //         vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
// // // //         for (int v : adjlist[u]) {
// // // //             if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
// // // //             else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
// // // //         }
// // // //         dfsvis[u] = false; return false;
// // // //     }

// // // //     void detect_cycle_dfs(int n) {
// // // //         sourceNode = -1; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<bool> vis(n, false), dfsvis(n, false);
// // // //         for(int i=0; i<n; i++) if(!vis[i] && dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// // // //         lastAlgo = DFS;
// // // //     }

// // // //     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
// // // //         vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
// // // //         for (int v : adjlist[u]) {
// // // //             if (v == p) continue;
// // // //             if (vis[v]) low[u] = min(low[u], tin[v]);
// // // //             else {
// // // //                 findBridgesHelper(v, u, tin, low, timer, vis);
// // // //                 low[u] = min(low[u], low[v]);
// // // //                 if (low[v] > tin[u]) anim_edges.push_back({u, v});
// // // //             }
// // // //         }
// // // //     }

// // // //     void find_bridges(int n) {
// // // //         sourceNode = -1; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false);
// // // //         int timer = 0;
// // // //         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
// // // //         lastAlgo = BRIDGES;
// // // //     }

// // // //     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
// // // //         vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
// // // //     }
// // // //     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
// // // //         vis[u] = true; anim_nodes.push_back(u); 
// // // //         for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
// // // //     }
// // // //     void getSCC(int n) {
// // // //         sourceNode = -1; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<bool> vis(n, false); stack<int> st;
// // // //         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
        
// // // //         unordered_map<int, list<int>> revAdj;
// // // //         for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
        
// // // //         fill(vis.begin(), vis.end(), false);
// // // //         while(!st.empty()) {
// // // //             int node = st.top(); st.pop();
// // // //             if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); }
// // // //         }
// // // //         lastAlgo = SCC;
// // // //     }
// // // // };

// // // // class WeightedGraph {
// // // // public:
// // // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // // //     AlgoType lastAlgo = NONE;
// // // //     vector<int> anim_nodes;
// // // //     vector<pair<int, int>> anim_edges;
// // // //     int lastCalculatedDistance = -1;
// // // //     int sourceNode = -1; // 🔥 For UI
// // // //     int destNode = -1;   // 🔥 For UI

// // // //     void add_edge(int u, int v, int wt, bool direction) {
// // // //         adjlist[u].push_back({v, wt});
// // // //         if (!direction) adjlist[v].push_back({u, wt});
// // // //     }

// // // //     void dijkstra(int n, int src, int dest) {
// // // //         sourceNode = src; destNode = dest;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<int> dist(n, INT_MAX); vector<int> parent(n, -1);
// // // //         set<pair<int, int>> st;
// // // //         dist[src] = 0; st.insert({0, src});
// // // //         while(!st.empty()){
// // // //             auto top = *(st.begin()); st.erase(st.begin());
// // // //             int u = top.second; int d = top.first;
// // // //             for(auto nbr : adjlist[u]){
// // // //                 if(d + nbr.second < dist[nbr.first]){
// // // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // // //                     dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // // //                 }
// // // //             }
// // // //         }
// // // //         for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// // // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == INT_MAX) ? -1 : dist[dest];
// // // //     }

// // // //     void toposort_bfs(int n) {
// // // //         sourceNode = -1; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<int> indegree(n, 0);
// // // //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// // // //         queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // // //         int count = 0;
// // // //         while (!q.empty()) {
// // // //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// // // //             for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
// // // //         }
// // // //         if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } 
// // // //         else lastAlgo = TOPOSORT_BFS;
// // // //     }

// // // //     void primsMST(int n, int src) {
// // // //         sourceNode = src; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
// // // //         vector<bool> vis(n, false); pq.push({0, {src, -1}});
// // // //         while (!pq.empty()) {
// // // //             auto it = pq.top(); pq.pop();
// // // //             int u = it.second.first, p = it.second.second;
// // // //             if (vis[u]) continue;
// // // //             vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
// // // //             for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
// // // //         }
// // // //         lastAlgo = PRIMS;
// // // //     }

// // // //     void kruskalMST(int n) {
// // // //         sourceNode = -1; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // // //         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
// // // //         DSU ds(n);
// // // //         for(auto e : edges) if(ds.unionByRank(e.u, e.v)) { anim_nodes.push_back(e.u); anim_nodes.push_back(e.v); anim_edges.push_back({e.u, e.v}); }
// // // //         lastAlgo = KRUSKAL;
// // // //     }

// // // //     void bellman_ford(int n, int src) {
// // // //         sourceNode = src; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<int> dist(n, 1e9); dist[src] = 0; anim_nodes.push_back(src);
// // // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // // //         for (int i = 0; i < n - 1; i++) for (auto e : edges) if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; anim_edges.push_back({e.u, e.v}); }
// // // //         lastAlgo = BELLMAN_FORD;
// // // //     }

// // // //     void floyd_warshall(int n) {
// // // //         sourceNode = -1; destNode = -1;
// // // //         anim_nodes.clear(); anim_edges.clear();
// // // //         vector<vector<int>> matrix(n, vector<int>(n, 1e9));
// // // //         for(int i=0; i<n; i++) matrix[i][i] = 0;
// // // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) matrix[p.first][nbr.first] = nbr.second;
// // // //         for(int k = 0; k < n; k++) {
// // // //             anim_nodes.push_back(k); 
// // // //             for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(matrix[i][k] != 1e9 && matrix[k][j] != 1e9) matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
// // // //         }
// // // //         lastAlgo = FLOYD;
// // // //     }
// // // // };

// // // // #endif
// // // //
// // // #ifndef GRAPH_H
// // // #define GRAPH_H

// // // #include <iostream>
// // // #include <unordered_map>
// // // #include <list>
// // // #include <vector>
// // // #include <queue>
// // // #include <stack>
// // // #include <set>
// // // #include <algorithm>
// // // #include <climits>

// // // using namespace std;

// // // enum AlgoType { 
// // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // };

// // // class DSU {
// // //     vector<int> parent, rank;
// // // public:
// // //     DSU(int n) {
// // //         parent.resize(n); rank.resize(n, 0);
// // //         for(int i = 0; i < n; i++) parent[i] = i;
// // //     }
// // //     int findUPar(int node) {
// // //         if(node == parent[node]) return node;
// // //         return parent[node] = findUPar(parent[node]); 
// // //     }
// // //     bool unionByRank(int u, int v) {
// // //         int ulp_u = findUPar(u), ulp_v = findUPar(v);
// // //         if(ulp_u == ulp_v) return false; 
// // //         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
// // //         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
// // //         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
// // //         return true; 
// // //     }
// // // };

// // // class UnweightedGraph {
// // // public:
// // //     unordered_map<int, list<int>> adjlist;
// // //     AlgoType lastAlgo = NONE;
// // //     vector<int> anim_nodes;
// // //     vector<pair<int, int>> anim_edges;
// // //     int sourceNode = -1; 
// // //     int destNode = -1;   

// // //     void add_edge(int u, int v, bool direction) {
// // //         adjlist[u].push_back(v);
// // //         if (!direction) adjlist[v].push_back(u);
// // //     }

// // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // //         sourceNode = startNode; destNode = targetNode;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> parent(n, -1); vector<bool> vis(n, false); queue<int> q;
// // //         q.push(startNode); vis[startNode] = true;
// // //         while(!q.empty()){
// // //             int u = q.front(); q.pop();
// // //             if(u == targetNode) break;
// // //             for(int v : adjlist[u]){
// // //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// // //             }
// // //         }
// // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // //             anim_nodes.push_back(v);
// // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // //         }
// // //         // 🔥 YE HAI FIX: Nodes aur Edges dono ko reverse karna zaroori hai
// // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // //         reverse(anim_edges.begin(), anim_edges.end());
// // //         lastAlgo = BFS;
// // //     }

// // //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// // //         vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
// // //         for (int v : adjlist[u]) {
// // //             if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
// // //             else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
// // //         }
// // //         dfsvis[u] = false; return false;
// // //     }

// // //     void detect_cycle_dfs(int n) {
// // //         sourceNode = -1; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<bool> vis(n, false), dfsvis(n, false);
// // //         for(int i=0; i<n; i++) if(!vis[i] && dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// // //         lastAlgo = DFS;
// // //     }

// // //     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
// // //         vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
// // //         for (int v : adjlist[u]) {
// // //             if (v == p) continue;
// // //             if (vis[v]) low[u] = min(low[u], tin[v]);
// // //             else {
// // //                 findBridgesHelper(v, u, tin, low, timer, vis);
// // //                 low[u] = min(low[u], low[v]);
// // //                 if (low[v] > tin[u]) anim_edges.push_back({u, v});
// // //             }
// // //         }
// // //     }

// // //     void find_bridges(int n) {
// // //         sourceNode = -1; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false);
// // //         int timer = 0;
// // //         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
// // //         lastAlgo = BRIDGES;
// // //     }

// // //     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
// // //         vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
// // //     }
// // //     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
// // //         vis[u] = true; anim_nodes.push_back(u); 
// // //         for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
// // //     }
// // //     void getSCC(int n) {
// // //         sourceNode = -1; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<bool> vis(n, false); stack<int> st;
// // //         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
        
// // //         unordered_map<int, list<int>> revAdj;
// // //         for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
        
// // //         fill(vis.begin(), vis.end(), false);
// // //         while(!st.empty()) {
// // //             int node = st.top(); st.pop();
// // //             if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); }
// // //         }
// // //         lastAlgo = SCC;
// // //     }
// // // };

// // // class WeightedGraph {
// // // public:
// // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // //     AlgoType lastAlgo = NONE;
// // //     vector<int> anim_nodes;
// // //     vector<pair<int, int>> anim_edges;
// // //     int lastCalculatedDistance = -1;
// // //     int sourceNode = -1; 
// // //     int destNode = -1;   

// // //     void add_edge(int u, int v, int wt, bool direction) {
// // //         adjlist[u].push_back({v, wt});
// // //         if (!direction) adjlist[v].push_back({u, wt});
// // //     }

// // //     void dijkstra(int n, int src, int dest) {
// // //         sourceNode = src; destNode = dest;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> dist(n, INT_MAX); vector<int> parent(n, -1);
// // //         set<pair<int, int>> st;
// // //         dist[src] = 0; st.insert({0, src});
// // //         while(!st.empty()){
// // //             auto top = *(st.begin()); st.erase(st.begin());
// // //             int u = top.second; int d = top.first;
// // //             for(auto nbr : adjlist[u]){
// // //                 if(d + nbr.second < dist[nbr.first]){
// // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // //                     dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // //                 }
// // //             }
// // //         }
// // //         for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// // //         // 🔥 YE HAI FIX: Nodes aur Edges dono ko reverse karna zaroori hai
// // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // //         reverse(anim_edges.begin(), anim_edges.end());
// // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == INT_MAX) ? -1 : dist[dest];
// // //     }

// // //     void toposort_bfs(int n) {
// // //         sourceNode = -1; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> indegree(n, 0);
// // //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// // //         queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // //         int count = 0;
// // //         while (!q.empty()) {
// // //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// // //             for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
// // //         }
// // //         if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } 
// // //         else lastAlgo = TOPOSORT_BFS;
// // //     }

// // //     void primsMST(int n, int src) {
// // //         sourceNode = src; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
// // //         vector<bool> vis(n, false); pq.push({0, {src, -1}});
// // //         while (!pq.empty()) {
// // //             auto it = pq.top(); pq.pop();
// // //             int u = it.second.first, p = it.second.second;
// // //             if (vis[u]) continue;
// // //             vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
// // //             for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
// // //         }
// // //         lastAlgo = PRIMS;
// // //     }

// // //     void kruskalMST(int n) {
// // //         sourceNode = -1; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // //         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
// // //         DSU ds(n);
// // //         for(auto e : edges) if(ds.unionByRank(e.u, e.v)) { anim_nodes.push_back(e.u); anim_nodes.push_back(e.v); anim_edges.push_back({e.u, e.v}); }
// // //         lastAlgo = KRUSKAL;
// // //     }

// // //     void bellman_ford(int n, int src) {
// // //         sourceNode = src; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> dist(n, 1e9); dist[src] = 0; anim_nodes.push_back(src);
// // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // //         for (int i = 0; i < n - 1; i++) for (auto e : edges) if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; anim_edges.push_back({e.u, e.v}); }
// // //         lastAlgo = BELLMAN_FORD;
// // //     }

// // //     void floyd_warshall(int n) {
// // //         sourceNode = -1; destNode = -1;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<vector<int>> matrix(n, vector<int>(n, 1e9));
// // //         for(int i=0; i<n; i++) matrix[i][i] = 0;
// // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) matrix[p.first][nbr.first] = nbr.second;
// // //         for(int k = 0; k < n; k++) {
// // //             anim_nodes.push_back(k); 
// // //             for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(matrix[i][k] != 1e9 && matrix[k][j] != 1e9) matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
// // //         }
// // //         lastAlgo = FLOYD;
// // //     }
// // // };

// // // #endif
// // // //


// // // #ifndef GRAPH_H
// // // #define GRAPH_H

// // // #include <iostream>
// // // #include <unordered_map>
// // // #include <list>
// // // #include <vector>
// // // #include <queue>
// // // #include <stack>
// // // #include <set>
// // // #include <algorithm>
// // // #include <climits>

// // // using namespace std;

// // // enum AlgoType { 
// // //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // // };

// // // class DSU {
// // //     vector<int> parent, rank;
// // // public:
// // //     DSU(int n) {
// // //         parent.resize(n); rank.resize(n, 0);
// // //         for(int i = 0; i < n; i++) parent[i] = i;
// // //     }
// // //     int findUPar(int node) {
// // //         if(node == parent[node]) return node;
// // //         return parent[node] = findUPar(parent[node]); 
// // //     }
// // //     bool unionByRank(int u, int v) {
// // //         int ulp_u = findUPar(u), ulp_v = findUPar(v);
// // //         if(ulp_u == ulp_v) return false; 
// // //         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
// // //         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
// // //         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
// // //         return true; 
// // //     }
// // // };

// // // class UnweightedGraph {
// // // public:
// // //     unordered_map<int, list<int>> adjlist;
// // //     AlgoType lastAlgo = NONE;
// // //     vector<int> anim_nodes;
// // //     vector<pair<int, int>> anim_edges;
// // //     int sourceNode = -1; 
// // //     int destNode = -1;   

// // //     void add_edge(int u, int v, bool direction) {
// // //         adjlist[u].push_back(v);
// // //         if (!direction) adjlist[v].push_back(u);
// // //     }

// // //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// // //         sourceNode = startNode; destNode = targetNode;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> parent(n, -1); vector<bool> vis(n, false); queue<int> q;
// // //         q.push(startNode); vis[startNode] = true;
// // //         while(!q.empty()){
// // //             int u = q.front(); q.pop();
// // //             if(u == targetNode) break;
// // //             for(int v : adjlist[u]){
// // //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// // //             }
// // //         }
// // //         for(int v = targetNode; v != -1; v = parent[v]) {
// // //             anim_nodes.push_back(v);
// // //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// // //         }
// // //         reverse(anim_nodes.begin(), anim_nodes.end());
// // //         reverse(anim_edges.begin(), anim_edges.end());
// // //         lastAlgo = BFS;
// // //     }

// // //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// // //         vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
// // //         for (int v : adjlist[u]) {
// // //             if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
// // //             else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
// // //         }
// // //         dfsvis[u] = false; return false;
// // //     }

// // //     void detect_cycle_dfs(int n) {
// // //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// // //         vector<bool> vis(n, false), dfsvis(n, false);
// // //         for(int i=0; i<n; i++) if(!vis[i] && dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// // //         lastAlgo = DFS;
// // //     }

// // //     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
// // //         vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
// // //         for (int v : adjlist[u]) {
// // //             if (v == p) continue;
// // //             if (vis[v]) low[u] = min(low[u], tin[v]);
// // //             else { findBridgesHelper(v, u, tin, low, timer, vis); low[u] = min(low[u], low[v]); if (low[v] > tin[u]) anim_edges.push_back({u, v}); }
// // //         }
// // //     }

// // //     void find_bridges(int n) {
// // //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false); int timer = 0;
// // //         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
// // //         lastAlgo = BRIDGES;
// // //     }

// // //     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
// // //         vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
// // //     }
// // //     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
// // //         vis[u] = true; anim_nodes.push_back(u); 
// // //         for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
// // //     }
// // //     void getSCC(int n) {
// // //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// // //         vector<bool> vis(n, false); stack<int> st;
// // //         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
// // //         unordered_map<int, list<int>> revAdj;
// // //         for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
// // //         fill(vis.begin(), vis.end(), false);
// // //         while(!st.empty()) { int node = st.top(); st.pop(); if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); } }
// // //         lastAlgo = SCC;
// // //     }
// // // };

// // // class WeightedGraph {
// // // public:
// // //     unordered_map<int, list<pair<int, int>>> adjlist;
// // //     AlgoType lastAlgo = NONE;
// // //     vector<int> anim_nodes;
// // //     vector<pair<int, int>> anim_edges;
// // //     int lastCalculatedDistance = -1;
// // //     int sourceNode = -1; 
// // //     int destNode = -1;   

// // //     void add_edge(int u, int v, int wt, bool direction) {
// // //         adjlist[u].push_back({v, wt}); if (!direction) adjlist[v].push_back({u, wt});
// // //     }

// // //     void dijkstra(int n, int src, int dest) {
// // //         sourceNode = src; destNode = dest;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> dist(n, 1e9); vector<int> parent(n, -1);
// // //         set<pair<int, int>> st;
// // //         dist[src] = 0; st.insert({0, src});
// // //         while(!st.empty()){
// // //             auto top = *(st.begin()); st.erase(st.begin());
// // //             int u = top.second; int d = top.first;
// // //             for(auto nbr : adjlist[u]){
// // //                 if(d + nbr.second < dist[nbr.first]){
// // //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// // //                     dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// // //                 }
// // //             }
// // //         }
// // //         if(dist[dest] != 1e9) {
// // //             for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// // //             reverse(anim_nodes.begin(), anim_nodes.end());
// // //             reverse(anim_edges.begin(), anim_edges.end());
// // //         }
// // //         lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
// // //     }

// // //     void bellman_ford(int n, int src, int dest) {
// // //         sourceNode = src; destNode = dest;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> dist(n, 1e9); vector<int> parent(n, -1); dist[src] = 0; 
// // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // //         for (int i = 0; i < n - 1; i++) {
// // //             for (auto e : edges) {
// // //                 if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; parent[e.v] = e.u; }
// // //             }
// // //         }
// // //         if (dist[dest] != 1e9) {
// // //             for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// // //             reverse(anim_nodes.begin(), anim_nodes.end());
// // //             reverse(anim_edges.begin(), anim_edges.end());
// // //         }
// // //         lastAlgo = BELLMAN_FORD; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
// // //     }

// // //     void floyd_warshall(int n, int src, int dest) {
// // //         sourceNode = src; destNode = dest;
// // //         anim_nodes.clear(); anim_edges.clear();
// // //         vector<vector<int>> dist(n, vector<int>(n, 1e9));
// // //         vector<vector<int>> nextNode(n, vector<int>(n, -1));
// // //         for(int i=0; i<n; i++) { dist[i][i] = 0; nextNode[i][i] = i; }
// // //         for(auto const& p : adjlist) { for(auto const& nbr : p.second) { dist[p.first][nbr.first] = nbr.second; nextNode[p.first][nbr.first] = nbr.first; } }
// // //         for(int k = 0; k < n; k++) {
// // //             for(int i = 0; i < n; i++) {
// // //                 for(int j = 0; j < n; j++) {
// // //                     if(dist[i][k] != 1e9 && dist[k][j] != 1e9 && dist[i][k] + dist[k][j] < dist[i][j]) { dist[i][j] = dist[i][k] + dist[k][j]; nextNode[i][j] = nextNode[i][k]; }
// // //                 }
// // //             }
// // //         }
// // //         if (dist[src][dest] != 1e9) {
// // //             int u = src; anim_nodes.push_back(u);
// // //             while (u != dest) { int v = nextNode[u][dest]; anim_edges.push_back({u, v}); anim_nodes.push_back(v); u = v; }
// // //         }
// // //         lastAlgo = FLOYD; lastCalculatedDistance = (dist[src][dest] == 1e9) ? -1 : dist[src][dest];
// // //     }

// // //     void toposort_bfs(int n) {
// // //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// // //         vector<int> indegree(n, 0);
// // //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// // //         queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// // //         int count = 0;
// // //         while (!q.empty()) {
// // //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// // //             for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
// // //         }
// // //         if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } else lastAlgo = TOPOSORT_BFS;
// // //     }

// // //     void primsMST(int n, int src) {
// // //         sourceNode = src; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// // //         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
// // //         vector<bool> vis(n, false); pq.push({0, {src, -1}});
// // //         while (!pq.empty()) {
// // //             auto it = pq.top(); pq.pop();
// // //             int u = it.second.first, p = it.second.second;
// // //             if (vis[u]) continue;
// // //             vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
// // //             for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
// // //         }
// // //         lastAlgo = PRIMS;
// // //     }

// // //     void kruskalMST(int n) {
// // //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// // //         struct Edge { int u, v, w; }; vector<Edge> edges;
// // //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// // //         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
// // //         DSU ds(n);
// // //         for(auto e : edges) if(ds.unionByRank(e.u, e.v)) { anim_nodes.push_back(e.u); anim_nodes.push_back(e.v); anim_edges.push_back({e.u, e.v}); }
// // //         lastAlgo = KRUSKAL;
// // //     }
// // // };

// // // #endif
// // //
// // #ifndef GRAPH_H
// // #define GRAPH_H

// // #include <iostream>
// // #include <unordered_map>
// // #include <list>
// // #include <vector>
// // #include <queue>
// // #include <stack>
// // #include <set>
// // #include <algorithm>
// // #include <climits>

// // using namespace std;

// // enum AlgoType { 
// //     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// // };

// // class DSU {
// //     vector<int> parent, rank;
// // public:
// //     DSU(int n) {
// //         parent.resize(n); rank.resize(n, 0);
// //         for(int i = 0; i < n; i++) parent[i] = i;
// //     }
// //     int findUPar(int node) {
// //         if(node == parent[node]) return node;
// //         return parent[node] = findUPar(parent[node]); 
// //     }
// //     bool unionByRank(int u, int v) {
// //         int ulp_u = findUPar(u), ulp_v = findUPar(v);
// //         if(ulp_u == ulp_v) return false; 
// //         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
// //         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
// //         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
// //         return true; 
// //     }
// // };

// // class UnweightedGraph {
// // public:
// //     unordered_map<int, list<int>> adjlist;
// //     AlgoType lastAlgo = NONE;
// //     vector<int> anim_nodes;
// //     vector<pair<int, int>> anim_edges;
// //     int sourceNode = -1; 
// //     int destNode = -1;   

// //     void add_edge(int u, int v, bool direction) {
// //         adjlist[u].push_back(v);
// //         if (!direction) adjlist[v].push_back(u);
// //     }

// //     void bfs_shortest_path(int startNode, int targetNode, int n) {
// //         sourceNode = startNode; destNode = targetNode;
// //         anim_nodes.clear(); anim_edges.clear();
// //         vector<int> parent(n, -1); vector<bool> vis(n, false); queue<int> q;
// //         q.push(startNode); vis[startNode] = true;
// //         while(!q.empty()){
// //             int u = q.front(); q.pop();
// //             if(u == targetNode) break;
// //             for(int v : adjlist[u]){
// //                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
// //             }
// //         }
// //         for(int v = targetNode; v != -1; v = parent[v]) {
// //             anim_nodes.push_back(v);
// //             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
// //         }
// //         reverse(anim_nodes.begin(), anim_nodes.end());
// //         reverse(anim_edges.begin(), anim_edges.end());
// //         lastAlgo = BFS;
// //     }

// //     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
// //         vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
// //         for (int v : adjlist[u]) {
// //             if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
// //             else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
// //         }
// //         dfsvis[u] = false; return false;
// //     }

// //     void detect_cycle_dfs(int n) {
// //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// //         vector<bool> vis(n, false), dfsvis(n, false);
// //         for(int i=0; i<n; i++) if(!vis[i] && dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
// //         lastAlgo = DFS;
// //     }

// //     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
// //         vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
// //         for (int v : adjlist[u]) {
// //             if (v == p) continue;
// //             if (vis[v]) low[u] = min(low[u], tin[v]);
// //             else { findBridgesHelper(v, u, tin, low, timer, vis); low[u] = min(low[u], low[v]); if (low[v] > tin[u]) anim_edges.push_back({u, v}); }
// //         }
// //     }

// //     void find_bridges(int n) {
// //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// //         vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false); int timer = 0;
// //         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
// //         lastAlgo = BRIDGES;
// //     }

// //     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
// //         vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
// //     }
// //     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
// //         vis[u] = true; anim_nodes.push_back(u); 
// //         for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
// //     }
// //     void getSCC(int n) {
// //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// //         vector<bool> vis(n, false); stack<int> st;
// //         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
// //         unordered_map<int, list<int>> revAdj;
// //         for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
// //         fill(vis.begin(), vis.end(), false);
// //         while(!st.empty()) { int node = st.top(); st.pop(); if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); } }
// //         lastAlgo = SCC;
// //     }
// // };

// // class WeightedGraph {
// // public:
// //     unordered_map<int, list<pair<int, int>>> adjlist;
// //     AlgoType lastAlgo = NONE;
// //     vector<int> anim_nodes;
// //     vector<pair<int, int>> anim_edges;
// //     int lastCalculatedDistance = -1;
// //     int sourceNode = -1; 
// //     int destNode = -1;   

// //     void add_edge(int u, int v, int wt, bool direction) {
// //         adjlist[u].push_back({v, wt}); if (!direction) adjlist[v].push_back({u, wt});
// //     }

// //     void dijkstra(int n, int src, int dest) {
// //         sourceNode = src; destNode = dest;
// //         anim_nodes.clear(); anim_edges.clear();
// //         vector<int> dist(n, 1e9); vector<int> parent(n, -1);
// //         set<pair<int, int>> st;
// //         dist[src] = 0; st.insert({0, src});
// //         while(!st.empty()){
// //             auto top = *(st.begin()); st.erase(st.begin());
// //             int u = top.second; int d = top.first;
// //             for(auto nbr : adjlist[u]){
// //                 if(d + nbr.second < dist[nbr.first]){
// //                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
// //                     dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
// //                 }
// //             }
// //         }
// //         if(dist[dest] != 1e9) {
// //             for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// //             reverse(anim_nodes.begin(), anim_nodes.end());
// //             reverse(anim_edges.begin(), anim_edges.end());
// //         }
// //         lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
// //     }

// //     void bellman_ford(int n, int src, int dest) {
// //         sourceNode = src; destNode = dest;
// //         anim_nodes.clear(); anim_edges.clear();
// //         vector<int> dist(n, 1e9); vector<int> parent(n, -1); dist[src] = 0; 
// //         struct Edge { int u, v, w; }; vector<Edge> edges;
// //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// //         for (int i = 0; i < n - 1; i++) {
// //             for (auto e : edges) {
// //                 if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; parent[e.v] = e.u; }
// //             }
// //         }
// //         if (dist[dest] != 1e9) {
// //             for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
// //             reverse(anim_nodes.begin(), anim_nodes.end());
// //             reverse(anim_edges.begin(), anim_edges.end());
// //         }
// //         lastAlgo = BELLMAN_FORD; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
// //     }

// //     void floyd_warshall(int n, int src, int dest) {
// //         sourceNode = src; destNode = dest;
// //         anim_nodes.clear(); anim_edges.clear();
// //         vector<vector<int>> dist(n, vector<int>(n, 1e9));
// //         vector<vector<int>> nextNode(n, vector<int>(n, -1));
// //         for(int i=0; i<n; i++) { dist[i][i] = 0; nextNode[i][i] = i; }
// //         for(auto const& p : adjlist) { for(auto const& nbr : p.second) { dist[p.first][nbr.first] = nbr.second; nextNode[p.first][nbr.first] = nbr.first; } }
// //         for(int k = 0; k < n; k++) {
// //             for(int i = 0; i < n; i++) {
// //                 for(int j = 0; j < n; j++) {
// //                     if(dist[i][k] != 1e9 && dist[k][j] != 1e9 && dist[i][k] + dist[k][j] < dist[i][j]) { dist[i][j] = dist[i][k] + dist[k][j]; nextNode[i][j] = nextNode[i][k]; }
// //                 }
// //             }
// //         }
// //         if (dist[src][dest] != 1e9) {
// //             int u = src; anim_nodes.push_back(u);
// //             while (u != dest) { int v = nextNode[u][dest]; anim_edges.push_back({u, v}); anim_nodes.push_back(v); u = v; }
// //         }
// //         lastAlgo = FLOYD; lastCalculatedDistance = (dist[src][dest] == 1e9) ? -1 : dist[src][dest];
// //     }

// //     void toposort_bfs(int n) {
// //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// //         vector<int> indegree(n, 0);
// //         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
// //         queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
// //         int count = 0;
// //         while (!q.empty()) {
// //             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
// //             for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
// //         }
// //         if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } else lastAlgo = TOPOSORT_BFS;
// //     }

// //     void primsMST(int n, int src) {
// //         sourceNode = src; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// //         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
// //         vector<bool> vis(n, false); pq.push({0, {src, -1}});
// //         while (!pq.empty()) {
// //             auto it = pq.top(); pq.pop();
// //             int u = it.second.first, p = it.second.second;
// //             if (vis[u]) continue;
// //             vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
// //             for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
// //         }
// //         lastAlgo = PRIMS;
// //     }

// //     // 🔥 KRUSKAL FIX ADDED HERE
// //     void kruskalMST(int n) {
// //         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
// //         struct Edge { int u, v, w; }; vector<Edge> edges;
// //         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
// //         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
// //         DSU ds(n);
// //         vector<bool> nodeAdded(n, false); // Fix for duplicate nodes
// //         for(auto e : edges) {
// //             if(ds.unionByRank(e.u, e.v)) { 
// //                 if(!nodeAdded[e.u]) { anim_nodes.push_back(e.u); nodeAdded[e.u] = true; }
// //                 if(!nodeAdded[e.v]) { anim_nodes.push_back(e.v); nodeAdded[e.v] = true; }
// //                 anim_edges.push_back({e.u, e.v}); 
// //             }
// //         }
// //         lastAlgo = KRUSKAL;
// //     }
// // };

// // #endif

// #ifndef GRAPH_H
// #define GRAPH_H

// #include <iostream>
// #include <unordered_map>
// #include <list>
// #include <vector>
// #include <queue>
// #include <stack>
// #include <set>
// #include <algorithm>
// #include <climits>

// using namespace std;

// enum AlgoType { 
//     NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
// };

// class DSU {
//     vector<int> parent, rank;
// public:
//     DSU(int n) {
//         parent.resize(n); rank.resize(n, 0);
//         for(int i = 0; i < n; i++) parent[i] = i;
//     }
//     int findUPar(int node) {
//         if(node == parent[node]) return node;
//         return parent[node] = findUPar(parent[node]); 
//     }
//     bool unionByRank(int u, int v) {
//         int ulp_u = findUPar(u), ulp_v = findUPar(v);
//         if(ulp_u == ulp_v) return false; 
//         if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
//         else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
//         else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
//         return true; 
//     }
// };

// class UnweightedGraph {
// public:
//     unordered_map<int, list<int>> adjlist;
//     AlgoType lastAlgo = NONE;
//     vector<int> anim_nodes;
//     vector<pair<int, int>> anim_edges;
//     int sourceNode = -1; 
//     int destNode = -1;   

//     void add_edge(int u, int v, bool direction) {
//         adjlist[u].push_back(v);
//         if (!direction) adjlist[v].push_back(u);
//     }

//     void bfs_shortest_path(int startNode, int targetNode, int n) {
//         sourceNode = startNode; destNode = targetNode;
//         anim_nodes.clear(); anim_edges.clear();
//         vector<int> parent(n, -1); vector<bool> vis(n, false); queue<int> q;
//         q.push(startNode); vis[startNode] = true;
//         while(!q.empty()){
//             int u = q.front(); q.pop();
//             if(u == targetNode) break;
//             for(int v : adjlist[u]){
//                 if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
//             }
//         }
//         for(int v = targetNode; v != -1; v = parent[v]) {
//             anim_nodes.push_back(v);
//             if(parent[v] != -1) anim_edges.push_back({parent[v], v});
//         }
//         reverse(anim_nodes.begin(), anim_nodes.end());
//         reverse(anim_edges.begin(), anim_edges.end());
//         lastAlgo = BFS;
//     }

//     bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
//         vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
//         for (int v : adjlist[u]) {
//             if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
//             else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
//         }
//         dfsvis[u] = false; return false;
//     }

//     void detect_cycle_dfs(int n) {
//         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
//         vector<bool> vis(n, false), dfsvis(n, false);
//         for(int i=0; i<n; i++) if(!vis[i] && dfs_cycle_helper(i, vis, dfsvis)) { lastAlgo = CYCLE_DETECTED; return; }
//         lastAlgo = DFS;
//     }

//     void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
//         vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
//         for (int v : adjlist[u]) {
//             if (v == p) continue;
//             if (vis[v]) low[u] = min(low[u], tin[v]);
//             else { findBridgesHelper(v, u, tin, low, timer, vis); low[u] = min(low[u], low[v]); if (low[v] > tin[u]) anim_edges.push_back({u, v}); }
//         }
//     }

//     void find_bridges(int n) {
//         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
//         vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false); int timer = 0;
//         for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
//         lastAlgo = BRIDGES;
//     }

//     void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
//         vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
//     }
//     void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
//         vis[u] = true; anim_nodes.push_back(u); 
//         for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
//     }
//     void getSCC(int n) {
//         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
//         vector<bool> vis(n, false); stack<int> st;
//         for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
//         unordered_map<int, list<int>> revAdj;
//         for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
//         fill(vis.begin(), vis.end(), false);
//         while(!st.empty()) { int node = st.top(); st.pop(); if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); } }
//         lastAlgo = SCC;
//     }
// };

// class WeightedGraph {
// public:
//     unordered_map<int, list<pair<int, int>>> adjlist;
//     AlgoType lastAlgo = NONE;
//     vector<int> anim_nodes;
//     vector<pair<int, int>> anim_edges;
//     int lastCalculatedDistance = -1;
//     int sourceNode = -1; 
//     int destNode = -1;   

//     void add_edge(int u, int v, int wt, bool direction) {
//         adjlist[u].push_back({v, wt}); if (!direction) adjlist[v].push_back({u, wt});
//     }

//     void dijkstra(int n, int src, int dest) {
//         sourceNode = src; destNode = dest;
//         anim_nodes.clear(); anim_edges.clear();
//         vector<int> dist(n, 1e9); vector<int> parent(n, -1);
//         set<pair<int, int>> st;
//         dist[src] = 0; st.insert({0, src});
//         while(!st.empty()){
//             auto top = *(st.begin()); st.erase(st.begin());
//             int u = top.second; int d = top.first;
//             for(auto nbr : adjlist[u]){
//                 if(d + nbr.second < dist[nbr.first]){
//                     if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
//                     dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
//                 }
//             }
//         }
//         if(dist[dest] != 1e9) {
//             for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
//             reverse(anim_nodes.begin(), anim_nodes.end());
//             reverse(anim_edges.begin(), anim_edges.end());
//         }
//         lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
//     }

//     void bellman_ford(int n, int src, int dest) {
//         sourceNode = src; destNode = dest;
//         anim_nodes.clear(); anim_edges.clear();
//         vector<int> dist(n, 1e9); vector<int> parent(n, -1); dist[src] = 0; 
//         struct Edge { int u, v, w; }; vector<Edge> edges;
//         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
//         for (int i = 0; i < n - 1; i++) {
//             for (auto e : edges) {
//                 if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; parent[e.v] = e.u; }
//             }
//         }
//         if (dist[dest] != 1e9) {
//             for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
//             reverse(anim_nodes.begin(), anim_nodes.end());
//             reverse(anim_edges.begin(), anim_edges.end());
//         }
//         lastAlgo = BELLMAN_FORD; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
//     }

//     void floyd_warshall(int n, int src, int dest) {
//         sourceNode = src; destNode = dest;
//         anim_nodes.clear(); anim_edges.clear();
//         vector<vector<int>> dist(n, vector<int>(n, 1e9));
//         vector<vector<int>> nextNode(n, vector<int>(n, -1));
//         for(int i=0; i<n; i++) { dist[i][i] = 0; nextNode[i][i] = i; }
//         for(auto const& p : adjlist) { for(auto const& nbr : p.second) { dist[p.first][nbr.first] = nbr.second; nextNode[p.first][nbr.first] = nbr.first; } }
//         for(int k = 0; k < n; k++) {
//             for(int i = 0; i < n; i++) {
//                 for(int j = 0; j < n; j++) {
//                     if(dist[i][k] != 1e9 && dist[k][j] != 1e9 && dist[i][k] + dist[k][j] < dist[i][j]) { dist[i][j] = dist[i][k] + dist[k][j]; nextNode[i][j] = nextNode[i][k]; }
//                 }
//             }
//         }
//         if (dist[src][dest] != 1e9) {
//             int u = src; anim_nodes.push_back(u);
//             while (u != dest) { int v = nextNode[u][dest]; anim_edges.push_back({u, v}); anim_nodes.push_back(v); u = v; }
//         }
//         lastAlgo = FLOYD; lastCalculatedDistance = (dist[src][dest] == 1e9) ? -1 : dist[src][dest];
//     }

//     void toposort_bfs(int n) {
//         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
//         vector<int> indegree(n, 0);
//         for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
//         queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
//         int count = 0;
//         while (!q.empty()) {
//             int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
//             for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
//         }
//         if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } else lastAlgo = TOPOSORT_BFS;
//     }

//     void primsMST(int n, int src) {
//         sourceNode = src; destNode = -1; anim_nodes.clear(); anim_edges.clear();
//         priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
//         vector<bool> vis(n, false); pq.push({0, {src, -1}});
//         while (!pq.empty()) {
//             auto it = pq.top(); pq.pop();
//             int u = it.second.first, p = it.second.second;
//             if (vis[u]) continue;
//             vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
//             for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
//         }
//         lastAlgo = PRIMS;
//     }

//     // 🔥 KRUSKAL FIX ADDED HERE
//     void kruskalMST(int n) {
//         sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
//         struct Edge { int u, v, w; }; vector<Edge> edges;
//         for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
//         sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
//         DSU ds(n);
//         vector<bool> nodeAdded(n, false); // Fix for duplicate nodes
//         for(auto e : edges) {
//             if(ds.unionByRank(e.u, e.v)) { 
//                 if(!nodeAdded[e.u]) { anim_nodes.push_back(e.u); nodeAdded[e.u] = true; }
//                 if(!nodeAdded[e.v]) { anim_nodes.push_back(e.v); nodeAdded[e.v] = true; }
//                 anim_edges.push_back({e.u, e.v}); 
//             }
//         }
//         lastAlgo = KRUSKAL;
//     }
// };

// #endif

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

enum AlgoType { 
    NONE, BFS, DFS, TOPOSORT_BFS, DIJKSTRA, PRIMS, KRUSKAL, SCC, BRIDGES, FLOYD, BELLMAN_FORD, CYCLE_DETECTED 
};

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n); rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if(node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]); 
    }
    bool unionByRank(int u, int v) {
        int ulp_u = findUPar(u), ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return false; 
        if(rank[ulp_u] < rank[ulp_v]) parent[ulp_u] = ulp_v;
        else if(rank[ulp_v] < rank[ulp_u]) parent[ulp_v] = ulp_u;
        else { parent[ulp_v] = ulp_u; rank[ulp_u]++; }
        return true; 
    }
};

class UnweightedGraph {
public:
    unordered_map<int, list<int>> adjlist;
    AlgoType lastAlgo = NONE;
    vector<int> anim_nodes;
    vector<pair<int, int>> anim_edges;
    int sourceNode = -1; 
    int destNode = -1;   

    void add_edge(int u, int v, bool direction) {
        adjlist[u].push_back(v);
        if (!direction) adjlist[v].push_back(u);
    }
//
// UnweightedGraph class ke andar ye traversals replace karo:

// void bfs_traversal_disconnected(int n) {
//     sourceNode = -1; destNode = -1;
//     anim_nodes.clear(); anim_edges.clear();
//     vector<bool> vis(n, false);

//     for (int i = 0; i < n; i++) {
//         if (!vis[i]) {
//             queue<int> q;
//             q.push(i);
//             vis[i] = true;
//             while (!q.empty()) {
//                 int size = q.size();
//                 while (size--) {
//                     int u = q.front(); q.pop();
//                     anim_nodes.push_back(u);
//                     for (int v : adjlist[u]) {
//                         if (!vis[v]) {
//                             vis[v] = true;
//                             anim_edges.push_back({u, v});
//                             q.push(v);
//                         }
//                     }
//                 }
//                 anim_nodes.push_back(-2); // 🔥 Level Marker: Visualizer yahan rukega
//             }
//             anim_nodes.push_back(-3); // 🔥 Component Marker: Island change
//         }
//     }
//     lastAlgo = BFS;
// }

// Graph.h ke andar ye vector add karlo
vector<int> nodeLevels; // Har node ka level store karega

// void bfs_traversal_disconnected(int n) {
//     sourceNode = 0; destNode = -1;
//     anim_nodes.clear(); anim_edges.clear();
//     nodeLevels.assign(n, 0); // Reset levels
    
//     vector<bool> vis(n, false);
    
//     queue<int> q; q.push(0); vis[0] = true;
//     nodeLevels[0] = 0;

//     while(!q.empty()){
//         int u = q.front(); q.pop();
//         for(int v : adjlist[u]){
//             if(!vis[v]){
//                 vis[v] = true;
//                 nodeLevels[v] = nodeLevels[u] + 1; // Parent level + 1
//                 anim_edges.push_back({u, v});
//                 q.push(v);
//                 anim_nodes.push_back(v);
//             }
//         }
//         anim_nodes.push_back(-2); // Level marker
//     }
//     lastAlgo = BFS;
// }

//   void bfs_traversal_disconnected(int n) {
//     sourceNode = 0; destNode = -1;
//     anim_nodes.clear(); anim_edges.clear();
//     nodeLevels.assign(n, 0); // 🔥 Sabko 0 level pehle set karo
//     vector<bool> vis(n, false);
    
//     queue<int> q; q.push(0); vis[0] = true;
//     anim_nodes.push_back(0); 

//     while(!q.empty()){
//         int u = q.front(); q.pop();
//         for(int v : adjlist[u]){
//             if(!vis[v]){
//                 vis[v] = true;
//                 nodeLevels[v] = nodeLevels[u] + 1; // Parent + 1
//                 anim_edges.push_back({u, v});
//                 anim_nodes.push_back(v);
//                 q.push(v);
//             }
//         }
//         anim_nodes.push_back(-2); // Level Marker
//     }
//     lastAlgo = BFS;
// }
//
void bfs_traversal_disconnected(int n) {
        sourceNode = 0; destNode = -1; 
        anim_nodes.clear(); anim_edges.clear();
        nodeLevels.assign(n, 0); 
        vector<bool> vis(n, false);
        
        queue<int> q; q.push(0); vis[0] = true;
        anim_nodes.push_back(0); 

        while(!q.empty()){
            int size = q.size(); // 🔥 Ye size wala logic zaroori hai level count ke liye
            while (size--) {
                int u = q.front(); q.pop();
                for (int v : adjlist[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        nodeLevels[v] = nodeLevels[u] + 1; 
                        anim_edges.push_back({u, v});
                        anim_nodes.push_back(v);
                        q.push(v);
                    }
                }
            }
            anim_nodes.push_back(-2); // 🔥 Ab marker ek level complete hone par hi lagega
        }
        lastAlgo = BFS;
    }

 

    // 🔥 DFS for Disconnected Graph
    void dfs_traversal_disconnected(int n) {
        sourceNode = -1;
         destNode = -1;
        anim_nodes.clear(); anim_edges.clear();
        vector<bool> vis(n, false);

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs_traversal_helper(i, vis);
                anim_nodes.push_back(-3); // Component Break
            }
        }
        lastAlgo = DFS;
    }

    // ==========================================
    // 🔥 2. PURE DFS TRAVERSAL (Depth-Wise)
    // ==========================================
    void dfs_traversal_helper(int u, vector<bool>& vis) {
        vis[u] = true;
        anim_nodes.push_back(u); 
        
        for(int v : adjlist[u]) {
            if(!vis[v]) {
                anim_edges.push_back({u, v}); 
                dfs_traversal_helper(v, vis);
            }
        }
    }

    void dfs_traversal(int startNode, int n) {
        sourceNode = startNode; destNode = -1;
        anim_nodes.clear(); anim_edges.clear();
        
        vector<bool> vis(n, false);
        dfs_traversal_helper(startNode, vis); 
        
        lastAlgo = DFS;
    }

    // ==========================================
    // 3. BFS Shortest Path (Pehle wala)
    // ==========================================
    void bfs_shortest_path(int startNode, int targetNode, int n) {
        sourceNode = startNode; destNode = targetNode;
        anim_nodes.clear(); anim_edges.clear();
        vector<int> parent(n, -1); vector<bool> vis(n, false); queue<int> q;
        q.push(startNode); vis[startNode] = true;
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(u == targetNode) break;
            for(int v : adjlist[u]){
                if(!vis[v]){ vis[v] = true; parent[v] = u; q.push(v); }
            }
        }
        for(int v = targetNode; v != -1; v = parent[v]) {
            anim_nodes.push_back(v);
            if(parent[v] != -1) anim_edges.push_back({parent[v], v});
        }
        reverse(anim_nodes.begin(), anim_nodes.end());
        reverse(anim_edges.begin(), anim_edges.end());
        lastAlgo = BFS;
    }

    // ==========================================
    // 4. DFS Cycle Detection (Pehle wala)
    // ==========================================
    bool dfs_cycle_helper(int u, vector<bool>& vis, vector<bool>& dfsvis) {
        vis[u] = true; dfsvis[u] = true; anim_nodes.push_back(u);
        for (int v : adjlist[u]) {
            if (!vis[v]) { anim_edges.push_back({u, v}); if (dfs_cycle_helper(v, vis, dfsvis)) return true; } 
            else if (dfsvis[v]) { anim_edges.push_back({u, v}); return true; }
        }
        dfsvis[u] = false; return false;
    }

  
    //
    void detect_cycle_dfs(int n) {
    sourceNode = -1; 
    destNode = -1; // Cycle detection mein destination ka koi kaam nahi
    anim_nodes.clear(); 
    anim_edges.clear();
    
    vector<bool> vis(n, false), dfsvis(n, false);
    
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            // 🔥 Agle component ka pehla node hi uska SRC dikhna chahiye
            if(sourceNode == -1) sourceNode = i; 
            
            if(dfs_cycle_helper(i, vis, dfsvis)) { 
                lastAlgo = CYCLE_DETECTED; 
                return; 
            }
        }
    }
    lastAlgo = DFS;
}

    // ==========================================
    // 5. Tarjan's Find Bridges
    // ==========================================
    void findBridgesHelper(int u, int p, vector<int>& tin, vector<int>& low, int& timer, vector<bool>& vis) {
        vis[u] = true; tin[u] = low[u] = timer++; anim_nodes.push_back(u);
        for (int v : adjlist[u]) {
            if (v == p) continue;
            if (vis[v]) low[u] = min(low[u], tin[v]);
            else { findBridgesHelper(v, u, tin, low, timer, vis); low[u] = min(low[u], low[v]); if (low[v] > tin[u]) anim_edges.push_back({u, v}); }
        }
    }

    void find_bridges(int n) {
        sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
        vector<int> tin(n, -1), low(n, -1); vector<bool> vis(n, false); int timer = 0;
        for (int i = 0; i < n; i++) if (!vis[i]) findBridgesHelper(i, -1, tin, low, timer, vis);
        lastAlgo = BRIDGES;
    }

    // ==========================================
    // 6. Kosaraju's SCC
    // ==========================================
    void dfs_scc1(int u, vector<bool>& vis, stack<int>& st) {
        vis[u] = true; for(int v : adjlist[u]) if(!vis[v]) dfs_scc1(v, vis, st); st.push(u);
    }
    void dfs_scc2(int u, vector<bool>& vis, unordered_map<int, list<int>>& revAdj) {
        vis[u] = true; anim_nodes.push_back(u); 
        for(int v : revAdj[u]) if(!vis[v]) { anim_edges.push_back({u, v}); dfs_scc2(v, vis, revAdj); }
    }
    void getSCC(int n) {
        sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
        vector<bool> vis(n, false); stack<int> st;
        for(int i=0; i<n; i++) if(!vis[i]) dfs_scc1(i, vis, st);
        unordered_map<int, list<int>> revAdj;
        for(int i=0; i<n; i++) for(int v : adjlist[i]) revAdj[v].push_back(i);
        fill(vis.begin(), vis.end(), false);
        while(!st.empty()) { int node = st.top(); st.pop(); if(!vis[node]) { dfs_scc2(node, vis, revAdj); anim_nodes.push_back(-1); } }
        lastAlgo = SCC;
    }
};

class WeightedGraph {
public:
    unordered_map<int, list<pair<int, int>>> adjlist;
    AlgoType lastAlgo = NONE;
    vector<int> anim_nodes;
    vector<pair<int, int>> anim_edges;
    int lastCalculatedDistance = -1;
    int sourceNode = -1; 
    int destNode = -1;   

    void add_edge(int u, int v, int wt, bool direction) {
        adjlist[u].push_back({v, wt}); if (!direction) adjlist[v].push_back({u, wt});
    }

    void dijkstra(int n, int src, int dest) {
        sourceNode = src; destNode = dest;
        anim_nodes.clear(); anim_edges.clear();
        vector<int> dist(n, 1e9); vector<int> parent(n, -1);
        set<pair<int, int>> st;
        dist[src] = 0; st.insert({0, src});
        while(!st.empty()){
            auto top = *(st.begin()); st.erase(st.begin());
            int u = top.second; int d = top.first;
            for(auto nbr : adjlist[u]){
                if(d + nbr.second < dist[nbr.first]){
                    if(st.find({dist[nbr.first], nbr.first}) != st.end()) st.erase({dist[nbr.first], nbr.first});
                    dist[nbr.first] = d + nbr.second; parent[nbr.first] = u; st.insert({dist[nbr.first], nbr.first});
                }
            }
        }
        if(dist[dest] != 1e9) {
            for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
            reverse(anim_nodes.begin(), anim_nodes.end());
            reverse(anim_edges.begin(), anim_edges.end());
        }
        lastAlgo = DIJKSTRA; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
    }

    void bellman_ford(int n, int src, int dest) {
        sourceNode = src; destNode = dest;
        anim_nodes.clear(); anim_edges.clear();
        vector<int> dist(n, 1e9); vector<int> parent(n, -1); dist[src] = 0; 
        struct Edge { int u, v, w; }; vector<Edge> edges;
        for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
        for (int i = 0; i < n - 1; i++) {
            for (auto e : edges) {
                if (dist[e.u] != 1e9 && dist[e.u] + e.w < dist[e.v]) { dist[e.v] = dist[e.u] + e.w; parent[e.v] = e.u; }
            }
        }
        if (dist[dest] != 1e9) {
            for(int v = dest; v != -1; v = parent[v]) { anim_nodes.push_back(v); if(parent[v] != -1) anim_edges.push_back({parent[v], v}); }
            reverse(anim_nodes.begin(), anim_nodes.end());
            reverse(anim_edges.begin(), anim_edges.end());
        }
        lastAlgo = BELLMAN_FORD; lastCalculatedDistance = (dist[dest] == 1e9) ? -1 : dist[dest];
    }

    void floyd_warshall(int n, int src, int dest) {
        sourceNode = src; destNode = dest;
        anim_nodes.clear(); anim_edges.clear();
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        vector<vector<int>> nextNode(n, vector<int>(n, -1));
        for(int i=0; i<n; i++) { dist[i][i] = 0; nextNode[i][i] = i; }
        for(auto const& p : adjlist) { for(auto const& nbr : p.second) { dist[p.first][nbr.first] = nbr.second; nextNode[p.first][nbr.first] = nbr.first; } }
        for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(dist[i][k] != 1e9 && dist[k][j] != 1e9 && dist[i][k] + dist[k][j] < dist[i][j]) { dist[i][j] = dist[i][k] + dist[k][j]; nextNode[i][j] = nextNode[i][k]; }
                }
            }
        }
        if (dist[src][dest] != 1e9) {
            int u = src; anim_nodes.push_back(u);
            while (u != dest) { int v = nextNode[u][dest]; anim_edges.push_back({u, v}); anim_nodes.push_back(v); u = v; }
        }
        lastAlgo = FLOYD; lastCalculatedDistance = (dist[src][dest] == 1e9) ? -1 : dist[src][dest];
    }

    void toposort_bfs(int n) {
        sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
        vector<int> indegree(n, 0);
        for (auto const& p : adjlist) for (auto const& nbr : p.second) indegree[nbr.first]++;
        queue<int> q; for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
        int count = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); anim_nodes.push_back(u); count++;
            for (auto const& nbr : adjlist[u]) { anim_edges.push_back({u, nbr.first}); if (--indegree[nbr.first] == 0) q.push(nbr.first); }
        }
        if (count < n) { lastAlgo = CYCLE_DETECTED; for(int i=0; i<n; i++) if(indegree[i] > 0) anim_nodes.push_back(i); } else lastAlgo = TOPOSORT_BFS;
    }

    void primsMST(int n, int src) {
        sourceNode = src; destNode = -1; anim_nodes.clear(); anim_edges.clear();
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        vector<bool> vis(n, false); pq.push({0, {src, -1}});
        while (!pq.empty()) {
            auto it = pq.top(); pq.pop();
            int u = it.second.first, p = it.second.second;
            if (vis[u]) continue;
            vis[u] = true; anim_nodes.push_back(u); if (p != -1) anim_edges.push_back({p, u});
            for (auto nbr : adjlist[u]) if (!vis[nbr.first]) pq.push({nbr.second, {nbr.first, u}});
        }
        lastAlgo = PRIMS;
    }

    void kruskalMST(int n) {
        sourceNode = -1; destNode = -1; anim_nodes.clear(); anim_edges.clear();
        struct Edge { int u, v, w; }; vector<Edge> edges;
        for(auto const& p : adjlist) for(auto const& nbr : p.second) edges.push_back({p.first, nbr.first, nbr.second});
        sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.w < b.w; });
        DSU ds(n);
        vector<bool> nodeAdded(n, false); // Fix for duplicate nodes
        for(auto e : edges) {
            if(ds.unionByRank(e.u, e.v)) { 
                if(!nodeAdded[e.u]) { anim_nodes.push_back(e.u); nodeAdded[e.u] = true; }
                if(!nodeAdded[e.v]) { anim_nodes.push_back(e.v); nodeAdded[e.v] = true; }
                anim_edges.push_back({e.u, e.v}); 
            }
        }
        lastAlgo = KRUSKAL;
    }
};

#endif