#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A"
#include <bits/stdc++.h>
 
using namespace std;

#include "../../graph/Prim.cpp"
#include "../../template/WeightedGraph.cpp"

int main() {
    int n; cin >> n;
	auto g = make_weighted_graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            if (c >= 0) g.add_edge(i, j, c);
        }
    }
    cout << Prim(g) << endl;
}