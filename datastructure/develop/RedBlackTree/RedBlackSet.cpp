#include <bits/stdc++.h>

using namespace std;

namespace spihill {
template<class T>
class RedBlackSetIterator;

template<class T, class Compare = less<T>>
struct RedBlackSet {
	struct NODE;
	struct NODE_LIST;
	friend RedBlackSetIterator<T>;
	using iterator = RedBlackSetIterator<T>;
	NODE_LIST list_dummy;
	NODE node_dummy;
	RedBlackSet() {
		node_dummy.index = &list_dummy;
		list_dummy.node = &node_dummy;
	}
	RedBlackSet(const RedBlackSet& R) {
		node_dummy.index = &list_dummy;
		node_dummy.left_size = R.node_dummy.left_size;
		list_dummy.node = &node_dummy;
		auto dfs = [&](auto f, NODE* old_node, NODE* new_node) {
			if (0) return new_node;
			if (old_node->left) {
				new_node->left = f(f, old_node->left, new NODE((T&&) *(old_node->left->key), new_node));
			}
			auto l = new NODE_LIST(&list_dummy, true);
			l->node = new_node;
			new_node->index = l;
			new_node->red = old_node->red;
			new_node->left_size = old_node->left_size;
			new_node->right_size = old_node->right_size;
			if (old_node->right) {
				new_node->right = f(f, old_node->right, new NODE((T&&) *(old_node->right->key), new_node));
			}
			return new_node;
		};
		if (R.node_dummy.left) node_dummy.left = dfs(dfs, R.node_dummy.left, new NODE((T&&) *(R.node_dummy.left->key), &node_dummy));
	}
	~RedBlackSet() {
		for (NODE_LIST* p = list_dummy.fp; p != &list_dummy;) {
			p = p->fp;
			delete p->bp;
		}
	}
	int size() {
		return node_dummy.left_size;
	}
	iterator begin() {
		return iterator(list_dummy.fp);
	}
	iterator end() {
		return iterator(&list_dummy);
	}
	iterator lower_bound(T&& v) {
		NODE* now = node_dummy.left;
		NODE* ans = nullptr;
		while (now != nullptr) {
			if (Compare()(*(now->key), v)) {
				now = now->right;
			}
			else {
				ans = now;
				now = now->left;
			}
		}
		if (ans) return iterator(ans->index);
		return iterator(&list_dummy);
	}
	iterator lower_bound(const T& v) {
		return lower_bound((T&&) v);
	}
	iterator upper_bound(T&& v) {
		NODE* now = node_dummy.left;
		NODE* ans = nullptr;
		while (now != nullptr) {
			if (Compare()(v, *(now->key))) {
				ans = now;
				now = now->left;
			}
			else {
				now = now->right;
			}
		}
		if (ans) return iterator(ans->index);
		return iterator(&list_dummy);
	}
	iterator upper_bound(const T& v) {
		return upper_bound((T&&) v);
	}
	RedBlackSet& operator=(const RedBlackSet& R) {
		for (NODE_LIST* p = list_dummy.fp; p != &list_dummy;) {
			p = p->fp;
			delete p->bp;
		}
		node_dummy.index = &list_dummy;
		node_dummy.left_size = R.node_dummy.left_size;
		list_dummy.node = &node_dummy;
		auto dfs = [&](auto f, NODE* old_node, NODE* new_node) {
			if (0) return new_node;
			if (old_node->left) {
				new_node->left = f(f, old_node->left, new NODE((T&&) *(old_node->left->key), new_node));
			}
			auto l = new NODE_LIST(&list_dummy, true);
			l->node = new_node;
			new_node->index = l;
			new_node->red = old_node->red;
			new_node->left_size = old_node->left_size;
			new_node->right_size = old_node->right_size;
			if (old_node->right) {
				new_node->right = f(f, old_node->right, new NODE((T&&) *(old_node->right->key), new_node));
			}
			return new_node;
		};
		if (R.node_dummy.left) node_dummy.left = dfs(dfs, R.node_dummy.left, new NODE((T&&) *(R.node_dummy.left->key), &node_dummy));
		return *this;
	}
	struct NODE_LIST {
		NODE_LIST* fp;
		NODE_LIST* bp;
		NODE* node;
		bool dummy = false;
		NODE_LIST() : fp(this), bp(this), node(nullptr), dummy(true) {}
		NODE_LIST(NODE_LIST* p, bool is_left) : node(nullptr) {
			NODE_LIST* pre = is_left ? p->bp : p;
			NODE_LIST* nex = is_left ? p : p->fp;
			bp = pre;
			fp = nex;
			pre->fp = this;
			nex->bp = this;
		}
		~NODE_LIST() {
			if (!dummy) delete node;
		}
		int get_position() {
			int result = -1;
			bool is_left = false;
			NODE* n = this->node;
			while (true) {
				if (!is_left) result += n->left_size + 1;
				if (n->par) is_left = (n->par->left == n);
				else break;
				n = n->par;
			}
			return result;
		}
	};
	void remove_list(NODE_LIST* p) {
		p->bp->fp = p->fp;
		p->fp->bp = p->bp;
		delete p;
	}
	struct NODE {
		T* key;
		NODE_LIST* index;
		NODE* left;
		NODE* right;
		NODE* par;
		bool red = true;
		int left_size;
		int right_size;
		NODE() : key(nullptr), index(nullptr), left(nullptr), right(nullptr), par(nullptr), left_size(0), right_size(0) {}
		NODE(T&& d, NODE* par_) : index(nullptr), left(nullptr) , right(nullptr), par(par_), left_size(0), right_size(0) {
			key = new T(d);
		}
		~NODE() {
			delete key;
		}
		void RotateR(NODE*& parent, NODE*& child) {
			NODE* P = this;
			NODE* R = this->par;
			NODE* l = this->left;
			NODE* B = l->right;
			if (R->left == P) R->left = l;
			else R->right = l;
			l->par = R;
			if (B) B->par = P;
			P->left = B;
			P->left_size = l->right_size;
			l->right_size += P->right_size + 1;
			l->right = P;
			P->par = l;
			parent = R;
			child = l;
		}
		void RotateL(NODE*& parent, NODE*& child) {
			NODE* P = this;
			NODE* R = this->par;
			NODE* r = this->right;
			NODE* B = r->left;
			if (R->left == P) R->left = r;
			else R->right = r;
			r->par = R;
			if (B) B->par = P;
			P->right = B;
			P->right_size = r->left_size;
			r->left_size += P->left_size + 1;
			r->left = P;
			P->par = r;
			parent = R;
			child = r;
		}
		void RotateRL(NODE*& parent, NODE*& child) {
			this->right->RotateR(parent, child);
			this->RotateL(parent, child);
		}
		void RotateLR(NODE*& parent, NODE*& child) {
			this->left->RotateL(parent, child);
			this->RotateR(parent, child);
		}
	};
	void remove_node(NODE* n, bool is_left) {
		if (n->par->left == n) n->par->left = is_left ? n->left : n->right;
		else  n->par->right = is_left ? n->left : n->right;
		if (is_left) n->left->par = n->par;
		else n->right->par = n->par;
		remove_list(n->index);
	}
	void remove_node(NODE* n) {
		if (n->par->left == n) n->par->left = nullptr;
		else  n->par->right = nullptr;
		remove_list(n->index);
	}
	void insert_run(T&& v, NODE* parent, NODE* child, bool is_left) {
		if (is_left) parent->left = child;
		else parent->right = child;
		child->index = new NODE_LIST(parent->index, is_left);
		child->index->node = child;
		while (parent->red) {
			if (parent == &node_dummy) {
				child->red = false;
				break;
			}
			NODE* grand = parent->par;
			if (child == parent->left && parent == grand->left) {
				grand->RotateR(parent, child);
				child->left->red = false;
			} else if (child == parent->right && parent == grand->left) {
				grand->RotateLR(parent, child);
				child->left->red = false;
			} else if (child == parent->left && parent == grand->right) {
				grand->RotateRL(parent, child);
				child->right->red = false;
			} else if (child == parent->right && parent == grand->right) {
				grand->RotateL(parent, child);
				child->right->red = false;
			}
		}
	}
	iterator insert(T&& v) {
		NODE* pre = &node_dummy;
		NODE* now = pre->left;
		bool is_left = true;
		pre->left_size++;
		while (now != nullptr) {
			pre = now;
			if (Compare()(*(now->key) , v)) now = now->right, is_left = false, pre->right_size++;
			else now = now->left, is_left = true, pre->left_size++;
		}
		NODE* child = new NODE((T&&) v, pre);
		insert_run((T&&) v, pre, child , is_left);
		return iterator(child->index);
	}
	iterator insert(const T& v) {
		return insert((T&&) v);
	}
	void erase_run(NODE* target) {
		if (target->red) {
			if (target->left) remove_node(target, true);
			else if (target->right) remove_node(target, false);
			else remove_node(target);
			return;
		}
		NODE* child = target->left ? target->left : target->right;
		NODE* parent;
		bool is_left = target->left == child;
		if (child == nullptr) {
			parent = target->par;
			is_left = (parent->left == target);
			remove_node(target);
		} else if (child->red) {
			remove_node(target, is_left);
			child->red = false;
			return;
		} else {
			remove_node(target, is_left);
			parent = child->par;
			is_left = (parent->left == child);
		}
		while (true) {
			NODE *t, *u;
			if (parent == &node_dummy) {
				if (parent->left) parent->left->red = false;
				break;
			}
			if (is_left) {
				if (!(parent->right->red)) {
					if (parent->right->left && parent->right->left->red) {
						parent->RotateRL(t, u);
						parent->par->red = parent->red;
						parent->red = false;
						break;
					} else if (parent->right->right && parent->right->right->red) {
						parent->RotateL(t, u);
						parent->par->red = parent->red;
						parent->red = false;
						parent->par->right->red = false;
						break;
					} else {
						parent->right->red = true;
						if (parent->red) {
							parent->red = false;
							break;
						}
						is_left = (parent->par->left == parent);
						parent = parent->par;
					}
				} else {
					parent->RotateL(t, u);
					parent->red = true;
					parent->par->red = false;
				}
			} else /* !is_left */{
				if (!(parent->left->red)) {
					if (parent->left->right && parent->left->right->red) {
						parent->RotateLR(t, u);
						parent->par->red = parent->red;
						parent->red = false;
						break;
					} else if (parent->left->left && parent->left->left->red) {
						parent->RotateR(t, u);
						parent->par->red = parent->red;
						parent->red = false;
						parent->par->left->red = false;
						break;
					} else {
						parent->left->red = true;
						if (parent->red) {
							parent->red = false;
							break;
						}
						is_left = (parent->par->left == parent);
						parent = parent->par;
					}
				} else {
					parent->RotateR(t, u);
					parent->red = true;
					parent->par->red = false;
				}
			}
		} /* while true */
	}
	iterator erase(T&& v) {
		NODE* pre = &node_dummy;
		NODE* now = pre->left;
		queue<pair<bool, NODE*>> q;
		q.emplace(true, pre);
		NODE* target = nullptr;
		while (now != nullptr) {
			pre = now;
			if (Compare()(*(now->key) , v)) now = now->right, q.emplace(false, pre);
			else if (Compare()(v, *(now->key))) now = now->left, q.emplace(true, pre);
			else break;
		}
		if (now == nullptr) return iterator(&list_dummy);
		target = now;
		while (!q.empty()) {
			if (q.front().first) q.front().second->left_size--;
			else q.front().second->right_size--;
			q.pop();
		}
		if (target->left != nullptr) {
			target->left_size--;
			target = target->left;
			while (target->right) target->right_size--, target = target->right;
		}
		swap(now->key, target->key);
		NODE* t = target->index->fp->node;
		erase_run(target);
		return iterator(t->index);
	}
	iterator erase(const T& v) {
		return erase((T&&) v);
	}
	int count(T&& v) {
		enum STATUS {LEFT, RIGHT, NEUTRAL};
		int sum = 0;
		queue<pair<STATUS, NODE*>> q;
		q.emplace(NEUTRAL, node_dummy.left);
		while (!q.empty()) {
			pair<STATUS, NODE*> t = q.front();
			q.pop();
			int status = t.first;
			NODE* n = t.second;
			if (n == nullptr) continue;
			if (status == NEUTRAL) {
				if (Compare()(v, *(n->key))) q.emplace(NEUTRAL, n->left);
				else if (Compare()(*(n->key), v)) q.emplace(NEUTRAL, n->right);
				else {
					sum++;
					q.emplace(LEFT, n->left);
					q.emplace(RIGHT, n->right);
				}
			} else if (status == LEFT) {
				if (Compare()(*(n->key), v)) q.emplace(LEFT, n->right);
				else {
					sum += n->right_size + 1;
					q.emplace(LEFT, n->left);
				}
			} else /* if (status == RIGHT) */{
				if (Compare()(v, *(n->key))) q.emplace(RIGHT, n->left);
				else {
					sum += n->left_size + 1;
					q.emplace(RIGHT, n->right);
				}
			}
		}
		return sum;
	}
	int count(const T& v) {
		return count((T&&) v);
	}
	bool is_balanced() {
		auto dfs = [&](auto f, NODE* R, int& black, int& cnt, bool is_red = true) {
			if (is_red && R->red) return false;
			int r_black = 0;
			int l_black = 0;
			int r_cnt = 0;
			int l_cnt = 0;
			cnt = 1;
			if (R->left) {
				if (!f(f, R->left, l_black, l_cnt, R->red)) return false;
			}
			if (R->right) {
				if (!f(f, R->right, r_black, r_cnt, R->red)) return false;
			}
			if (r_black != l_black) {
				cerr << "black" << endl;
				return false;
			}
			if (r_cnt != R->right_size) {
				cerr << "r_cnt" << endl;
				return false;
			}
			if (l_cnt != R->left_size) {
				cerr << "l_cnt" << endl;
				return false;
			}
			black = r_black + !(R->red);
			cnt += r_cnt + l_cnt;
			return true;
		};
		int t, u;
		return dfs(dfs, node_dummy.left, t, u);
	}
	const T& operator[](int x) {
		if (x < 0 || size() <= x) throw out_of_range("Error at RedBlackSet::operator[]");
		int pos = 0;
		NODE* now = node_dummy.left;
		while (true) {
			if (pos + now->left_size < x) pos += now->left_size + 1, now = now->right;
			else if (x < pos + now->left_size) now = now->left;
			else break;
		}
		return *(now->key);
	}
};
template<class T>
class RedBlackSetIterator {
	friend RedBlackSet<T>;
	using NODE_LIST = typename RedBlackSet<T>::NODE_LIST;
	NODE_LIST* list_ptr;
	RedBlackSetIterator(NODE_LIST* n) : list_ptr(n) {}
public:
	RedBlackSetIterator(const RedBlackSetIterator& R) : list_ptr(R.list_ptr) {}
	RedBlackSetIterator& operator++() {
		if (list_ptr->dummy) throw out_of_range("Error at RedBlackSetIterator& operator++()");
		list_ptr = list_ptr->fp;
		return *this;
	}
	RedBlackSetIterator operator++(int unused) {
		if (list_ptr->dummy) throw out_of_range("Error at RedBlackSetIterator operator++(int)");
		RedBlackSetIterator result = *this;
		list_ptr = list_ptr->fp;
		return result;
	}
	RedBlackSetIterator& operator--() {
		if (list_ptr->bp->dummy) throw out_of_range("Error at RedBlackSetIterator& operator--()");
		list_ptr = list_ptr->bp;
		return *this;
	}
	RedBlackSetIterator operator--(int unused) {
		if (list_ptr->bp->dummy) throw out_of_range("Error at RedBlackSetIterator operator--(int)");
		RedBlackSetIterator result = *this;
		list_ptr = list_ptr->bp;
		return result;
	}
	int operator-(const RedBlackSetIterator& R) {
		return list_ptr->get_position() - R.list_ptr->get_position();
	}
	const T& operator*() const {
		assert(list_ptr->node->key);
		return *(list_ptr->node->key);
	}
	bool operator==(const RedBlackSetIterator& R) {
		return this->list_ptr == R.list_ptr;
	}
	bool operator!=(const RedBlackSetIterator& R) {
		return !(*this == R);
	}
};
}

