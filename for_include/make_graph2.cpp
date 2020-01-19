template<class T = long long, class U = long long>
graph<T, U> make_graph(size_t N) {
	return move(graph<T, U>(N));
}