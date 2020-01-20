/**
 * @title Sparse Table
 */
template<class T, class F = function<T(T, T)>>
struct SparseTable {
	using index_type = uint_fast32_t;
	vector<vector<T>> table;
	vector<index_type> L;
	const F f;
	SparseTable(F f) : f(f) {}
	SparseTable(F f, const vector<T>& v) : SparseTable(f) { build(v);}
	void build(const vector<T>& v) {
		table.clear();
		const index_type sz = v.size(); 
		table.emplace_back(sz);
		for (index_type i = 0; i < sz; i++) table[0][i] = v[i];
		for (index_type len = 2, pos = 1; len < sz; len <<= 1, pos++) {
			table.emplace_back(sz - len / 2);
			for (index_type i = 0; i + len / 2 < sz; i++) {
				table[pos][i] = f(table[pos-1][i], table[pos-1][i+len/2]);
			}
		}
		L.clear(); L.resize(sz+1);
		index_type len = 1;
		for (index_type i = 1; i <= sz; i++) {
			if ((index_type(1) << len) < i) len++;
			L[i] = len-1;
		}
	}
	T get(index_type l, index_type r) const {
		return f(table[L[r-l]][l], table[L[r-l]][r-(1 << L[r-l])]);
	}
};