using namespace spihill;

void check_insert(const int);
void check_erase(const int);
bool check(RedBlackSet<int>& R, multiset<int>& S);

int main()
{
	cout << "START INSERT TEST" << endl;
	check_insert(100000);
	cout << "PASSED" << endl;
	cout << "START ERASE TEST" << endl;
	check_erase(100000);
	cout << "PASSED" << endl;
	return 0;
}

void check_erase(const int MAX)
{
	RedBlackSet<int> R_random_small;
	RedBlackSet<int> R_increase;
	RedBlackSet<int> R_decrease;
	RedBlackSet<int> R_nothing;

	multiset<int> S_random_small;
	multiset<int> S_increase;
	multiset<int> S_decrease;
	multiset<int> S_nothing;

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	std::uniform_real_distribution<> dist1(-1.0, 1.0);

	for (int i = -MAX; i < MAX; i++) {
		int big = 1000000000 * dist1(engine);
		int small = 100 * dist1(engine);
		R_random_small.insert(small);
		R_increase.insert(i);
		R_decrease.insert(i);
		R_nothing.insert(big);
		S_random_small.insert(small);
		S_increase.insert(i);
		S_decrease.insert(i);
	}
	for (int i = 0; i < MAX; i++) {
		R_increase.erase(-i - 1);
		R_decrease.erase(i);
		S_increase.erase(-i - 1);
		S_decrease.erase(i);
	}

	for (int i = -100; i <= 100; i++) {
		assert(R_random_small.count(i) == (int) S_random_small.count(i));
		assert((int) S_random_small.count(i) == R_random_small.upper_bound(i) - R_random_small.lower_bound(i));
	}

	for (int i = 0; i < 10; i++) {
		int small = 100 * dist1(engine);
		while (R_random_small.erase(small) != R_random_small.end());
		S_random_small.erase(small);
	}

	for (int i = -100; i <= 100; i++) {
		assert(R_random_small.count(i) == (int) S_random_small.count(i));
		assert((int) S_random_small.count(i) == R_random_small.upper_bound(i) - R_random_small.lower_bound(i));
	}

	while (R_nothing.erase(*(R_nothing.begin())) != R_nothing.end());

	assert(check(R_increase, S_increase));
	assert(check(R_decrease, S_decrease));
	assert(check(R_random_small, S_random_small));
	assert(check(R_nothing, S_nothing));
	assert(R_increase.is_balanced());
	assert(R_decrease.is_balanced());
	assert(R_random_small.is_balanced());
	return;
}

