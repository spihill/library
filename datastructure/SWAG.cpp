template<class Monoid>
struct SWAG {
	using Monoid_T = typename Monoid::monoid_type;
	struct node {
		Monoid val, sum;
		node() : val(), sum() {}
		node(Monoid_T v, Monoid_T s) : val(v), sum(s) {}
		node(Monoid v, Monoid s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	Monoid_T fold_all() const {
		if (empty()) return Monoid().val;
		if (F.empty()) return B.top().sum.val;
		if (B.empty()) return F.top().sum.val;
		return (F.top().sum + B.top().sum).val;
	}
	void push(Monoid x) {
		if (B.empty()) B.emplace(x, x);
		else {
			Monoid s{B.top().sum + x};
			B.emplace(x, move(s));
		}
	}
	void push(Monoid_T x) {
		push(Monoid(x));
	}
	void pop() {
		assert(!empty());
		if (F.empty()) {
			F.emplace(B.top().val, B.top().val); B.pop();
			while (B.size()) {
				F.emplace(B.top().val, B.top().val + F.top().sum);
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