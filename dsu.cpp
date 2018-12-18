struct dsu_orz {
	int up[N], sz[N];
	
	void init() {
		for (int i = 1; i <= n; i++) {
			up[i] = i;
			sz[i] = 1;
		}
	}
	
	int find(int v) {
		if (up[v] == v) {
			return v;
		}
		return find(up[v]);
	}
	 
	void merge(int u, int v) {	
		int uwu = find(u), ovo = find(v);
		if (sz[uwu] > sz[ovo]) {
			swap(uwu, ovo);
		}
		if (uwu != ovo) {
			up[uwu] = ovo;
			sz[ovo] += sz[uwu];
		}
	}
	
	int get_size(int v) {
		return sz[find(v)];
	}
	
} dsu;
