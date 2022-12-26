#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, MINS_PER_HOUR = 60, MINS_PER_DAY = MINS_PER_HOUR * 24;
int n, szA, szB;
struct Arc {
	int L, R;
	void read() {
		int h1, m1, h2, m2;
		scanf("%d:%d-%d:%d", &h1, &m1, &h2, &m2);
		L = h1 * MINS_PER_HOUR + m1;
		R = h2 * MINS_PER_HOUR + m2;
	}
	void shift(int const &delta) { // delta in [0, MINS_PER_DAY]
		(L += delta) >= MINS_PER_DAY && (L -= MINS_PER_DAY);
		(R += delta) >= MINS_PER_DAY && (R -= MINS_PER_DAY);
	}
	bool operator < (Arc const &t) const {
		return R < t.R;
	}
} a[maxn], segA[maxn], segB[maxn];
int main() {
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case) {
		for(int i = 0; i < n; ++i) {
			a[i].read();
			assert(a[i].L != a[i].R);
		}
		int ans = 0;
		for(int i = 0; i < n; ++i) {
			int delta = a[i].L, cnt = 0;
			for(int j = 0; j < n; ++j)
				a[j].shift(MINS_PER_DAY - delta);
			// now, a[i] = (0, R)
			szA = szB = 0;
			for(int j = 0; j < n; ++j)
				if(a[i].R <= a[j].R && (!a[j].L || a[j].R < a[j].L)) { // a[j].contain(a[i])
					++cnt;
				} else if(a[j].L < a[j].R && a[j].R <= a[i].R) { // a[i].contain(a[j])
					;
				} else if(a[i].R <= a[j].L && (!a[j].R || a[j].L < a[j].R)) { // !a[i].intersect(a[j])
					;
				} else if(a[j].L <= a[i].R && a[j].R <= a[i].R) { // a[i].contain(reverse(a[j]))
					++cnt;
				} else if(a[j].L < a[j].R) {
					segA[szA++] = a[j];
				} else {
					segB[szB++] = (Arc){a[j].R, a[j].L};
				}
			sort(segA, segA + szA);
			sort(segB, segB + szB);
			cnt += szA;
			multiset<int> sp;
			for(int i = 0, j = 0; i < szB; ++i) {
				for( ; j < szA && segA[j].R <= segB[i].R; ++j)
					sp.insert(segA[j].L);
				multiset<int>::iterator it = sp.lower_bound(segB[i].L);
				if(it == sp.end()) {
					++cnt;
				} else {
					sp.erase(it);
				}
			}
			if(ans < cnt)
				ans = cnt;
			for(int j = 0; j < n; ++j)
				a[j].shift(delta);
		}
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
