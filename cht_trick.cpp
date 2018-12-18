struct line {

	ll a, b;
	vector<line> cht;

	void reset() {
		cht.clear();
	}

	bool cross(line l1, line l2, line l3) {
		return 1.0 * (l3.b - l1.b) / (l1.a - l3.a) <= 1.0 * (l2.b - l1.b) / (l1.a - l2.a);
	}

	void add(line a) {
		while (cht.size() >= 2 && cross(cht[cht.size() - 2], cht.back(), a)) {
			cht.pop_back();
		}
		cht.push_back(a);
	}

	ll y(int i, ll x) {
		return cht[i].a * x + cht[i].b;
	}

	ll query(ll x) {
		int l = 0, r = cht.size() - 1;
		ll ans = -LLONG_MAX;
		while (l <= r) {
			int mid = (l + r) >> 1;
			ll cur = y(mid, x);
			ans = max(ans, cur);
			if (mid != (int)cht.size() - 1 && y(mid + 1, x) > cur) {
				l = mid + 1;
			} else if (mid != 0 && y(mid - 1, x) > cur) {
				r = mid - 1;
			} else {
				break;
			}
		}
		return ans;
	}

} s;
