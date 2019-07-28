template<class CAP_T>
struct Edge_Cap_Rev {
	int from;
	int to;
	CAP_T cap;
	int rev;
	Edge_Cap_Rev(int x, int y, CAP_T z, int w) : from(x), to(y), cap(z), rev(w) {}
};
using edge = Edge_Cap_Rev<>;