#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370"

#include <bits/stdc++.h>
using namespace std;

#include "../../graph/is_Biparite.cpp"
#include "../../dp/PartialSum_limited.cpp"
#include "../../template/UnWeightedGraph.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (int i = 0; i < E; i++) {
		int a, b; cin >> a >> b; a--; b--;
		G.add_edge(a, b);
		G.add_edge(b, a);
	}

	auto res = is_Biparite(G);
	if (res.size() == 0) {
		cout << -1 << endl;
		return 0;
	}
	map<int, int> m;
	int zero = 0;
	vector<int> w;
	vector<int> cnt;
	for (auto& x: res) {
		int diff = abs(x.first - x.second);
		zero += diff;
		m[diff]++;
	}
	for (auto& x: m) {
		w.push_back(x.first*2);
		cnt.push_back(x.second);
	}
	auto dp = PartialSum_limited(w, cnt, zero * 2 + 1);
	for (int i = 0; i <= zero; i++) {
		if (dp[zero+i] >= 0 || dp[zero-i] >= 0) {
			long long a = V + i;
			long long b = V - i;
			cout << a * b / 4 - E << endl;
			return 0;
		}
	}
}