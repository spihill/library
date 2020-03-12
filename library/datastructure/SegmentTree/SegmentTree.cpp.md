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


# :heavy_check_mark: セグメント木

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cbada5aa9c548d7605cff951f3e28eda">datastructure/SegmentTree</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SegmentTree/SegmentTree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 02:35:52+09:00




## Depends on

* :heavy_check_mark: <a href="../../for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/SegmentTree_RMQ.test.cpp.html">test/aoj/SegmentTree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj/SegmentTree_RMQ_2.test.cpp.html">test/aoj/SegmentTree_RMQ_2.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj/SegmentTree_RSQ.test.cpp.html">test/aoj/SegmentTree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yosupo/SegTree_Affine.test.cpp.html">test/yosupo/SegTree_Affine.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title セグメント木
 * @brief 0-indexed 半開区間
 * @brief クラス Node は Monoid であり、{型(monoid_type), 演算(operator+), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief Node の具体例は monoid/ にある。
 */
namespace segmenttree_n {
#include "../../for_include/is_monoid.cpp"
template<class Node>
struct SegmentTree {
	static_assert(is_monoid_v<Node>, "");
	using Node_T = typename Node::monoid_type;
	using index_type = uint_fast32_t;
	index_type n;
	vector<Node> node;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	SegmentTree (index_type N) {build(N);}
	// @brief vector で初期化 $O(N)$
	SegmentTree (const vector<Node_T>& v) {build(v);}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(index_type N) {
		n = calc_n(N);
		node.clear(); node.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<Node_T>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	// @brief index i に v を代入 $O(\log N)$
	void set(index_type i, Node_T v) {
		i += n - 1;
		node[i].val = move(v);
		while (i) {
			i = (i-1) / 2;
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	// @brief [l, r) を取得 $O(\log N)$
	Node_T get(index_type l, index_type r) {
		Node val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = val_l + node[l];
			if (r % 2 == 0) val_r = node[r-1] + val_r;
		}
		return (val_l + val_r).val;
	}
	// @brief index i を取得 $O(\log N)$
	const Node_T& operator[](index_type i) {
		return node[i+n-1].val;
	}
private:
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
} // namespace segmenttree_n
using segmenttree_n::SegmentTree;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SegmentTree/SegmentTree.cpp"
/**
 * @title セグメント木
 * @brief 0-indexed 半開区間
 * @brief クラス Node は Monoid であり、{型(monoid_type), 演算(operator+), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief Node の具体例は monoid/ にある。
 */
namespace segmenttree_n {
#line 1 "datastructure/SegmentTree/../../for_include/is_monoid.cpp"
namespace is_monoid_n {
#line 1 "datastructure/SegmentTree/../../for_include/is_addable.cpp"
namespace is_addable_n {
template <class T1, class T2 = T1>
class is_addable {
	template <class U1, class U2> static constexpr auto check(U1*, U2*) -> decltype(
		declval<U1>() + declval<U2>(), true_type()
	);
	template <class U1, class U2> static constexpr auto check(...) -> false_type;
public:
	static constexpr bool value = decltype(check<T1, T2>(nullptr, nullptr))::value;
};
template <class T, class U = T>
constexpr bool is_addable_v = is_addable<T, U>::value;
} // namespace is_addable_n
using is_addable_n::is_addable;
using is_addable_n::is_addable_v;
#line 3 "datastructure/SegmentTree/../../for_include/is_monoid.cpp"
template <class T>
class is_monoid {
	template <class U> static constexpr true_type check(typename U::monoid_tag*);
	template <class U> static constexpr false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value && is_addable_v<T>;
};
template <class T> constexpr bool is_monoid_v = is_monoid<T>::value;
} // namespace is_monoid_n
using is_monoid_n::is_monoid;
using is_monoid_n::is_monoid_v;
#line 9 "datastructure/SegmentTree/SegmentTree.cpp"
template<class Node>
struct SegmentTree {
	static_assert(is_monoid_v<Node>, "");
	using Node_T = typename Node::monoid_type;
	using index_type = uint_fast32_t;
	index_type n;
	vector<Node> node;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	SegmentTree (index_type N) {build(N);}
	// @brief vector で初期化 $O(N)$
	SegmentTree (const vector<Node_T>& v) {build(v);}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(index_type N) {
		n = calc_n(N);
		node.clear(); node.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<Node_T>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	// @brief index i に v を代入 $O(\log N)$
	void set(index_type i, Node_T v) {
		i += n - 1;
		node[i].val = move(v);
		while (i) {
			i = (i-1) / 2;
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	// @brief [l, r) を取得 $O(\log N)$
	Node_T get(index_type l, index_type r) {
		Node val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = val_l + node[l];
			if (r % 2 == 0) val_r = node[r-1] + val_r;
		}
		return (val_l + val_r).val;
	}
	// @brief index i を取得 $O(\log N)$
	const Node_T& operator[](index_type i) {
		return node[i+n-1].val;
	}
private:
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
} // namespace segmenttree_n
using segmenttree_n::SegmentTree;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

