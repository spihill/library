#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"

template<class T, class U>
Node<T, U>::Node() : val(3) {}

template<class T, class U>
Node<T, U> Node<T, U>::operator+(const Node& rhs) const {
	return Node(val + rhs.val);
}

template<class T, class U>
void Node<T, U>::assign(const U v) {
	val += v;
}

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<Node<int>> S(-2e18, 2e18, false);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) - 3 * (y - x) << endl;
		}
	}
}