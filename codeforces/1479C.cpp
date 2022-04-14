#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
 
const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 9, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);
 
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
 
inline void query(vector<int> &seq, int pos) {
	if(!seq[pos]) {
		int &val = seq[pos];
		printf("? %d\n", pos);
		fflush(stdout);
		scanf("%d", &val);
	}
}
inline bool check(vector<int> &seq, int pos) {
	query(seq, pos);
	query(seq, pos - 1);
	query(seq, pos + 1);
	if(seq[pos] < seq[pos - 1] && seq[pos] < seq[pos + 1]) {
		printf("! %d\n", pos);
		return 1;
	}
	return 0;
}
 
void solve() {
	int low, upp;
	scanf("%d%d", &low, &upp);
	int len = upp - low + 1;
	const int maxn = 32;
	int n = 2;
	static int e[maxn + 1][maxn + 1];
	memset(e, 0, sizeof e);
	e[1][0] = 1;
	for(int i = 1; (1 << i) <= len; ++i, ++n) {
		e[i + 1][i] = 1 << (i - 1);
		for(int j = 0; j < i; ++j)
			e[i + 1][j] = e[i][j];
	}
	int S;
	if((1 << (n - 2)) == len && low == 1) {
		S = n - 1;
	} else {
		S = n++;
		for(int i = n - 2; i >= 1; --i) {
			int val = 1 << (i - 1);
			if(val > len)
				continue;
			int adt = upp - val;
			if(adt > 0) {
				e[S][i] = adt;
			} else {
				for(int j = 0; j < i; ++j)
					e[S][j] = e[i][j];
			}
			upp -= val;
			len -= val;
		}
	}
	int m = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < i; ++j)
			m += e[i][j] > 0;
	printf("YES\n");
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < i; ++j)
			if(e[i][j] > 0)
				printf("%d %d %d\n", n - i, n - j, e[i][j]);
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