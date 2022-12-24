#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, perm[maxn];
long long ans;
void solve(int *pL, int *pR) {
	int len = pR - pL;
	if(len == 1)
		return;
	int *pM = pL + len / 2;
	solve(pL, pM);
	solve(pM, pR);
	static int vec[maxn];
	for(int *u = pL, *v = pM, *w = vec; u < pM || v < pR; )
		if(v == pR || (u < pM && *u < *v)) {
			*(w++) = *(u++);
			ans += v - pM;
		} else {
			*(w++) = *(v++);
		}
	memcpy(pL, vec, len * sizeof(*pL));
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", perm + i);
	for(int i = 1; i <= n; ++ans) {
		int p = i;
		while((i += 2) <= n && perm[i - 1] > perm[i]);
		reverse(perm + p, perm + i);
	}
	solve(perm + 1, perm + n + 1);
	printf("%lld\n", ans);
	return 0;
}
