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


# :warning: tools/RandomClass.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4a931512ce65bdc9ca6808adf92d8783">tools</a>
* <a href="{{ site.github.repository_url }}/blob/master/tools/RandomClass.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-13 20:18:32+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct RandomClass {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	RandomClass() : rd(), xor128(rd()) {}
	T make_random(T min_v, T max_v) { 
		static_assert(is_integral<T>::value);
		return uniform_int_distribution<T>(min_v, max_v)(xor128);
	}
};
#define make_real(type) template<> type RandomClass<type>::make_random(type min_v, type max_v) { return uniform_real_distribution<type>(min_v, max_v)(xor128);}
make_real(float)
make_real(double)
make_real(long double)
#undef make_real
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "tools/RandomClass.cpp"
template<class T>
struct RandomClass {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	RandomClass() : rd(), xor128(rd()) {}
	T make_random(T min_v, T max_v) { 
		static_assert(is_integral<T>::value);
		return uniform_int_distribution<T>(min_v, max_v)(xor128);
	}
};
#define make_real(type) template<> type RandomClass<type>::make_random(type min_v, type max_v) { return uniform_real_distribution<type>(min_v, max_v)(xor128);}
make_real(float)
make_real(double)
make_real(long double)
#undef make_real
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

