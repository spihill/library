template<class T>
struct SWAG {
	struct node {
		T val, sum;
		node() : val(), sum() {}
		node(T v, T s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	T fold_all() const {
		if (empty()) return T();
		if (F.empty()) return B.top().sum;
		if (B.empty()) return F.top().sum;
		return F.top().sum + B.top().sum;
	}
	void push(T x) {
		if (B.empty()) B.emplace(x, x);
		else {
			T s{B.top().sum + x};
			B.emplace(x, move(s));
		}
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