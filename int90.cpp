#include "bits/stdc++.h"
using ll = long long;
using namespace std;
 
const int N = 2e5 + 5, MAX = 1e9, mod = 1e9 + 7;

const ll nine = 1e9;

struct __int90 {
	pair <ll, ll> a;
	bool operator < (__int90 y) {
		if (a.first < y.a.first || (a.first == y.a.first && a.second < y.a.second)) {
			return 1;
		}
		return 0;
	}
	bool operator > (__int90 y) {
		if (a.first > y.a.first || (a.first == y.a.first && a.second > y.a.second)) {
			return 1;
		}
		return 0;
	}
	bool operator <= (__int90 y) {
		if (a.first > y.a.first || (a.first == y.a.first && a.second > y.a.second)) {
			return 0;
		}
		return 1;
	}
	bool operator >= (__int90 y) {
		if (a.first < y.a.first || (a.first == y.a.first && a.second < y.a.second)) {
			return 1;
		}
		return 0;
	}
	bool operator == (__int90 y) {
		return a == y.a;
	}
	bool operator != (__int90 y) {
		return a != y.a;
	}
	__int90 operator + (__int90 y) {
		__int90 ans;
		ans.a = {a.first + y.a.first + (a.second + y.a.second) / nine, (a.second + y.a.second) % nine};
		return ans;
	}
	__int90 operator - (__int90 y) {
		__int90 ans;
		if (a.second < y.a.second) {
			ans.a = {a.first - y.a.first - 1 + (a.second - y.a.second + nine) / nine, (a.second - y.a.second + nine) % nine};
		} else {
			ans.a = {a.first - y.a.first + (a.second - y.a.second) / nine, (a.second - y.a.second) % nine};
		}
		return ans;
	}
	__int90 operator * (__int90 y) {
		__int90 ans;
		ans.a = {a.first * y.a.first * nine + a.second * y.a.first + a.first * y.a.second + a.second * y.a.second / nine, (a.second * y.a.second) % nine};
		return ans;
	}
	__int90 operator / (__int90 y) {
		__int90 x = {a};
		__int90 l = {{0, 0}}, r = {{3e4, 0}};
		while (true) {
			if (l == r) {
				return l;
			} else if (l + __int90{{0, 1}} == r) {
				if (r * y <= x) {
					return r;
				}
				return l;
			}
			__int90 mid = l + r;
			if (mid.a.first % 2 != 0) {
				mid = mid + __int90{{0, nine}};
			}
			mid.a.first /= 2;
			mid.a.second /= 2;
			if (mid * y <= x) {
				l = mid;
			} else {
				r = mid - __int90{{0, 1}};
			}
		}
		return l;
	}
	void operator += (__int90 y) {
		a = (__int90{a} + y).a;
	}
	void operator -= (__int90 y) {
		a = (__int90{a} - y).a;
	}
	void operator *= (__int90 y) {
		a = (__int90{a} * y).a;
	}
	void operator /= (__int90 y) {
		a = (__int90{a} / y).a;
	}
};

ostream& operator << (ostream &os, __int90 const& ans) {
	if (ans.a.first == 0) return os << ans.a.second;
	return os << ans.a.first << setw(9) << setfill('0') << ans.a.second;
}

int main() {
	__int90 a = {{3e4, 1e9}}, b = {{3e4, 0}};
	cout << a << ' ' << b << '\n';
	// 300001000000000 30000000000000
	cout << a + b << ' ' << a - b << '\n';
	// 60001000000000 1000000000
	cout << a * b << ' ' << a / b << '\n';
	// 900030000000000000000000000 1
	cout << (a > b) << ' ' << (a == a) << '\n'; // 1 1
	cout << (a < b) << ' ' << (a != a) << '\n'; // 0 0
}
