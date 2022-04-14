#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)3e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);
const LL maxv = (LL)5e18;

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

struct Operation {
	char typ; // + or ^
	LL x, y;
};

LL exgcd(LL a, LL b, LL &x, LL &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	LL r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}

void solve() {
	LL n;
	scanf("%lld", &n);
	vector<Operation> out;
	auto make = [&](LL x, LL k) {
		if(k <= 1)
			return;
		LL cur = 0, mul = x;
		while(k > 0) {
			if(k & 1) {
				if(!cur) {
					cur = mul;
				} else {
					out.push_back((Operation){'+', cur, mul});
					cur += mul;
				}
			}
			k >>= 1;
			if(k > 0) {
				out.push_back((Operation){'+', mul, mul});
				mul += mul;
			}
		}
	};
	static const int maxd = 20;
	LL m;
	for(int i = maxd - 1; i >= 0; --i)
		if(n * (1 << i | 1) != (n ^ (n << i))) {
			make(n, 1 << i);
			out.push_back((Operation){'^', n, n << i});
			m = n ^ (n << i);
			break;
		}
	LL x, y;
	LL r = exgcd(n, m, x, y);
	assert(r == 1);
	make(n, abs(x));
	x = n * abs(x);
	make(m, abs(y));
	y = m * abs(y);
	LL adt = 0;
	while((x ^ y) != 1) {
		++adt;
		x += n;
		y += n;
	}
	if(adt > 0) {
		make(n, adt);
		LL tmp = n * adt;
		out.push_back((Operation){'+', x - tmp, tmp});
		out.push_back((Operation){'+', y - tmp, tmp});
	}
	out.push_back((Operation){'^', x, y});

	printf("%d\n", (int)out.size());
	for(auto &it : out)
		printf("%lld %c %lld\n", it.x, it.typ, it.y);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}