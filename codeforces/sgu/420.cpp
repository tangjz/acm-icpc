#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL getPrev(LL x) {
	static char buf[31];
	int len = sprintf(buf, "%lld", x);
	if(prev_permutation(buf, buf + len) && buf[0] != '0')
		sscanf(buf, "%lld", &x);
	return x;
}
LL getNext(LL x) {
	static char buf[31];
	int len = sprintf(buf, "%lld", x);
	if(next_permutation(buf, buf + len))
		sscanf(buf, "%lld", &x);
	return x;
}
int main() {
	LL L, R;
	scanf("%lld%lld", &L, &R);
	set<LL> ans;
	// xy yx
	for(int x = 1; x < 9; ++x)
		for(int y = x + 1; y <= 9; ++y) {
			int p = x * 10 + y, q = y * 10 + x;
			if(L <= p && q <= R)
				ans.insert(p);
		}
	// min(dis) < maxd
	static const int maxd = (int)1e3;
	for(int d = 0; d < maxd && L + d <= R; ++d) {
		LL p = L + d, q = getNext(p), tmp;
		if(p == q || q > R)
			continue;
		if((tmp = getPrev(p)) != p && tmp >= L)
			continue;
		if((tmp = getNext(q)) != q && tmp <= R)
			continue;
		ans.insert(p);
	}
	for(int d = 0; d < maxd && R - d >= L; ++d) {
		LL q = R - d, p = getPrev(q), tmp;
		if(p == q || p < L)
			continue;
		if((tmp = getNext(q)) != q && tmp <= R)
			continue;
		if((tmp = getPrev(p)) != p && tmp >= L)
			continue;
		ans.insert(p);
	}
	// ..xyy (L|R) ..yxy || ..xyx (L|R) ..yxx
	for(int o = 0; o < 2; ++o)
		for(int x = 0; x < 9; ++x)
			for(int y = x + 1; y <= 9; ++y) {
				int z = o ? x : y;
				for(LL low = x * 10 + y, upp = y * 10 + x, pw = 100; low <= R; low = low * 10 + z, upp = upp * 10 + z, pw *= 10) {
					LL sL = L % pw;
					if(low < sL && sL <= upp && (x || L >= pw)) {
						LL p = L - sL + upp, q = getNext(p), tmp;
						if(p == q || q > R)
							continue;
						if((tmp = getPrev(p)) != L - sL + low)
							continue;
						if((tmp = getNext(q)) != q && tmp <= R)
							continue;
						ans.insert(p);
					}
				}
				for(LL low = x * 10 + y, upp = y * 10 + x, pw = 100; low <= R; low = low * 10 + z, upp = upp * 10 + z, pw *= 10) {
					LL sR = R % pw;
					if(low <= sR && sR < upp && (x || R >= pw)) {
						LL q = R - sR + low, p = getPrev(q), tmp;
						if(p == q || p < L)
							continue;
						if((tmp = getNext(q)) != R - sR + upp)
							continue;
						if((tmp = getPrev(p)) != p && tmp >= L)
							continue;
						ans.insert(p);
					}
				}
			}
	printf("%d\n", (int)ans.size() * 2);
	return 0;
}