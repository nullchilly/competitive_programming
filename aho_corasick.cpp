struct aho_corasick {
	
#define A 26
	int n = 0, sz = 0;
	int sizes[N];
	int child[N][A + 1];
	int nxt[N][A + 1], fail[N];
	int fl[N];
	vector<int> id[N];
	vector<int> occur[N];

#define m(a) memset(a, 0, sizeof a)
	void reset() {
		n = sz = 0;
		m(sizes), m(child), m(nxt), m(fail), m(fl);
		for (int i = 0; i < N; i++) {
			id[i].clear();
			occur[i].clear();
		}
	}
#undef m

	void add(string& s) {
		int ptr = 0;
		for (auto& ch : s) {
			int c = ch - 'a';
			if (!child[ptr][c]) {
				child[ptr][c] = ++sz;
			}
			ptr = child[ptr][c];
		}
		n++;
		sizes[n] = s.size();
		id[ptr].push_back(n);
	}
	
	void bfs() {
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (!id[fail[u]].empty()) {
				fl[u] = fail[u];
			} else {
				fl[u] = fl[fail[u]];
			}
			for (int i = 0; i < A; i++) {
				int v = child[u][i];
				nxt[u][i] = nxt[fail[u]][i];
				if (v) {
					fail[v] = nxt[u][i];
					nxt[u][i] = v;
					q.push(v);
				}
			}
		}
	}
	
	void fun(string& t) {
		int ptr = 0;
		for (int i = 0; i < t.size(); i++) {
			int ch = t[i] - 'a';
			ptr = nxt[ptr][ch];
			for (auto& cid : id[ptr]) {
				occur[cid].push_back(i);
			}
			int curp = ptr;
			while (ptr) {
				ptr = fl[ptr];
				for (auto& cid : id[ptr]) {
					occur[cid].push_back(i);
				}
			}
			ptr = curp;
		}
		for (int i = 1; i <= n; i++) {
			for (auto& id : occur[i]) {
				cout << id - sizes[i] + 1 << ' ';
			}
			cout << '\n';
		}
	}
#undef A
	
} aho;
