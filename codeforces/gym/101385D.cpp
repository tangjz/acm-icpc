#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int maxn = 51, maxm = 101, mod = 1000000007;
int alen, blen;
LL amsk[2], bmsk[2];
char a[maxn], b[maxn];
unordered_map<LL, int> f, g;
int main() {
	freopen("interleave.in", "r", stdin);
	freopen("interleave.out", "w", stdout);
	scanf("%s%s", a + 1, b + 1);
	alen = strlen(a + 1);
	blen = strlen(b + 1);
	if(blen < alen) {
		swap(a, b);
		swap(alen, blen);
	}
	for(int i = 1; i <= alen; ++i)
		amsk[a[i] == '1'] |= 1LL << i;
	f[1] = 1;
	for(int i = 1; i <= alen + blen; ++i) {
		unordered_map<LL, int>().swap(g);
		bmsk[0] = bmsk[1] = 0;
		for(int j = 0, k = i; j <= alen && k; ++j, --k)
			if(k <= blen)
				bmsk[b[k] == '1'] |= 1LL << j;
		for(unordered_map<LL, int>::iterator it = f.begin(); it != f.end(); ++it) {
			LL msk = it -> first;
			int ways = it -> second;
			for(int o = 0; o < 2; ++o) {
				LL msk2 = ((msk << 1) & amsk[o]) | (msk & bmsk[o]);
				(g[msk2] += ways) >= mod && (g[msk2] -= mod);
			}
		}
		swap(f, g);
	}
	printf("%d\n", f[1LL << alen]);
	return 0;
}
