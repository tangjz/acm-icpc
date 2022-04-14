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

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

vector<int> perform(int n, int perm[]) {
	static int pos[maxn];
	for(int i = 0; i < n; ++i)
		pos[perm[i]] = i;
	// printf("perform: ");
	// for(int i = 0; i < n; ++i)
	// 	printf("%d%c", perm[i], " \n"[i == n - 1]);
	for(int i = 1; i < n; ++i)
		if(pos[i - 1] > pos[i]) {
			vector<int> ret;
			int L = pos[i], R = pos[i - 1];
			int adt = 1;
			while(L + adt < n && perm[L + adt] == perm[L] + adt)
				++adt;
			if(L > 0)
				ret.push_back(L);
			ret.push_back(adt);
			ret.push_back(R - L + 1 - adt);
			if(R < n - 1)
				ret.push_back(n - 1 - R);
			int tot = 0;
			static int nxt[maxn];
			// printf("action:");
			for(int x : ret) {
				// printf(" %d", x);
				int sta = n - tot - x;
				for(int j = 0; j < x; ++j)
					nxt[sta + j] = perm[tot + j];
				tot += x;
			}
			// puts("");
			memcpy(perm, nxt, n * sizeof(int));
			return ret;
		}
	return {};
}

void solve() {
	int n;
	static int a[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		--a[i];
	}
	vector<vector<int> > out;
	while(1) {
		vector<int> seg = perform(n, a);
		if(seg.empty())
			break;
		out.push_back(seg);
	}
	printf("%d\n", (int)out.size());
	for(auto &vec : out) {
		printf("%d", (int)vec.size());
		for(int x : vec)
			printf(" %d", x);
		printf("\n");
	}
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