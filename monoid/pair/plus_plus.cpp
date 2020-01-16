#include "../plus.cpp"

template<class T, class U = T>
struct plus_plus_monoid {
	struct Lazy : public plus_monoid<U> {
		using plus_monoid<U>::plus_monoid;
		using plus_monoid<U>::operator+;
		using plus_monoid<U>::operator=;
		Lazy(plus_monoid<U> x) : plus_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Monoid : public plus_monoid<T> {
		using plus_monoid<T>::plus_monoid;
		using plus_monoid<T>::operator+;
		using plus_monoid<T>::operator=;
		Monoid(plus_monoid<T> x) : plus_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(this->val + rhs.val);
		}
	};
};