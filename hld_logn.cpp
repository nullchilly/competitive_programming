#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll N = 5e5 + 5;

int n, q;
int id, sz[N], par[N], p[N], V[N], rt[N], d[N];
int L[N], R[N], up[N], h[N];
ll a[N], t[N];
basic_string<int> g[N];

void dfs(int v, int p = 0) {
  for (auto &u : g[v]) {
    g[u].erase(find(begin(g[u]), end(g[u]), v));
    par[u] = v, h[u] = h[v] + 1, dfs(u), sz[v] += sz[u];
    if (sz[g[v][0]] < sz[u]) swap(g[v][0], u);
  }
}

void build(int &i, int p, int l, int r) {
  for (int m = l, s = sz[V[l]] + !g[V[r]].empty() * sz[V[r + 1]]; m <= r; m++) {
    if (s > 2 * sz[V[m + 1]]) {
      i = V[m], d[i] = d[p] + 1, up[i] = p;
      build(L[i], i, l, m - 1);
      build(R[i], i, m + 1, r);
      t[i] = t[L[i]] + a[i] + t[R[i]];
      return;
    }
  }
}

void hld(int v) {
  p[v] = ++id, V[id] = v;
  for (auto &u : g[v]) {
    rt[u] = (u == g[v][0] ? rt[v] : u);
    hld(u);
  }
  if (g[v].empty()) build(v, 0, p[rt[v]], p[v]);
}

void upd(int i, int w) {
  a[i] += w;
  do t[i] += w; while ((i = up[i]));
}

ll que(int u) {
  int ou = R[u];
  ll ans = 0;
  do if (R[u] == ou) ans += t[L[u]] + a[u]; while ((u = up[ou = u]));
  return ans;
}

ll que(int u, int v) {
  int ou = L[u], ov = R[v];
  ll ans = 0;
  auto upR = [&] {
    if (ou == L[u]) ans += t[R[u]] + a[u];
    u = up[ou = u];
  };
  auto upL = [&] {
    if (ov == R[v]) ans += t[L[v]] + a[v];
    v = up[ov = v];
  };
  while (d[u] > d[v]) upR();
  while (d[u] < d[v]) upL();	
  while (u != v) upR(), upL();
  return ans + a[u];
}

ll quy(int u, int v, ll ans = 0) {
  for (; rt[u] != rt[v]; v = par[rt[v]]) {
    if (h[rt[u]] > h[rt[v]]) swap(u, v);
    ans += que(v);
  }
  if (h[u] > h[v]) swap(u, v);
  return ans + (rt[v] == u ? que(v) : que(u, v));
}

int32_t main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) sz[i] = 1, read(a[i]);
  for (int i = 1, u, v; i < n; i++) 
    cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
  dfs(1), hld(rt[1] = 1);
  for (int i = 1, t, u, v; i <= q; i++) {
    cin >> t >> u >> v;
    if (t) cout << quy(u, v) << '\n';
    else upd(u, v);
  }
}
