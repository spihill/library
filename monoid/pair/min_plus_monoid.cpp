#include "../min_monoid.cpp"
#include "../plus_monoid.cpp"

template<class T, class U = T>
struct min_plus_monoid {
	template<class TT> using lazy_monoid = plus_monoid<TT>;
	template<class TT> using node_monoid = min_monoid<TT>;
	struct Lazy : public lazy_monoid<U> {
		using lazy_monoid<U>::lazy_monoid;
		using lazy_monoid<U>::operator+;
		using lazy_monoid<U>::operator=;
		Lazy(lazy_monoid<U> x) : lazy_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Node : public node_monoid<T> {
		using node_monoid<T>::node_monoid;
		using node_monoid<T>::operator+;
		using node_monoid<T>::operator=;
		Node(node_monoid<T> x) : node_monoid<T>(x) {}
		inline Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
};