void check_insert(const int MAX)
{
	RedBlackSet<int> R_random_big;
	RedBlackSet<int> R_random_small;
	RedBlackSet<int> R_increase;
	RedBlackSet<int> R_decrease;

	multiset<int> S_random_big;
	multiset<int> S_random_small;
	multiset<int> S_increase;
	multiset<int> S_decrease;

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	std::uniform_real_distribution<> dist1(-1.0, 1.0);

	for (int i = -MAX; i < MAX; i++) {
		int big = 1000000000 * dist1(engine);
		int small = 100 * dist1(engine);
		R_random_big.insert(big);
		R_random_small.insert(small);
		R_increase.insert(i);
		R_decrease.insert(-i);
		S_random_big.insert(big);
		S_random_small.insert(small);
		S_increase.insert(i);
		S_decrease.insert(-i);
	}
	auto R_copy(R_random_big);
	auto S_copy = S_random_big;
	RedBlackSet<int> R_assign;
	R_assign = R_random_big;
	for (int i = -MAX; i < MAX; i++) {
		int big = 1000000000 * dist1(engine);
		R_copy.insert(big);
		R_assign.insert(big);
		S_copy.insert(big);
	}
	assert(check(R_increase, S_increase));
	assert(check(R_decrease, S_decrease));
	assert(check(R_random_big, S_random_big));
	assert(check(R_random_small, S_random_small));
	assert(check(R_copy, S_copy));
	assert(check(R_assign, S_copy));
	assert(R_increase.is_balanced());
	assert(R_decrease.is_balanced());
	assert(R_random_big.is_balanced());
	assert(R_copy.is_balanced());
	assert(R_assign.is_balanced());
	assert(R_random_small.is_balanced());
	return;
}

bool check(RedBlackSet<int>& R, multiset<int>& S)
{
	auto itr_S = S.begin();
	auto itr_R = R.begin();
	if ((int) S.size() != R.size()) {
		cerr << "S.size() != R.size()" << endl;
		return false;
	}
	for (; itr_R != R.end(); itr_R++, itr_S++) {
		if (*itr_R != *itr_S) return false;
	}
	return itr_S == S.end();
}
