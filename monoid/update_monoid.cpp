namespace update_monoid_n {
template<class T>
struct update_monoid {
	using monoid_type = pair<T, char>;
	pair<T, char> val;
	update_monoid(T v) : val(v, 0) {}
	update_monoid(pair<T, char> v) : val(v) {}
	update_monoid() : val(T(), 1) {}
	static update_monoid merge(const update_monoid& lhs, const update_monoid& rhs) {
		if (rhs.val.second) return lhs;
		return rhs;
	}
};
}
using update_monoid_n::update_monoid;