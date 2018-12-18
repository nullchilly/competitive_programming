struct line {
	ll a, b;
} tree[N << 3];
 
struct lichao {
 
	lichao() {
		for (int i = 1; i < N << 3; i++) {
			tree[i].a = LLONG_MAX;
		}
	}
 
	ll y(line l, ll x) {
		if (l.a == LLONG_MAX) {
			return LLONG_MAX;
		}
		return l.a * x + l.b;
	}
 
	void update(line x, int id = 1, int l = -1e5, int r = N) {
		int mid = (l + r) >> 1;
		bool i1 = y(x, l) < y(tree[id], l);
		bool i2 = y(x, mid) < y(tree[id], mid);
		if (i2) {
			swap(tree[id], x);
		}
		if (r - l == 1) {
			return;
		} else if (i1 != i2) {
			update(x, id << 1, l, mid);
		} else {
			update(x, (id << 1) | 1, mid, r);
		}
	}
 
	ll query(int x, int id = 1, int l = -1e5, int r = N) {
		int mid = (l + r) >> 1;
		if (r - l == 1) {
			return y(tree[id], x);
		} else if (x < mid) {
			return min(y(tree[id], x), query(x, id << 1, l, mid));
		} else {
			return min(y(tree[id], x), query(x, (id << 1) | 1, mid, r));
		}
	}
 
} s;
