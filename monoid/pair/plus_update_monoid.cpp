#include "../plus_monoid.cpp"
#include "../update_monoid.cpp"

template<class T, class U = T>
struct plus_update_monoid {
	struct Lazy : public update_monoid<U> {
		using update_monoid<U>::update_monoid;
		using update_monoid<U>::operator+;
		using update_monoid<U>::operator=;
		Lazy(update_monoid<U> x) : update_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
		inline bool is_unity() const {
			return this->unit;
		}
	};
	struct Monoid : public plus_monoid<T> {
		using plus_monoid<T>::plus_monoid;
		using plus_monoid<T>::operator+;
		using plus_monoid<T>::operator=;
		Monoid(plus_monoid<T> x) : plus_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(rhs.val);
		}
	};
};