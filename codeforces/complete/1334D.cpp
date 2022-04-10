#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)1e5 + 1;
int t, n, tot, seq[maxn];
LL L, R;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%lld%lld", &n, &L, &R);
		tot = 0;
		LL pre = 0, cur;
		for(int i = 1; i < n; ++i) {
			cur = pre + (n - i) * 2; // (pre, cur]
			if(max(pre + 1, L) <= min(cur, R))
				for(int j = 1; j <= (n - i) * 2; ++j)
					if(pre + j >= L && pre + j <= R)
						seq[tot++] = j & 1 ? i : i + (j >> 1);
			pre = cur;
			if(pre >= R)
				break;
		}
		if(pre < R)
			seq[tot++] = 1;
		for(int i = 0; i < tot; ++i)
			printf("%d%c", seq[i], " \n"[i == tot - 1]);
	}
	return 0;
}