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


# :warning: graph/develop/Ford_Fulkerson.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#95854e999cb9c227e468acd41a41ac58">graph/develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/develop/Ford_Fulkerson.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-04 22:02:13+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Ford_Fulkerson {
	edges& v;
	vector<bool> used;
	int n;
	const int INF = INT_MAX;
// a:Vertex(|V|)
	Ford_Fulkerson(edges& a) : v(a) {
		n = a.size();
		used.resize(n);
	}
// x:from y:to z:capacity
	void add_edge(int x, int y, int z) {
		v.add_edge(edge(x, y, z, v[y].size()));
		v.add_edge(edge(y, x, 0, v[x].size()-1));
	}
	int dfs(int s, int t, int f) {
		if (used[s]) return 0;
		used[s] = true;
		if (s == t) return f;
		for (auto& x : v[s]) {
			if (x.cap == 0) continue;
			int ret = dfs(x.to, t, min(f, x.cap));
			if (ret > 0) {
				x.cap -= ret;
				v[x.to][x.rev].cap += ret;
				return ret;
			}
		}
		return 0;
	}
	int calc(int s, int t) {
		int res = 0;
		while (true){
			fill(used.begin(), used.end(), false);
			int r = dfs(s, t, INF);
			if (r == 0) break;
			res += r;
		}
		return res;
	}
};
/*
	Depends on
		- Edge_Cap_Rev
		- Edges_List
*/
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/develop/Ford_Fulkerson.cpp"
struct Ford_Fulkerson {
	edges& v;
	vector<bool> used;
	int n;
	const int INF = INT_MAX;
// a:Vertex(|V|)
	Ford_Fulkerson(edges& a) : v(a) {
		n = a.size();
		used.resize(n);
	}
// x:from y:to z:capacity
	void add_edge(int x, int y, int z) {
		v.add_edge(edge(x, y, z, v[y].size()));
		v.add_edge(edge(y, x, 0, v[x].size()-1));
	}
	int dfs(int s, int t, int f) {
		if (used[s]) return 0;
		used[s] = true;
		if (s == t) return f;
		for (auto& x : v[s]) {
			if (x.cap == 0) continue;
			int ret = dfs(x.to, t, min(f, x.cap));
			if (ret > 0) {
				x.cap -= ret;
				v[x.to][x.rev].cap += ret;
				return ret;
			}
		}
		return 0;
	}
	int calc(int s, int t) {
		int res = 0;
		while (true){
			fill(used.begin(), used.end(), false);
			int r = dfs(s, t, INF);
			if (r == 0) break;
			res += r;
		}
		return res;
	}
};
/*
	Depends on
		- Edge_Cap_Rev
		- Edges_List
*/
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

