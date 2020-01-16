#include "../min_monoid.cpp"
#include "../update_monoid.cpp"

template<class T, class U = T>
struct min_update_monoid {
	struct Lazy : public update_monoid<U> {
		using update_monoid<U>::update_monoid;
		using update_monoid<U>::operator+;
		using update_monoid<U>::operator=;
		Lazy(update_monoid<U> x) : update_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		inline bool is_unity() const {
			return this->unit;
		}
	};
	struct Monoid : public min_monoid<T> {
		using min_monoid<T>::min_monoid;
		using min_monoid<T>::operator+;
		using min_monoid<T>::operator=;
		Monoid(min_monoid<T> x) : min_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(rhs.val);
		}
	};
};