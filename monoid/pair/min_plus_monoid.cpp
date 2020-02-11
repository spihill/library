namespace min_plus_monoid_n {
#include "../min_monoid.cpp"
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct min_plus_monoid : public monoid_pair_base<min_monoid<T>, plus_monoid<U>> {
	using super = monoid_pair_base<min_monoid<T>, plus_monoid<U>>;
	struct Lazy : public super::Lazy_m {
		Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		bool is_unity() const {
			return this->val == T();
		}
		using super::Lazy_m::operator+;
		using super::Lazy_m::operator=;
		using super::Lazy_m::Lazy_m;
	};
	struct Node : public super::Node_m {
		Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
		using super::Node_m::operator+;
		using super::Node_m::operator=;
		using super::Node_m::Node_m;
	};
};
} // namespace min_plus_monoid_n
using min_plus_monoid_n::min_plus_monoid;