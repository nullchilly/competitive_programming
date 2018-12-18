struct euler_orz {

	int id, tin[N], tout[N];

	void dfs(int v, int p) {
		tin[v] = ++id;
		for (auto u : adj[v]) {
			if (u != p) {
				dfs(u, v);
				child[v].push_back(u);
			}
		}
		tout[v] = ++id;
	}

	void setup() {
		dfs(1, 0);
	}

	bool contain(int v, int u) {
		return tin[v] < tin[u] && tout[u] < tout[v];
	}

	int child_in_simple_path(int v, int u) {
		return *--upper_bound(child[v].begin(), child[v].end(), u, [this](int u, int v) {
			return tin[u] < tin[v];
		});
	}

	void update(int v, int x) {
		seg.update(1, 1, id, tin[v], tin[v], x);
		seg.update(1, 1, id, tout[v], tout[v], x);
	}

	void update_subtree(int v, int x) {
		seg.update(1, 1, id, tin[v], tout[v], x);
	}

	ll query(int v) {
		return seg.query(1, 1, id, tin[v], tout[v]) >> 1;
	}

} tree;
