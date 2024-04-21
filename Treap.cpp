template<class S, S(*op)(S, S), S(*e)()>
class Treap{
	struct Node {
		S val;
		unique_ptr<Node> lch, rch;
		int pri;
		int siz;
		S sum;
		bool rev;
		Node(S v, int p) :val(v), pri(p), siz(1), sum(v), rev(false) {
			lch = nullptr;
			rch = nullptr;
		}
	};
	unique_ptr<Node> root;

	int size(unique_ptr<Node>& t) {
		if (t == nullptr)return 0;
		return t->siz;
	}
	S prod(unique_ptr<Node>& t) {
		if (t == nullptr)return e();
		return t->sum;
	}

	void push(unique_ptr<Node>& t) {
		if (t == nullptr)return;
		if (t->rev) {
			swap(t->lch, t->rch);
			if (t->lch)t->lch->rev ^= true;
			if (t->rch)t->rch->rev ^= true;
			t->rev = false;
		}
	}

	unique_ptr<Node> update(unique_ptr<Node> t) {
		t->siz = size(t->lch) + size(t->rch) + 1;
		t->sum = op(op(prod(t->lch), prod(t->rch)), t->val);
		return t;
	}

	unique_ptr<Node> merge(unique_ptr<Node> l, unique_ptr<Node> r) {
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

	pair<unique_ptr<Node>, unique_ptr<Node>> split(unique_ptr<Node> t, int k) {
		if (t == nullptr)return { nullptr,nullptr };

		push(t);
		if (k <= size(t->lch)) {
			pair<unique_ptr<Node>, unique_ptr<Node>> s = split(move(t->lch), k);
			t->lch = move(s.second);
			return { move(s.first),update(move(t)) };
		}
		else {
			pair<unique_ptr<Node>, unique_ptr<Node>> s = split(move(t->rch), k - size(t->lch) - 1);
			t->rch = move(s.first);
			return { update(move(t)),move(s.second) };
		}
	}

	unique_ptr<Node> insert(unique_ptr<Node> t, int k, S v) {
		auto [l, r] = split(move(t), k);
		unique_ptr<Node> ret = merge(move(l), make_unique<Node>(v, rand()));
		ret = merge(move(ret), move(r));
		return ret;
	}

	unique_ptr<Node> erase(unique_ptr<Node> t, int k) {
		auto [l, r_aux] = split(move(t), k);
		auto [m, r] = split(move(r_aux), 1);
		return merge(move(l), move(r));
	}

	void reverse(unique_ptr<Node>& t, int l, int r) {
		auto [b_aux, c] = split(move(t), r);
		auto [a, b] = split(move(b_aux), l);
		if (b != nullptr)b->rev ^= true;
		auto t_aux = merge(move(a), move(b));
		t = merge(move(t_aux), move(c));
	}

	void rotate(unique_ptr<Node>& t, int l, int m, int r) {
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

	int prod(int l, int r) {
		assert(0 <= l and l <= r and r <= size(root));
		auto [a, b] = split(move(root), r);
		auto [c, d] = split(move(a), l);

		int ret = prod(d);

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
