#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = 128;
struct uint128 {
	unsigned long long HI, LO;
	uint128() { HI = LO = 0; }
	void operator = (int const &t) {
		HI = 0;
		LO = t;
	}
	void shiftAdd(bool const &t) {
		HI = HI << 1 | (LO >> 63);
		LO = LO << 1 | t;
	}
	bool operator == (uint128 const &t) const {
		return HI == t.HI && LO == t.LO;
	}
	bool operator < (uint128 const &t) const {
		return HI != t.HI ? HI < t.HI : LO < t.LO;
	}
} all, pos[maxn];
int n, ord[maxn];
char buf[maxn];
inline bool cmp(int const &u, int const &v) {
	return pos[u] < pos[v] || (pos[u] == pos[v] && buf[u] < buf[v]);
}
bool check(int len) {
	if(len > maxm)
		return 0;
	int cnt = n - len + 1;
	all = 0;
	for(int j = 0; j < len; ++j)
		all.shiftAdd(1);
	for(int i = 0; i < cnt; ++i) {
		ord[i] = i;
		pos[i] = 0;
		for(int j = 0; j < len; ++j)
			pos[i].shiftAdd((buf[i] == buf[i + j]));
	}
	sort(ord, ord + cnt, cmp);
	int ctr = 0;
	for(int L = 0, R; L < cnt; L = R) {
		for(R = L + 1; R < cnt && pos[ord[L]] == pos[ord[R]] && buf[ord[L]] == buf[ord[R]]; ++R);
		if(pos[ord[L]] == all)
			continue;
		for(int i = L; i < R; ++i)
			for(int j = i + 1; j < R; ++j) {
				int u = ord[i], v = ord[j];
				bool chk = 1;
				for(int k = 0; k < len; ++k)
					if(buf[u + k] == buf[v + k] && buf[u + k] != buf[u]) {
						chk = 0;
						break;
					}
				if(chk)
					return 1;
			}
	}
	return 0;
}
int main() {
	scanf("%d%s", &n, buf);
	int mx = 0;
	for(int i = 0, j; i < n; i = j) {
		for(j = i + 1; j < n && buf[i] == buf[j]; ++j);
		mx = max(mx, j - i);
	}
	int L = mx, R = mx << 1;
	for( ; L < R && check(R); L = R, R = min(R << 1, n));
	while(L < R) {
		int M = (L + R + 1) >> 1;
		if(check(M)) {
			L = M;
		} else {
			R = M - 1;
		}
	}
	for( ; L <= mx && L > 0 && !check(L); --L);
	printf("%d\n", L - (n == maxn - 1));
	return 0;
}