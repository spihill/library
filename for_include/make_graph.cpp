template<class T = long long>
graph<T> make_graph(size_t N) {
	return move(graph<T>(N));
}