---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj/Prim_2.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Prim_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Prim.cpp.html">graph/Prim.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A"
#include <bits/stdc++.h>
 
using namespace std;

#include "../../graph/Prim.cpp"

int main() {
    int n; cin >> n;
    graph<long long> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            if (c >= 0) g.add_edge(i, j, c);
        }
    }
    cout << Prim(g) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Prim_2.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A"
#include <bits/stdc++.h>
 
using namespace std;

#line 1 "test/aoj/../../graph/Prim.cpp"
namespace prim_n {
#line 1 "test/aoj/../../graph/../snippet/WeightedEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int to;
	W w;
	template<class... Args> Edge(int t, Args... args) : to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "test/aoj/../../graph/../snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 9 "test/aoj/../../graph/../snippet/WeightedEdge.cpp"
};
template<class W>
struct Edges : private vector<vector<Edge<W>>> {
	using type = vector<vector<Edge<W>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#line 1 "test/aoj/../../graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 18 "test/aoj/../../graph/../snippet/WeightedEdge.cpp"
};#line 3 "test/aoj/../../graph/Prim.cpp"
template<class W>
W Prim(Edges<W>& e) {
	W res = 0;
	vector<char> used(e.size(), 0);
	priority_queue<pair<W, int>, vector<pair<W, int>>, greater<>> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second] != 0) continue;
		used[p.second] = 1;
		res += p.first;
		for (auto& x : e[p.second]) {
			q.emplace(x.w, x.to);
		}
	}
	return res;
}
}
using prim_n::Prim;
template<class W> using graph = prim_n::Edges<W>;#line 7 "test/aoj/Prim_2.test.cpp"

int main() {
    int n; cin >> n;
    graph<long long> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            if (c >= 0) g.add_edge(i, j, c);
        }
    }
    cout << Prim(g) << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

