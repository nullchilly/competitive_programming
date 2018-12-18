struct segtree {
	#define lc (id << 1)
	#define rc (lc | 1)
	#define mid ((l + r) >> 1)
 
	int lazy[N << 2], tree[N << 2];
 
	void reset() {
		for (int i = 1; i < N << 2; i++) {
			tree[i] = 0;
		}
	}
 
	void push(int id, int l, int r) {
		tree[id] += lazy[id];
		if (l < r) {
			lazy[lc] += lazy[id];
			lazy[rc] += lazy[id];
		}
		lazy[id] = 0;
	}
	 
	void update(int L, int R, int V, int id = 1, int l = 1, int r = n) {
		push(id, l, r);
		if (l > R || r < L) {
			return;
		}
		if (L <= l && r <= R) {
			lazy[id] = V;
			push(id, l, r);
			return;
		}
		update(L, R, V, lc, l, mid);
		update(L, R, V, rc, mid + 1, r);
		tree[id] = max(tree[lc], tree[rc]);
	}
	
	int query(int L, int R, int id = 1, int l = 1, int r = n) {
		push(id, l, r);
		if (l > R || r < L) {
			return 0;
		}
		if (L <= l && r <= R) {
			return tree[id];
		}
		return max(query(L, R, lc, l, mid), query(L, R, rc, mid + 1, r));
	}
	
	#undef lc
	#undef rc
	#undef mid
} seg;
