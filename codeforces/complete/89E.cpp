#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)1e3 + 1, maxm = (int)1e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, tot = maxm;
	static int a[maxn] = {}, b[maxn] = {};
	static char buf[maxm], out[maxm] = {};
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for( ; n > 0 && !a[n]; --n);
	for(int M = 0; M <= n; ++M) {
		memcpy(b + 1, a + 1, n * sizeof(int));
		int m = 0, fir = n + 1, pos = -1;
		for(int i = 1; i <= M && m <= tot; ++i) {
			if(!b[i])
				continue;
			int j = i;
			for( ; j < M && b[j + 1] >= b[i]; ++j);
			for( ; pos < j - 1; ++pos) {
				buf[m++] = 'A';
				buf[m++] = 'R';
			}
			buf[m++] = 'A';
			for( ; pos >= i - 1; --pos) {
				if(b[pos + 1] > 0)
					--b[pos + 1];
				buf[m++] = 'L';
			}
			buf[m++] = 'A';
			--i;
		}
		for(int i = M + 1; i <= n; ++i)
			if(b[i]) {
				fir = i;
				break;
			}
		for(int upp = n; upp >= fir && m <= tot; ) {
			int L = upp;
			bool blocked = 0;
			for( ; b[L] > 0; --L)
				if(b[L] > 1) {
					blocked = 1;
				} else if(blocked) {
					break;
				}
			while(!blocked && L >= fir) {
				for( ; !b[L]; --L);
				for( ; b[L] > 0; --L)
					if(b[L] > 1) {
						blocked = 1;
					} else if(blocked) {
						break;
					}
			}
			for( ; pos < upp - 1; ++pos) {
				buf[m++] = 'A';
				buf[m++] = 'R';
			}
			buf[m++] = 'A';
			for( ; pos >= L; --pos) {
				if(b[pos + 1] > 0)
					--b[pos + 1];
				buf[m++] = 'L';
			}
			buf[m++] = 'A';
			for( ; upp > M && !b[upp]; --upp);
		}
		if(m < tot) {
			buf[m] = '\0';
			strcpy(out, buf);
			tot = m;
		}
	}
	puts(out);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}