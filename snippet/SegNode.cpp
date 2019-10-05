template<class T, class U = T>
struct Node {
	T val;
	const static T UNITY = $1;
	explicit Node(T v) : val(v) {}
	explicit Node() : val(UNITY) {}
	inline Node operator+(const Node& rhs) const { // valとrhs.valの演算 
		return Node($2);
	}
	inline void assign(const U v) { // setクエリで代入する際の処理
		val = $3;
	}
	using NODE_T = T; using ASSIGN_T = U;
};