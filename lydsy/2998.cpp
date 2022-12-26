#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL getPrev(LL x) {
	static char buf[31];
	int len = sprintf(buf, "%lld", x);
	if(prev_permutation(buf, buf + len) && buf[0] != '0')
		sscanf(buf, "%lld", &x);
	return x;
}
inline LL getNext(LL x) {
	static char buf[31];
	int len = sprintf(buf, "%lld", x);
	if(next_permutation(buf, buf + len))
		sscanf(buf, "%lld", &x);
	return x;
}
LL L, R;
set<LL> ans;
inline void checkLeft(LL p) {
	LL q = getNext(p), tmp;
	if(p != q && q <= R && ((tmp = getPrev(p)) == p || tmp < L) && ((tmp = getNext(q)) == q || tmp > R))
		ans.insert(p);
}
inline void checkRight(LL q) {
	LL p = getPrev(q), tmp;
	if(p != q && p >= L && ((tmp = getNext(q)) == q || tmp > R) && ((tmp = getPrev(p)) == p || tmp < L))
		ans.insert(p);
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld", &L, &R);
		set<LL>().swap(ans);
		// min(dis) < maxd
		static const int maxd = (int)1e3;
		for(int d = 0; d < maxd && L + d <= R; checkLeft(L + (d++)));
		for(int d = 0; d < maxd && R - d >= L; checkRight(R - (d++)));
		// ..xyy (L|R) ..yxy || ..xyx (L|R) ..yxx
		for(int o = 0; o < 2; ++o)
			for(int x = 0; x < 9; ++x)
				for(int y = x + 1; y <= 9; ++y) {
					int z = o ? x : y;
					for(LL low = x * 10 + y, upp = y * 10 + x, pw = 100; low <= R; low = low * 10 + z, upp = upp * 10 + z, pw *= 10) {
						LL sL = L % pw, sR = R % pw;
						if(low < sL && sL <= upp && (x || L >= pw))
							checkLeft(L - sL + upp);
						if(low <= sR && sR < upp && (x || R >= pw))
							checkRight(R - sR + low);
					}
				}
		printf("%d\n", (int)ans.size() * 2);
	}
	return 0;
}
