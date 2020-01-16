#include "../min.cpp"
#include "../plus.cpp"

template<class T, class U = T>
struct min_plus_monoid {
	struct Lazy : public plus_monoid<U> {
		using plus_monoid<U>::plus_monoid;
		using plus_monoid<U>::operator+;
		using plus_monoid<U>::operator=;
		Lazy(plus_monoid<U> x) : plus_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Monoid : public min_monoid<T> {
		using min_monoid<T>::min_monoid;
		using min_monoid<T>::operator+;
		using min_monoid<T>::operator=;
		Monoid(min_monoid<T> x) : min_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(this->val + rhs.val);
		}
	};
};