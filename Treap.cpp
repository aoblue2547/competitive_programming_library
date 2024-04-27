template<class S, S(*op)(S, S), S(*e)()>
class Treap {
	class xorshift {
		ull x;
	public:
		xorshift() {
			mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
			x = rnd();
			for (int i = 0; i < 100; i++) {
				random();
			}
		}

		ull random() {
			x = x ^ (x << 7);
			return x = x ^ (x >> 9);
		}
	} rnd;
	struct Node {
		S val;
		Node* lch, *rch;
		int pri;
		int siz;
		S sum;
		bool rev;
		Node(S v, int p) :val(v), pri(p), siz(1), sum(v), rev(false) {
			lch = nullptr;
			rch = nullptr;
		}
	};
	Node* root;

	int size(Node* t) {
		if (t == nullptr)return 0;
		return t->siz;
	}
	S prod(Node* t) {
		if (t == nullptr)return e();
		return t->sum;
	}

	void push(Node* t) {
		if (t == nullptr)return;
		if (t->rev) {
			swap(t->lch, t->rch);
			if (t->lch)t->lch->rev ^= true;
			if (t->rch)t->rch->rev ^= true;
			t->rev = false;
		}
	}

	Node* update(Node* t) {
		t->siz = size(t->lch) + size(t->rch) + 1;
		t->sum = op(op(prod(t->lch), prod(t->rch)), t->val);
		return t;
	}

	Node* merge(Node* l, Node* r) {
		push(l);
		push(r);
		if (l == nullptr)return r;
		if (r == nullptr)return l;

		if (l->pri > r->pri) {
			l->rch = merge(move(l->rch), move(r));
			return update(move(l));
		}
		else {
			r->lch = merge(move(l), move(r->lch));
			return update(move(r));
		}
	}

	pair<Node*, Node*> split(Node* t, int k) {
		if (t == nullptr)return { nullptr,nullptr };

		push(t);
		if (k <= size(t->lch)) {
			pair<Node*, Node*> s = split(move(t->lch), k);
			t->lch = move(s.second);
			return { move(s.first),update(move(t)) };
		}
		else {
			pair<Node*, Node*> s = split(move(t->rch), k - size(t->lch) - 1);
			t->rch = move(s.first);
			return { update(move(t)),move(s.second) };
		}
	}

	Node* insert(Node* t, int k, S v) {
		auto [l, r] = split(move(t), k);
		Node* ret = merge(move(l), new Node(v, rnd.random()));
		ret = merge(move(ret), move(r));
		return ret;
	}

	Node* erase(Node* t, int k) {
		auto [l, r_aux] = split(move(t), k);
		auto [m, r] = split(move(r_aux), 1);
		delete m;
		return merge(move(l), move(r));
	}

	void reverse(Node* t, int l, int r) {
		auto [b_aux, c] = split(move(t), r);
		auto [a, b] = split(move(b_aux), l);
		if (b != nullptr)b->rev ^= true;
		auto t_aux = merge(move(a), move(b));
		t = merge(move(t_aux), move(c));
	}

	void rotate(Node* t, int l, int m, int r) {
		reverse(t, l, r);
		reverse(t, l, l + r - m);
		reverse(t, l + r - m, r);
	}

public:

	int size() {
		return size(root);
	}

	void insert(int k, S v) {
		assert(0 <= k and k <= size(root));
		root = insert(move(root), k, v);
	}

	void erase(int k) {
		assert(0 <= k and k < size(root));
		root = erase(move(root), k);
	}

	S prod(int l, int r) {
		assert(0 <= l and l <= r and r <= size(root));
		auto [a, b] = split(move(root), r);
		auto [c, d] = split(move(a), l);

		S ret = prod(d);

		root = merge(merge(move(c), move(d)), move(b));

		return ret;
	}

	S operator[](int k) {
		assert(0 <= k and k < size(root));
		return prod(k, k + 1);
	}

	void reverse(int l, int r) {
		assert(0 <= l and l <= r and r <= size(root));
		reverse(root, l, r);
	}

	void rotate(int l, int m, int r) {
		assert(0 <= l and l <= m and m <= r and r <= size(root));
		rotate(root, l, m, r);
	}

	void debug() {
		int n = size(root);
		if (n > 0)push(root);
		for (int i = 0; i < n; ++i) {
			cerr << (*this)[i] << " ";
		}
		cerr << endl;
	}
};
