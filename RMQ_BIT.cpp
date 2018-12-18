#include "bits/stdc++.h"
using namespace std;

const int N = 2e5 + 2;

int n, q, a[N], BIT1[N], BIT2[N], dpl[N], dpr[N];

void update(int p, int v) {
	int cur = p + 1;
	a[p] = v, v = INT_MAX;
	while (cur <= n) {
		int lsb = cur & -cur;
		v = min(v, BIT2[cur]);
		cur += lsb;
		dpr[cur] = v;
	}
	v = INT_MAX, cur = p - 1;
	while (cur) {
		int lsb = cur & -cur;
		v = min(v, BIT1[cur]);
		cur -= lsb;
		dpl[cur] = v;
	}
	cur = p;
	while (cur <= n) {
		int lsb = cur & -cur;
		BIT1[cur] = a[cur];
		if (cur - lsb + 1 <= p - 1) {
			BIT1[cur] = min(BIT1[cur], dpl[cur - lsb]);
		}
		if (cur >= p + 1) {
			BIT1[cur] = min(BIT1[cur], dpr[cur]);
		}
		cur += lsb;
	}
	cur = p;
	while (cur) {
		int lsb = cur & -cur;
		BIT2[cur] = a[cur];
		if (cur <= p - 1) {
			BIT2[cur] = min(BIT2[cur], dpl[cur]);
		}
		if (cur + lsb - 1 >= p + 1) {
			BIT2[cur] = min(BIT2[cur], dpr[cur + lsb]);
		}
		cur -= lsb;
	}
}

int query(int l, int r) {
	int ans = INT_MAX;
	while (true) {
		int lsb = l & -l;
		if (l + lsb > n) break;
		ans = min(ans, BIT2[l]);
		l += lsb;
	}
	ans = min(ans, a[l]);
	while (true) {
		int lsb = r & -r;
		if (r - lsb < 1) break;
		ans = min(ans, BIT1[r]);
		r -= lsb;
	}
	return ans;
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	memset(BIT1, 0x3f, sizeof BIT1);
	memset(BIT2, 0x3f, sizeof BIT2);
	memset(dpl, 0x3f, sizeof dpl);
	memset(dpr, 0x3f, sizeof dpr);
	a[0] = a[n + 1] = INT_MAX;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		update(i, a[i]);
	}
	while (q--) {
		int type, l, r;
		cin >> type >> l >> r;
		if (type == 1) {
			update(l, r);
		} else {
			cout << query(l, r) << '\n';
		}
	}
}
