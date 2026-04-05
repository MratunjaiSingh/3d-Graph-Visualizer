 #ifndef DSU_H
#define DSU_H

#include <unordered_map>
using namespace std;

template<typename T>
class DSU {
public:
    unordered_map<T, T> parent;
    unordered_map<T, int> rank;

    // make set
    void make_set(T node) {
        parent[node] = node;
        rank[node] = 0;
    }

    // find parent with path compression
    T find_parent(T node) {
        if (parent[node] == node) return node;
        return parent[node] = find_parent(parent[node]);
    }

    // union by rank
    void union_set(T u, T v) {
        u = find_parent(u);
        v = find_parent(v);

        if (u == v) return;

        if (rank[u] < rank[v]) {
            parent[u] = v;
        }
        else if (rank[v] < rank[u]) {
            parent[v] = u;
        }
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
};

#endif