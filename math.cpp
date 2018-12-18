#include "bits/stdc++.h"
using ll = long long;
using namespace std;
 
const ll N = 2e5 + 5, MAX = 1e18, mod = 1e9 + 7;

ll add(ll a, ll b) {
	return (a % mod + b % mod) % mod;
}

ll sub(ll a, ll b) {
	return (a % mod + b % mod + mod * 2) % mod;
}

ll mul(ll a, ll b) {
	return (a % mod * b % mod) % mod;
}
 
ll npow(ll x, ll k) {
	ll res = 1;
	while (k) {
		if (k & 1) {
			if (x && MAX / x < res) return LLONG_MAX;
			res = res * x;
		}
		if (x && MAX / x < x) x = 0;
		x = x * x;
		k >>= 1;
	}
	if (res == 0) {
		return LLONG_MAX;
	}
	return res;
}
 
ll binpow(ll x, ll k) {
	ll res = 1;
	while (k) {
		if (k & 1) {
			res = mul(res, x);
		}
		x = mul(x, x);
		k >>= 1;
	}
	return res;
}

bool prime(int n) {
	if (n < 2) return 0;
	if (n == 2) return 1;
	int s = sqrt(n);
	for (int i = 2; i <= s; ++i) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}
 
int main() {
	cout << binpow(1e9, 1e9) << '\n'; // 312556845
	cout << npow(1e9, 1e9) << '\n'; // LLONG_MAX
	cout << prime(4) << ' ' << prime(1e9 + 7); // 0 1
}
