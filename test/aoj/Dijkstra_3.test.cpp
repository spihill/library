#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dijkstra.cpp"

int main() {
    int n; cin >> n;
    graph<int> g(n);
    for (int i = 0; i < n; i++) {
        int v, k; cin >> v >> k;
        while (k--) {
            int u, c; cin >> u >> c;
            g.add_edge(v, u, c);
        }
    }
    Dijkstra(g, 0, INT_MAX);
    for (int i = 0; i < n; i++) {
        cout << i << " " << g.dist[i] << endl;
    }
}