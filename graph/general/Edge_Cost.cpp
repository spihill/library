template<class COST_T>
struct Edge_Cost {
	int from;
	int to;
	COST_T cost;
	Edge_Cost(int from_, int to_, COST_T cost_) : from(from_), to(to_), cost(cost_) {}
	Edge_Cost(void) : from(0), to(0), cost(0) {}
	inline bool operator<(const Edge_Cost a) const {
		return cost < a.cost;
	}
	inline bool operator>(const Edge_Cost a) const {
		return a < (*this);
	}
};
using edge = Edge_Cost<>;