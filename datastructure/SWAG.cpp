/**
 * @title SWAG (Sliding Window Aggregation)
 * @brief 本来 SWAG は半群を扱うことができるが、これは Node を扱う。queue が空の時には単位元を返す。
 */
template<class Node>
struct SWAG {
	using node_type = typename Node::monoid_type;
	struct node {
		Node val, sum;
		node() : val(), sum() {}
		node(node_type v, node_type s) : val(v), sum(s) {}
		node(Node v, Node s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	// @brief queue の中の和をとる $O(1)$
	node_type fold_all() const {
		if (empty()) return Node().val;
		if (F.empty()) return B.top().sum.val;
		if (B.empty()) return F.top().sum.val;
		return Node::merge(F.top().sum, B.top().sum).val;
	}
	// @brief queue の末尾に要素を push $O(1)$
	void push(Node x) {
		if (B.empty()) B.emplace(x, x);
		else {
			Node s{Node::merge(B.top().sum, x)};
			B.emplace(x, move(s));
		}
	}
	// @brief queue の先頭の要素を pop ならし $O(1)$
	void pop() {
		assert(!empty());
		if (F.empty()) {
			F.emplace(B.top().val, B.top().val); B.pop();
			while (B.size()) {
				F.emplace(B.top().val, Node::merge(B.top().val, F.top().sum));
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