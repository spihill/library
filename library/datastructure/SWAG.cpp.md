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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: SWAG (Sliding Window Aggregation)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SWAG.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-13 21:37:20+09:00




## Required by

* :heavy_check_mark: <a href="../algorithm/syakutori.cpp.html">尺取り法</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_A.test.cpp.html">test/aoj/syakutori_DSL_3_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_C.test.cpp.html">test/aoj/syakutori_DSL_3_C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/SWAG_Affine.test.cpp.html">test/yosupo/SWAG_Affine.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title SWAG (Sliding Window Aggregation)
 * @brief 本来 SWAG は半群を扱うことができるが、これは Node を扱う。queue が空の時には単位元を返す。
 */
template<class Node>
struct SWAG {
	using node_type = typename Node::monoid_type;
	struct node {
		Node val, sum;
		node() : val(), sum() {}
		node(node_type v, node_type s) : val(v), sum(s) {}
		node(Node v, Node s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	// @brief queue の中の和をとる $O(1)$
	node_type fold_all() const {
		if (empty()) return Node().val;
		if (F.empty()) return B.top().sum.val;
		if (B.empty()) return F.top().sum.val;
		return Node::merge(F.top().sum, B.top().sum).val;
	}
	// @brief queue の末尾に要素を push $O(1)$
	void push(Node x) {
		if (B.empty()) B.emplace(x, x);
		else {
			Node s{Node::merge(B.top().sum, x)};
			B.emplace(x, move(s));
		}
	}
	// @brief queue の先頭の要素を pop ならし $O(1)$
	void pop() {
		assert(!empty());
		if (F.empty()) {
			F.emplace(B.top().val, B.top().val); B.pop();
			while (B.size()) {
				F.emplace(B.top().val, Node::merge(B.top().val, F.top().sum));
				B.pop();
			}
		}
		F.pop();
	}
	bool empty() const {
		return size() == 0;
	}
	uint_fast32_t size() const {
		return F.size() + B.size();
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SWAG.cpp"
/**
 * @title SWAG (Sliding Window Aggregation)
 * @brief 本来 SWAG は半群を扱うことができるが、これは Node を扱う。queue が空の時には単位元を返す。
 */
template<class Node>
struct SWAG {
	using node_type = typename Node::monoid_type;
	struct node {
		Node val, sum;
		node() : val(), sum() {}
		node(node_type v, node_type s) : val(v), sum(s) {}
		node(Node v, Node s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	// @brief queue の中の和をとる $O(1)$
	node_type fold_all() const {
		if (empty()) return Node().val;
		if (F.empty()) return B.top().sum.val;
		if (B.empty()) return F.top().sum.val;
		return Node::merge(F.top().sum, B.top().sum).val;
	}
	// @brief queue の末尾に要素を push $O(1)$
	void push(Node x) {
		if (B.empty()) B.emplace(x, x);
		else {
			Node s{Node::merge(B.top().sum, x)};
			B.emplace(x, move(s));
		}
	}
	// @brief queue の先頭の要素を pop ならし $O(1)$
	void pop() {
		assert(!empty());
		if (F.empty()) {
			F.emplace(B.top().val, B.top().val); B.pop();
			while (B.size()) {
				F.emplace(B.top().val, Node::merge(B.top().val, F.top().sum));
				B.pop();
			}
		}
		F.pop();
	}
	bool empty() const {
		return size() == 0;
	}
	uint_fast32_t size() const {
		return F.size() + B.size();
	}
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

