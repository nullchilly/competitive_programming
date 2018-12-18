struct LCA_orz {

	int id = 0;
	int h[N], tin[M], tout[M], euler[M], LOG[M];

	struct node {
		int h, v;
		bool operator < (const node &o) const {
			return h < o.h;
		}
	} mn[18][M];

	void dfs(int v) {
		euler[++id] = v;
		for (auto u : adj[v]) {
			if (h[u] == 0) {
				h[u] = h[v] + 1;
				dfs(u);
				euler[++id] = v;
			}
		}
	}

	void setup() {
		for (int i = 1; i < M; ++i) {
			LOG[i] = (i & 1) ? LOG[i - 1] : LOG[i >> 1] + 1;
		}
		for (int j = 0; j <= 17; ++j) {
			for (int i = 1; i <= id; ++i) {
				mn[j][i].h = INT_MAX;
			}
		}
		dfs(h[1] = 1);
		memset(tin, 0x3f, sizeof tin);
		for (int i = 1; i <= id; ++i) {
			int x = euler[i];
			tin[x] = min(tin[x], i);
			tout[x] = max(tout[x], i);
			mn[0][i] = {h[x], x};
		}
		for (int j = 1; j <= 17; ++j) {
			for (int i = 1; i <= id - (1 << j) + 1; ++i) {
				mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	int get_min(int l, int r) {
		int k = LOG[r - l + 1];
		return min(mn[k][l], mn[k][r - (1 << k) + 1]).v;
	}

	int get(int u, int v) {
		return get_min(min(tin[u], tin[v]), max(tout[u], tout[v]));
	}

} LCA;
