#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 3, mod = (int)1e9 + 7;
int n, p[maxn], pL[maxn], pR[maxn];
int pos[maxn];
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", p + i);
			pL[i] = i - 1;
			pR[i] = i + 1;
			pos[p[i]] = i;
		}
		pR[0] = 1;
		pL[n + 1] = n;
		bool chk = 1;
		multiset<int> Hash;
		for(int i = 1; i <= n; ++i)
			Hash.insert(1);
		for(int i = 1; i <= n; ++i) {
			int u = pos[i], v = pL[u];
			if(u - v != *Hash.rbegin()) {
				fprintf(stderr, "halted %d\n", i);
				chk = 0;
				break;
			}
			int w = pR[u];
			pR[v] = w;
			pL[w] = v;
			Hash.erase(Hash.find(u - v));
			if(w <= n) {
				Hash.erase(Hash.find(w - u));
				Hash.insert(w - v);
			}
		}
		puts(chk ? "Yes" : "No");
	}
	return 0;
}