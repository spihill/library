template<class T, class U = T>
struct Node {
	T val;
	explicit Node(T v) : val(v) {}
	explicit Node() : val() {}
	inline Node operator+(const Node& rhs) const { // valとrhs.valの演算 
		return Node($1);
	}
	inline void assign(const U v) { // setクエリで代入する際の処理
		val = $2;
	}
	using NODE_T = T; using ASSIGN_T = U;
};